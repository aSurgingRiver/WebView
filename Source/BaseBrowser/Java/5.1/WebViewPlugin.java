// Copyright Epic Games, Inc. All Rights Reserved.
package com.epicgames.unreal;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.Canvas;
import android.graphics.Color;
import android.net.http.SslError;
import android.opengl.EGL14;
import android.opengl.EGLConfig;
import android.opengl.EGLContext;
import android.opengl.EGLDisplay;
import android.opengl.EGLExt;
import android.opengl.GLES11Ext;
import android.opengl.EGLSurface;
import android.opengl.GLES20;
import javax.microedition.khronos.egl.EGL10;
import android.opengl.GLES31Ext;
import android.util.AttributeSet;
import android.util.Log;
import android.os.SystemClock;
import android.os.Message;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.FrameLayout;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.ClientCertRequest;
import android.webkit.ConsoleMessage;
import android.webkit.HttpAuthHandler;
import android.webkit.JsResult;
import android.webkit.JsPromptResult;
import android.webkit.PermissionRequest;
import android.webkit.SslErrorHandler;
import android.webkit.WebBackForwardList;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import java.io.ByteArrayInputStream;
import android.graphics.SurfaceTexture;
import android.view.Surface;
import android.os.Build;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.WindowMetrics;
import android.view.WindowManager;

import java.nio.ByteBuffer;
import java.text.MessageFormat;
import android.view.InputDevice;

// Simple layout to apply absolute positioning for the WebView
//class WebViewPluginVertScroll extends ViewGroup
//{
//	public WebViewPluginVertScroll(Context context, WebView inWebViewPlugin)
//	{
//		super(context);
//		webView = inWebViewPlugin;
//	}
//
//	@Override
//	protected void onLayout(boolean changed, int left, int top, int right, int bottom){
////		webView.layout(left+curX,top+curY,right+curX,bottom+curY);
//		webView.layout(left,top,right,bottom);
//	}
//
//	public boolean Update(final int x, final int y, final int width, final int height){
//		curX = x;
//		curY = y;
//		ViewGroup.LayoutParams params = getLayoutParams();
//		if(params==null){
//			params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT, ViewGroup.LayoutParams.FILL_PARENT);
//		}
//		params.width = width;
//		params.height = height;
//		setLayoutParams(params);
//		return true;
//	}
//	private WebView webView;
//	int curX;
//	int curY;
//}

class WebViewEnv {
	private static final WebViewEnv instance = new WebViewEnv();

	private static class EnvContext{
		public void MakeCurrent(){
			EGL14.eglMakeCurrent(mDisplay, mSurfaceDraw, mSurfaceRead, mContext);
		}
		public EGLDisplay mDisplay;
		public EGLContext mContext;
		public EGLSurface mSurfaceDraw;
		public EGLSurface mSurfaceRead;
	}

	public static native void Log(String message);

	public void RenderEnv(){
		if(nowContext==null )return ;
		nowContext.MakeCurrent();
	}
	public void RestoreEnv(){
		if(oldContext==null )return ;
		oldContext.MakeCurrent();
	}

	public WebViewEnv() {
	}

	public static GameActivity GetGameActivity(){
		return GameActivity._activity; // 5.1-5.4
		//return GameActivity.Get(); // 5.5 least
	}
	private void Initinner(int texture_type,EGLContext mContext,EGLDisplay mDisplay){
//		nowContext = new EnvContext();
		DisplayMetrics displayMetrics = new DisplayMetrics();
		GetGameActivity().getWindowManager().getDefaultDisplay().getRealMetrics(displayMetrics);
		int width = displayMetrics.widthPixels;
		int height = displayMetrics.heightPixels;

		EnvContext curContext = new EnvContext();
		curContext.mDisplay = EGL14.EGL_NO_DISPLAY;
		EGLContext shareContext = EGL14.EGL_NO_CONTEXT;
		// texture_type 2:vulkan  1:opengl  0:buffer
		if(texture_type !=1&&texture_type !=2){
			BackendRender(0,width,height);
			return ;
		}
		else if(texture_type==1){
			String RendererString = GLES20.glGetString(GLES20.GL_RENDERER);
			if (RendererString!=null && RendererString.contains("Adreno (TM) ")){
				String lastVersion ="";
				for(char at: RendererString.substring(12).toCharArray()){
					if(!Character.isDigit(at))
						break;
					lastVersion = lastVersion + at;
				}
				int AdrenoVersion = Integer.parseInt(lastVersion);
				if (AdrenoVersion < 400 || android.os.Build.VERSION.SDK_INT < 22)
				{
					mUseOwnContext = false;
					BackendRender(0,width,height);
					return ;
				}
			}
			curContext.mDisplay = mDisplay;
			shareContext = mContext;
		}
		else{
			curContext.mDisplay = EGL14.eglGetDisplay(EGL14.EGL_DEFAULT_DISPLAY);
			if (curContext.mDisplay == EGL14.EGL_NO_DISPLAY)
			{
				BackendRender(0,width,height);
				return;
			}
			int[] version = new int[2];
			if (!EGL14.eglInitialize(curContext.mDisplay, version, 0, version, 1))
			{
				curContext.mDisplay = null;
				BackendRender(0,width,height);
				return ;
			}
			mCreatedEGLDisplay = true;
		}

		int[] configSpec = new int[] {
				EGL14.EGL_RENDERABLE_TYPE, EGLExt.EGL_OPENGL_ES3_BIT_KHR,
				EGL14.EGL_SURFACE_TYPE, EGL14.EGL_WINDOW_BIT,
				EGL14.EGL_RED_SIZE,   8,
				EGL14.EGL_GREEN_SIZE, 8,
				EGL14.EGL_BLUE_SIZE,  8,
				EGL14.EGL_ALPHA_SIZE,  8,
				EGL14.EGL_DEPTH_SIZE, 8,
				EGL14.EGL_STENCIL_SIZE, 8,
				EGL14.EGL_NONE,
				};
		EGLConfig[] configs = new EGLConfig[1];
		int[] num_config = new int[1];
		EGL14.eglChooseConfig(curContext.mDisplay, configSpec, 0, configs, 0, 1, num_config, 0);
		int[] contextAttribs = new int[] {
						EGL14.EGL_CONTEXT_CLIENT_VERSION, 2,
						EGL14.EGL_NONE
				};
		curContext.mContext = EGL14.eglCreateContext(curContext.mDisplay, configs[0], shareContext, contextAttribs, 0);

		String extensions = EGL14.eglQueryString(curContext.mDisplay, EGL10.EGL_EXTENSIONS);
		if (extensions!=null && extensions.contains("EGL_KHR_surfaceless_context"))
		{
			curContext.mSurfaceDraw = EGL14.EGL_NO_SURFACE;
		}
		else
		{
			int[] pbufferAttribs = new int[] { EGL14.EGL_NONE };
			curContext.mSurfaceDraw = EGL14.eglCreatePbufferSurface(curContext.mDisplay, configs[0], pbufferAttribs, 0);
		}
		curContext.mSurfaceRead = curContext.mSurfaceDraw;

		nowContext = curContext;

		oldContext = new EnvContext();

		oldContext.mDisplay = EGL14.eglGetCurrentDisplay();
		oldContext.mContext = EGL14.eglGetCurrentContext();
		oldContext.mSurfaceDraw = EGL14.eglGetCurrentSurface(EGL14.EGL_DRAW);
		oldContext.mSurfaceRead = EGL14.eglGetCurrentSurface(EGL14.EGL_READ);

		RenderEnv();
		BackendRender(texture_type,width,height);
		RestoreEnv();
	}
	public static WebViewEnv Get(){
		return instance;
	}

	public boolean UseOwnContext(){
		return mUseOwnContext;
	}

	private native void BackendRender(int type,int screenW,int screenH);
	// for system init
	public void Init(int texture_type){
		EGLDisplay mDisplay = EGL14.eglGetCurrentDisplay();
		EGLContext mContext = EGL14.eglGetCurrentContext();
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				WebViewEnv.Get().Initinner(texture_type,mContext,mDisplay);
			}
		});
	}
	@Override
	protected void finalize(){
		if(nowContext!=null){
			if (nowContext.mSurfaceDraw != EGL14.EGL_NO_SURFACE)
			{
				EGL14.eglDestroySurface(nowContext.mDisplay, nowContext.mSurfaceDraw);
				nowContext.mSurfaceDraw = nowContext.mSurfaceRead = EGL14.EGL_NO_SURFACE;
			}
			if (nowContext.mContext != EGL14.EGL_NO_CONTEXT)
			{
				EGL14.eglDestroyContext(nowContext.mDisplay, nowContext.mContext);
				nowContext.mContext = EGL14.EGL_NO_CONTEXT;
			}
			if(mCreatedEGLDisplay){
				EGL14.eglTerminate(nowContext.mDisplay);
				nowContext.mDisplay = EGL14.EGL_NO_DISPLAY;
				mCreatedEGLDisplay = false;
			}
		}
	}
	private EnvContext nowContext;
	private EnvContext oldContext;
	private boolean mUseOwnContext=true;
	private boolean mCreatedEGLDisplay=false;

//	private int     type=0;

}
// Wrapper for the layout and WebView for the C++ to call
class WebViewPlugin
{
	private static final String TAG = "WebViewPlugin";

	public WebViewPlugin(long inNativePtr, int type,int width, int height, final boolean bEnableRemoteDebugging, final boolean bUseTransparency, final boolean bEnableDomStorage,  final String userAgentApplication)
	{
		final WebViewPlugin w = this;

		nativePtr = inNativePtr;

		if(type==1 || type==2){
			webViewDraw = new WebViewDrawEGL();
		}
		else{
			webViewDraw = new WebViewDrawBuffer();
		}
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				WebView.setWebContentsDebuggingEnabled(bEnableRemoteDebugging && !WebViewEnv.GetGameActivity().nativeIsShippingBuild());

				// create the WebView
				webView = new GLWebView(WebViewEnv.GetGameActivity());
				webView.setWebViewClient(new ViewClient());
				webView.setWebChromeClient(new ChromeClient());
				String UserAgent = WebSettings.getDefaultUserAgent(WebViewEnv.GetGameActivity()) + " " + userAgentApplication;
				//webView.getSettings().supportMultipleWindows();
				webView.getSettings().setLayoutAlgorithm(WebSettings.LayoutAlgorithm.NORMAL);
				webView.getSettings().setLoadsImagesAutomatically(true);
				webView.getSettings().setUserAgentString(UserAgent);
				webView.getSettings().setJavaScriptEnabled(true);
//				webView.getSettings().setJavaScriptCanOpenWindowsAutomatically(true);
				webView.getSettings().setAllowFileAccess( true );
				webView.getSettings().setAllowContentAccess( true );
				webView.getSettings().setAllowFileAccessFromFileURLs(true);
				webView.getSettings().setAllowUniversalAccessFromFileURLs(true);
//				webView.getSettings().setOffscreenPreRaster(true);
				//webView.getSettings().setSupportMultipleWindows(true);
				webView.getSettings().setDomStorageEnabled(bEnableDomStorage);//bEnableDomStorage
				webView.getSettings().setMixedContentMode(WebSettings.MIXED_CONTENT_ALWAYS_ALLOW);
				webView.getSettings().setMediaPlaybackRequiresUserGesture(false);

				webView.getSettings().setCacheMode( WebSettings.LOAD_DEFAULT );
				webView.getSettings().setLoadWithOverviewMode(true);
				webView.getSettings().setUseWideViewPort(true);
				//
//				webView.getSettings().setSupportZoom(true);//
//				webView.getSettings().setBuiltInZoomControls(true); //
//				webView.getSettings().setDisplayZoomControls(false);
//				webView.getSettings().setSafeBrowsingEnabled(false);
//				webView.getSettings().setVideoOverlayForEmbeddedEncryptedVideoEnabled(false);
				if(type==0){
					android.graphics.Paint paint = new android.graphics.Paint();
					paint.setAntiAlias(true);
					paint.setFilterBitmap(true);
					paint.setDither(true);
					webView.setLayerType(View.LAYER_TYPE_SOFTWARE, paint);
				}
				else{
					webView.setLayerType(View.LAYER_TYPE_HARDWARE, null);
				}
				webView.setVerticalScrollBarEnabled(true);
				webView.setHorizontalScrollBarEnabled(true);
				webView.setFocusable(true);
				webView.setFocusableInTouchMode(true);
//				webView.addJavascriptInterface();
				if (bUseTransparency)
				{
					webView.setBackgroundColor(Color.TRANSPARENT);
				}

//				webView.setVisibility(View.INVISIBLE);

				// Wrap the webview in a layout that will do absolute positioning for us
				ViewGroup decorView = (ViewGroup) WebViewEnv.GetGameActivity().getWindow().getDecorView();
				ViewGroup.LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT, ViewGroup.LayoutParams.FILL_PARENT);
//				layoutScrollVert = new WebViewPluginVertScroll(WebViewEnv.GetGameActivity(), webView);
//				layoutScrollVert.addView(webView, params );
//				WebViewEnv.GetGameActivity().addContentView(layoutScrollVert, params);
//				WebViewEnv.Get().AddView(layoutScrollVert);
				decorView.addView(webView, 0, params);
				Update(0,0,width,height);
//				webView.requestFocus();
////				webView.setSurface(surface);
//				WebViewEnv.GetGameActivity().addContentView(webView, params);


//				webView.Update(0,0,width,height);
				webView.BindInterface();


				NextURL = null;
			}
		});
	}

	public String GetURL(){
		if(webView==null)
			return "";
		return webView.getUrl();
	}

	public void Draw(){
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable() {
			 @Override
			 public void run(){
				 if(webView==null)
					 return ;
//				 webView.draw(null);
//				 webView.invalidate();
			 }
		}
		);
	}
	public native void Asyn(String type,String Json,String funcid);
	public native void OnPaint(int width,int height);

	public native void OnAcceleratePaint(int width,int height);
//	public native void OnBitmapPaint(int width,int height,Bitmap bitmap);
//	public native void RegisterBitmap(int width,int height,Bitmap bitmap);

	public native int Register(int width,int height);

	public native ByteBuffer RegisterMemory(int width,int height);

	public native void Unregister(int width,int height);


	boolean PendingSetVisibility;
	public void SetVisibility(boolean InIsVisible)
	{
		PendingSetVisibility = InIsVisible;
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				webView.setVisibility(PendingSetVisibility? View.VISIBLE: View.GONE);
			}
		});
	}

	public void release()
	{
		Close();
	}

	public void ExecuteJavascript(final String script)
	{
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				if(webView != null)
				{
					webView.evaluateJavascript(script, null);
				}
			}
		});
	}
	public void LoadURL(final String url)
	{
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				NextURL = url;
				//NextURL = "https://m.bilibili.com";
				int colPos = NextURL.indexOf(':');

				boolean bNeedsPrefix = colPos < 0;

				if(!bNeedsPrefix  && !NextURL.equalsIgnoreCase("about:blank"))
				{
					try
					{
						String UrlAddress = NextURL.substring(colPos + 1);

						//check if the address contains only numbers
						bNeedsPrefix = UrlAddress.matches("[0-9]+"); // it's a port number, and URLs like "google.com:80" also need the "http://" prefix

						//try to correct malformed protocols, like "http:www.google.com"
						if(!bNeedsPrefix)
						{
							String UrlProtocol = NextURL.substring(0, colPos);

							if((NextURL.equalsIgnoreCase("http") || NextURL.equalsIgnoreCase("https")) && !UrlAddress.startsWith("/"))
							{
								NextURL = UrlProtocol + "://" + UrlAddress;
							}
						}

					}
					catch(IndexOutOfBoundsException e)
					{}
				}

				if(bNeedsPrefix)
				{
					//default scheme is http://
					NextURL = "http://" + NextURL;
				}

				webView.loadUrl(NextURL);
				NextURL = null;
//				NextContent = null;
			}
		});
	}

	public void LoadString(final String contents, final String url)
	{
//		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
//		{
//			@Override
//			public void run()
//			{
//				NextURL = url;
//				NextContent = contents;
//			}
//		});
	}

	public void StopLoad()
	{
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				webView.stopLoading();
			}
		});
	}

	public void Reload()
	{
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				webView.reload();
			}
		});
	}

	public void GoBackOrForward(final int Steps)
	{
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				webView.goBackOrForward(Steps);
			}
		});
	}

	public boolean CanGoBackOrForward(int Steps)
	{
		return webView.canGoBackOrForward(Steps);
	}

	public void SendTouchEvent(int idx,int event, float x, float y)
	{
		final int index = idx;
		final int actionType = event;
		final float actionX = x;//webView.getLeft() + (x * webView.getWidth());
		final float actionY = y;//webView.getTop() + (y * webView.getHeight());
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				long eventTime = SystemClock.uptimeMillis();
//				String strAction="unkown" ;
				if(MotionEvent.ACTION_DOWN==event){
//					strAction = "Begin";
					downTime = eventTime;
					ScrollX =webView.getScrollX();
					ScrollY =webView.getScrollY();
				}
//				else if(MotionEvent.ACTION_UP==event){
////					ScrollX =webView.getScrollX();
////					ScrollY =webView.getScrollY();
//					strAction = "UP";
//				}
//				else if(MotionEvent.ACTION_MOVE==event){
//					strAction = "Move";
//				}
				webView.computeScroll();
				MotionEvent.PointerProperties Properties = new MotionEvent.PointerProperties();
				Properties.id = index;
				Properties.toolType = MotionEvent.TOOL_TYPE_FINGER;
				MotionEvent.PointerCoords Coords = new MotionEvent.PointerCoords();
				Coords.x = actionX + ScrollX;
				Coords.y = actionY + ScrollY;
//				Log.i(LogTag,String.format("time{%d %d} in{%.0f %.0f} s{%d %d} o{%.0f %.0f} idx=%d action=%s "
//						,downTime,eventTime,actionX,actionY,ScrollX,ScrollY ,Coords.x,Coords.y,idx,strAction));
				MotionEvent event = MotionEvent.obtain(downTime, eventTime, actionType,
						1, new MotionEvent.PointerProperties[]{Properties},
						new MotionEvent.PointerCoords[]{Coords}, 0, 0, 1.0f, 1.0f, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
				webView.onTouchEvent(event);
				event.recycle();
			}
		});
	}

	public void SendMouseEvent(int idx,int event, float x, float y)
	{
		final int index = idx;
		final int actionType = event;
		final float actionX = x;
		final float actionY = y;
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				if(MotionEvent.ACTION_DOWN==event){
					downTime = SystemClock.uptimeMillis();
					ScrollX =webView.getScrollX();
					ScrollY =webView.getScrollY();
				}
				int buttonState =0;
				if((index&MotionEvent.BUTTON_PRIMARY) == MotionEvent.BUTTON_PRIMARY)buttonState = (buttonState|MotionEvent.BUTTON_PRIMARY);
				if((index&MotionEvent.BUTTON_SECONDARY) == MotionEvent.BUTTON_SECONDARY)buttonState = (buttonState|MotionEvent.BUTTON_SECONDARY);
				if((index&MotionEvent.BUTTON_TERTIARY) == MotionEvent.BUTTON_TERTIARY)buttonState = (buttonState|MotionEvent.BUTTON_TERTIARY);

				long eventTime = SystemClock.uptimeMillis();
				MotionEvent.PointerProperties Properties = new MotionEvent.PointerProperties();
				Properties.id = 0;
				Properties.toolType = MotionEvent.TOOL_TYPE_MOUSE;

				MotionEvent.PointerCoords Coords = new MotionEvent.PointerCoords();
				Coords.x = actionX + ScrollX;
				Coords.y = actionY + ScrollY;

				MotionEvent event = MotionEvent.obtain(downTime, eventTime, actionType,
						1, new MotionEvent.PointerProperties[]{Properties},
						new MotionEvent.PointerCoords[]{Coords}, 0, buttonState, 1.0f, 1.0f, 0, 0, InputDevice.SOURCE_MOUSE, 0);

				webView.dispatchTouchEvent(event);
				event.recycle();
			}
		});
	}

	private static class KeyTableData
	{
		public final int key;
		public final int meta;

		KeyTableData (int keycode, int metadata)
		{
			key = keycode;
			meta = metadata;
		}
	}
	
	private static final KeyTableData[] KeyTableList = {
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 0
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 1
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 2
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 3
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 4
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 5
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 6
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 7
		new KeyTableData(KeyEvent.KEYCODE_DEL, 0),	// 8
		new KeyTableData(KeyEvent.KEYCODE_TAB, 0),	// 9
		new KeyTableData(KeyEvent.KEYCODE_ENTER, 0),	// 10
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 11
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 12
		new KeyTableData(KeyEvent.KEYCODE_ENTER, 0),	// 13
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 14
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 15
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 16
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 17
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 18
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 19
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 20
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 21
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 22
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 23
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 24
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 25
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 26
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 27
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 28
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 29
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 30
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0),	// 31
		new KeyTableData(KeyEvent.KEYCODE_SPACE, 0),	// 32
		new KeyTableData(KeyEvent.KEYCODE_1, KeyEvent.META_SHIFT_ON),	// 33
		new KeyTableData(KeyEvent.KEYCODE_APOSTROPHE, KeyEvent.META_SHIFT_ON),	// 34
		new KeyTableData(KeyEvent.KEYCODE_POUND, 0),	// 35
		new KeyTableData(KeyEvent.KEYCODE_4, KeyEvent.META_SHIFT_ON),	// 36
		new KeyTableData(KeyEvent.KEYCODE_5, KeyEvent.META_SHIFT_ON),	// 37
		new KeyTableData(KeyEvent.KEYCODE_7, KeyEvent.META_SHIFT_ON),	// 38
		new KeyTableData(KeyEvent.KEYCODE_APOSTROPHE, 0),	// 39
		new KeyTableData(KeyEvent.KEYCODE_NUMPAD_LEFT_PAREN, 0),	// 40
		new KeyTableData(KeyEvent.KEYCODE_NUMPAD_RIGHT_PAREN, 0),	// 41
		new KeyTableData(KeyEvent.KEYCODE_STAR, 0),	// 42
		new KeyTableData(KeyEvent.KEYCODE_PLUS, 0),	// 43
		new KeyTableData(KeyEvent.KEYCODE_COMMA, 0),	// 44
		new KeyTableData(KeyEvent.KEYCODE_MINUS, 0),	// 45
		new KeyTableData(KeyEvent.KEYCODE_PERIOD, 0),	// 46
		new KeyTableData(KeyEvent.KEYCODE_SLASH, 0),	// 47
		new KeyTableData(KeyEvent.KEYCODE_0, 0),	// 48
		new KeyTableData(KeyEvent.KEYCODE_1, 0),	// 49
		new KeyTableData(KeyEvent.KEYCODE_2, 0),	// 50
		new KeyTableData(KeyEvent.KEYCODE_3, 0),	// 51
		new KeyTableData(KeyEvent.KEYCODE_4, 0),	// 52
		new KeyTableData(KeyEvent.KEYCODE_5, 0),	// 53
		new KeyTableData(KeyEvent.KEYCODE_6, 0),	// 54
		new KeyTableData(KeyEvent.KEYCODE_7, 0),	// 55
		new KeyTableData(KeyEvent.KEYCODE_8, 0),	// 56
		new KeyTableData(KeyEvent.KEYCODE_9, 0),	// 57
		new KeyTableData(KeyEvent.KEYCODE_SEMICOLON, KeyEvent.META_SHIFT_ON),	// 58
		new KeyTableData(KeyEvent.KEYCODE_SEMICOLON, 0),	// 59
		new KeyTableData(KeyEvent.KEYCODE_COMMA, KeyEvent.META_SHIFT_ON),	// 60
		new KeyTableData(KeyEvent.KEYCODE_EQUALS, 0),	// 61
		new KeyTableData(KeyEvent.KEYCODE_PERIOD, KeyEvent.META_SHIFT_ON),	// 62
		new KeyTableData(KeyEvent.KEYCODE_SLASH, KeyEvent.META_SHIFT_ON),	// 63
		new KeyTableData(KeyEvent.KEYCODE_AT, 0),	// 64
		new KeyTableData(KeyEvent.KEYCODE_A, KeyEvent.META_SHIFT_ON),	// 65
		new KeyTableData(KeyEvent.KEYCODE_B, KeyEvent.META_SHIFT_ON),	// 66
		new KeyTableData(KeyEvent.KEYCODE_C, KeyEvent.META_SHIFT_ON),	// 67
		new KeyTableData(KeyEvent.KEYCODE_D, KeyEvent.META_SHIFT_ON),	// 68
		new KeyTableData(KeyEvent.KEYCODE_E, KeyEvent.META_SHIFT_ON),	// 69
		new KeyTableData(KeyEvent.KEYCODE_F, KeyEvent.META_SHIFT_ON),	// 70
		new KeyTableData(KeyEvent.KEYCODE_G, KeyEvent.META_SHIFT_ON),	// 71
		new KeyTableData(KeyEvent.KEYCODE_H, KeyEvent.META_SHIFT_ON),	// 72
		new KeyTableData(KeyEvent.KEYCODE_I, KeyEvent.META_SHIFT_ON),	// 73
		new KeyTableData(KeyEvent.KEYCODE_J, KeyEvent.META_SHIFT_ON),	// 74
		new KeyTableData(KeyEvent.KEYCODE_K, KeyEvent.META_SHIFT_ON),	// 75
		new KeyTableData(KeyEvent.KEYCODE_L, KeyEvent.META_SHIFT_ON),	// 76
		new KeyTableData(KeyEvent.KEYCODE_M, KeyEvent.META_SHIFT_ON),	// 77
		new KeyTableData(KeyEvent.KEYCODE_N, KeyEvent.META_SHIFT_ON),	// 78
		new KeyTableData(KeyEvent.KEYCODE_O, KeyEvent.META_SHIFT_ON),	// 79
		new KeyTableData(KeyEvent.KEYCODE_P, KeyEvent.META_SHIFT_ON),	// 80
		new KeyTableData(KeyEvent.KEYCODE_Q, KeyEvent.META_SHIFT_ON),	// 81
		new KeyTableData(KeyEvent.KEYCODE_R, KeyEvent.META_SHIFT_ON),	// 82
		new KeyTableData(KeyEvent.KEYCODE_S, KeyEvent.META_SHIFT_ON),	// 83
		new KeyTableData(KeyEvent.KEYCODE_T, KeyEvent.META_SHIFT_ON),	// 84
		new KeyTableData(KeyEvent.KEYCODE_U, KeyEvent.META_SHIFT_ON),	// 85
		new KeyTableData(KeyEvent.KEYCODE_V, KeyEvent.META_SHIFT_ON),	// 86
		new KeyTableData(KeyEvent.KEYCODE_W, KeyEvent.META_SHIFT_ON),	// 87
		new KeyTableData(KeyEvent.KEYCODE_X, KeyEvent.META_SHIFT_ON),	// 88
		new KeyTableData(KeyEvent.KEYCODE_Y, KeyEvent.META_SHIFT_ON),	// 89
		new KeyTableData(KeyEvent.KEYCODE_Z, KeyEvent.META_SHIFT_ON),	// 90
		new KeyTableData(KeyEvent.KEYCODE_LEFT_BRACKET, 0),	// 91
		new KeyTableData(KeyEvent.KEYCODE_BACKSLASH, 0),	// 92
		new KeyTableData(KeyEvent.KEYCODE_RIGHT_BRACKET, 0),	// 93
		new KeyTableData(KeyEvent.KEYCODE_6, KeyEvent.META_SHIFT_ON),	// 94
		new KeyTableData(KeyEvent.KEYCODE_MINUS, KeyEvent.META_SHIFT_ON),	// 95
		new KeyTableData(KeyEvent.KEYCODE_GRAVE, 0),	// 96
		new KeyTableData(KeyEvent.KEYCODE_A, 0),	// 97
		new KeyTableData(KeyEvent.KEYCODE_B, 0),	// 98
		new KeyTableData(KeyEvent.KEYCODE_C, 0),	// 99
		new KeyTableData(KeyEvent.KEYCODE_D, 0),	// 100
		new KeyTableData(KeyEvent.KEYCODE_E, 0),	// 101
		new KeyTableData(KeyEvent.KEYCODE_F, 0),	// 102
		new KeyTableData(KeyEvent.KEYCODE_G, 0),	// 103
		new KeyTableData(KeyEvent.KEYCODE_H, 0),	// 104
		new KeyTableData(KeyEvent.KEYCODE_I, 0),	// 105
		new KeyTableData(KeyEvent.KEYCODE_J, 0),	// 106
		new KeyTableData(KeyEvent.KEYCODE_K, 0),	// 107
		new KeyTableData(KeyEvent.KEYCODE_L, 0),	// 108
		new KeyTableData(KeyEvent.KEYCODE_M, 0),	// 109
		new KeyTableData(KeyEvent.KEYCODE_N, 0),	// 110
		new KeyTableData(KeyEvent.KEYCODE_O, 0),	// 111
		new KeyTableData(KeyEvent.KEYCODE_P, 0),	// 112
		new KeyTableData(KeyEvent.KEYCODE_Q, 0),	// 113
		new KeyTableData(KeyEvent.KEYCODE_R, 0),	// 114
		new KeyTableData(KeyEvent.KEYCODE_S, 0),	// 115
		new KeyTableData(KeyEvent.KEYCODE_T, 0),	// 116
		new KeyTableData(KeyEvent.KEYCODE_U, 0),	// 117
		new KeyTableData(KeyEvent.KEYCODE_V, 0),	// 118
		new KeyTableData(KeyEvent.KEYCODE_W, 0),	// 119
		new KeyTableData(KeyEvent.KEYCODE_X, 0),	// 120
		new KeyTableData(KeyEvent.KEYCODE_Y, 0),	// 121
		new KeyTableData(KeyEvent.KEYCODE_Z, 0),	// 122
		new KeyTableData(KeyEvent.KEYCODE_LEFT_BRACKET, KeyEvent.META_SHIFT_ON),	// 123
		new KeyTableData(KeyEvent.KEYCODE_BACKSLASH, KeyEvent.META_SHIFT_ON),	// 124
		new KeyTableData(KeyEvent.KEYCODE_RIGHT_BRACKET, KeyEvent.META_SHIFT_ON),	// 125
		new KeyTableData(KeyEvent.KEYCODE_GRAVE, KeyEvent.META_SHIFT_ON),	// 126
		new KeyTableData(KeyEvent.KEYCODE_UNKNOWN, 0)	// 127
	};

	public boolean SendKeyEvent(boolean bDown, int keycode)
	{
		if (keycode < 0 || keycode > 127)
		{
			return false;
		}

		final int actionType = bDown ? KeyEvent.ACTION_DOWN : KeyEvent.ACTION_UP;
		final long actionTime = SystemClock.uptimeMillis();
		final int actionCode = KeyTableList[keycode].key;
		final int actionMeta = KeyTableList[keycode].meta;
//		GameActivity.Log.debug("SendTouchEvent(event=" + (bDown ? "Down" : "Up") + ", key=" + keycode + ", code=" + actionCode + ", meta=" + actionMeta);
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				long eventTime = SystemClock.uptimeMillis();
				webView.dispatchKeyEvent(new KeyEvent(actionTime, eventTime, actionType, actionCode, 0, actionMeta));
			}
		});
		return true;
	}

	// called from C++ paint event
	public void Update(final int x, final int y, final int width, final int height)
	{
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				if (bClosed || webView==null) {
					return;
				}
				webView.Update(x,y,width,height);
			}
		});
	}

	public void Scale(int zoom){
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				if (bClosed || webView==null) {
					return;
				}
				webView.setInitialScale(zoom);
			}
		});
	}

	public void Close()
	{
		bClosed = true;
		WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				if(webView!=null){
					ViewGroup parent = (ViewGroup)webView.getParent();
					if (parent != null)
					{
						parent.removeView(webView);
					}
				}
//				if(layoutScrollVert!=null){
//					ViewGroup parent = (ViewGroup)layoutScrollVert.getParent();
//					if (parent != null)
//					{
//						parent.removeView(layoutScrollVert);
//					}
//				}
				WebViewEnv.Get().RenderEnv();
				webViewDraw.Release();
				WebViewEnv.Get().RestoreEnv();
				webViewDraw = null;
			}
		});
	}

/*
		All this internal surface view does is manage the
		offscreen bitmap that the media player decoding can
		render into for eventual extraction to the UE4 buffers.
*/

	public native void nativeClearCachedAttributeState(int PositionAttrib, int TexCoordsAttrib);

	// ======================================================================================

	class JSMessage{
//		Context mContext;
//		JSMessage(Context c) {
//			mContext = c;
//		}

		@android.webkit.JavascriptInterface
		public void asyn(String type,String Json,String funcid) {
			Asyn(type,Json,funcid);
		}
	}

	class WebViewSurfaceTexture extends SurfaceTexture implements SurfaceTexture.OnFrameAvailableListener {

		private Surface mSurface;

		public boolean EqualSize(int width,int height){
			return width==Width && height==Height;
		}
		public WebViewSurfaceTexture(int texName,int width,int height) {
			super(texName);
			Width = width;
			Height = height;
			initSurfaceTexture();
		}

		public WebViewSurfaceTexture(int texName, boolean singleBufferMode) {
			super(texName, singleBufferMode);
			initSurfaceTexture();
		}

		public WebViewSurfaceTexture(boolean singleBufferMode) {
			super(singleBufferMode);
			initSurfaceTexture();
		}

		void initSurfaceTexture() {
			mSurface = new Surface(this);
			setOnFrameAvailableListener(this);
			setDefaultBufferSize(Width,Height);
		}

		@Override
		public void release() {
			mSurface.release();
			mSurface = null;
			super.release();
			Unregister(Width,Height);
		}

		public Canvas beginDraw() {
			return mSurface != null ? mSurface.lockCanvas(null) : null;
		}

		public void endDraw(Canvas canvas) {
			if(mSurface != null){
				mSurface.unlockCanvasAndPost(canvas);
			}
		}

		@Override
		public void onFrameAvailable(SurfaceTexture sf) {
			if(isReleased())
				return ;// has release stop sync
			try{
				WebViewEnv.Get().RenderEnv();
				updateTexImage();
				OnAcceleratePaint(Width,Height);
			}
			finally {
				WebViewEnv.Get().RestoreEnv();
			}
		}

		private int Width;
		private int Height;

		//private native void updateNativeTexImage();
	}
	public class WebViewDraw {
		@Override
		protected void finalize(){
			WebViewEnv.Get().RenderEnv();
			Release();
			WebViewEnv.Get().RestoreEnv();
		}
		public void endDraw(){}

		public void Release(){
			if(canvas!=null){
				canvas = null;
			}
		}

		public long GetNativePtr()
		{
			return WebViewPlugin.this.nativePtr;
		}

		public Canvas beginDraw(int width,int height){
			return null;
		}
		protected Canvas canvas = null;

	}

	class WebViewDrawEGL extends  WebViewDraw{
		@Override
		public void endDraw(){
			surfaceTexture.endDraw(canvas);
			WebViewEnv.Get().RestoreEnv();
		}
		@Override
		public Canvas beginDraw(int width,int height){
			if(0==width||0==height) return null;
			if(surfaceTexture==null || !surfaceTexture.EqualSize(width,height)) {
				WebViewEnv.Get().RenderEnv();
				Release();
				textureid = Register(width,height) ;
				if(textureid<=0)
					return null;
				surfaceTexture = new WebViewSurfaceTexture(textureid,width, height);
				WebViewEnv.Get().RestoreEnv();
			}
			try{
				WebViewEnv.Get().RenderEnv();
				canvas = surfaceTexture.beginDraw();
			}
			catch( Exception e){
				canvas = null;
			}
			return canvas;
		}
		@Override
		public void Release(){
			if(surfaceTexture!=null){
				surfaceTexture.release();
				surfaceTexture = null;
			}
		}

		private int textureid = 0 ;
		private WebViewSurfaceTexture surfaceTexture=null;
//		private int is_lock = 0;
	}
	class WebViewDrawBuffer extends  WebViewDraw{
		@Override
		public void endDraw(){
			WebViewEnv.Get().RestoreEnv();
			shared_memory.position(0);
			target_bitmap.copyPixelsToBuffer(shared_memory);
//			shared_memory.rewind();
			OnPaint(preWidth,preHeight);
			WebViewEnv.Get().RestoreEnv();
//			target_bitmap.eraseColor(0x00000000);
		}
		@Override
		public Canvas beginDraw(int width,int height){
			if(0==width||0==height) return null;
			if(canvas==null || preWidth!=width || preHeight!=height) {
				Release();
				WebViewEnv.Get().RestoreEnv();
				Unregister(preWidth,preHeight);
				shared_memory = RegisterMemory(width,height);
				if(shared_memory==null){
					return null;
				}
				WebViewEnv.Get().RestoreEnv();
				preWidth = width;
				preHeight = height;
				target_bitmap = Bitmap.createBitmap(width, height, Config.ARGB_8888);
				canvas = new Canvas(target_bitmap);
			}
			return canvas;
		}

		@Override
		public void Release(){
			super.Release();
			if(target_bitmap!=null){
				target_bitmap = null;
			}
		}
		private Bitmap target_bitmap = null;
		private ByteBuffer shared_memory = null;
		protected int preWidth = 0 ;
		protected int preHeight = 0;
	}

	class GLWebView extends WebView 
	{
		// default constructors
		public GLWebView(Context context) {
			super(context);
			init();
		}

		public GLWebView(Context context, AttributeSet attrs) {
			super(context, attrs);
			init();
		}

		public GLWebView(Context context, AttributeSet attrs, int defStyle) {
			super(context, attrs, defStyle);
			init();
		}

		public void init()
		{
			setOnTouchListener(new View.OnTouchListener() {
				@Override
				public boolean onTouch(View v, MotionEvent event) {
					return false;
				}
			});
		}

		private boolean Update_Game(final int x, final int y,final int width, final int height){

			ViewGroup parent = (ViewGroup)webView.getParent();
			if (parent != null)
			{
				parent.removeView(webView);
			}

			FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
					width,
					height 
			);
//			params.leftMargin = x;
//			params.topMargin = y;
			ViewGroup decorView = (ViewGroup) WebViewEnv.GetGameActivity().getWindow().getDecorView();
			decorView.addView(webView, 0, params);
			return true;
		}

		public boolean Update(final int x, final int y, final int width, final int height){
			ViewGroup.LayoutParams params = getLayoutParams();
			if(params==null){
				params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT, ViewGroup.LayoutParams.FILL_PARENT);
			}
			params.width = width;
			params.height = height;
			setLayoutParams(params);
//			measure(
//					View.MeasureSpec.makeMeasureSpec(width, View.MeasureSpec.EXACTLY),
//					View.MeasureSpec.makeMeasureSpec(height, View.MeasureSpec.EXACTLY)
//			);
//			layout(0,0,width,height);
			return true;
		}


//		@Override
//		protected void onLayout(boolean changed, int left, int top, int right, int bottom){
//			Super.onLayout(left,top,right,bottom);
//		}

		@Override
		public boolean onInterceptTouchEvent(MotionEvent event) {
			return false; //
		}
		@Override
		public void draw(Canvas canvas) {
			if(bClosed)return ;
			Canvas _canvas = webViewDraw.beginDraw(webView.getWidth(), webView.getHeight());
			if(_canvas==null) return ;
			_canvas.save();
			int ScrollY = webView.getScrollY();
			int ScrollX = webView.getScrollX();
			_canvas.translate(-ScrollX, -ScrollY);
			try{
				super.draw(_canvas);
			}finally {
				_canvas.restore();
				webViewDraw.endDraw();
			}
		}
		@Override
		protected boolean awakenScrollBars() {
			return super.awakenScrollBars(View.SCROLLBARS_OUTSIDE_OVERLAY, true);
		}
		public void BindInterface(){
			addJavascriptInterface(new JSMessage(),"webview_android");
		}
	}

	private class ViewClient
		extends WebViewClient
	{
		@Override
		public void onReceivedSslError(WebView view, SslErrorHandler handler, SslError error) {
			handler.proceed();
		}
		@Override
		public WebResourceResponse shouldInterceptRequest(WebView View, String Url)
		{
			byte[] Result = shouldInterceptRequestImpl(Url);
			if (Result != null)
			{
				return new WebResourceResponse("text/html", "utf8", new ByteArrayInputStream(Result));
			}
			else
			{
				return null;
			}
		}

		@Override
		public boolean shouldOverrideUrlLoading(WebView View, WebResourceRequest request){
			if(ShouldOverrideUrlLoading(View,request.getUrl().toString()))return true;
			//View.loadUrl(Url);
			return super.shouldOverrideUrlLoading(View,request);
		}

		public native boolean ShouldOverrideUrlLoading(WebView View, String Url);
		@Override
		public void onPageStarted(WebView View, String Url, Bitmap Favicon)
		{
			WebBackForwardList History = View.copyBackForwardList();
			onPageLoad(Url, true, History.getSize(), History.getCurrentIndex());
		}

		@Override
		public void onPageFinished(WebView View, String Url)
		{
			webView.evaluateJavascript("\"object\" != typeof ue && (delete ue, ue = {});", null);
			webView.evaluateJavascript("\"object\" == typeof webview_android && (ue[\"$receive\"] != webview_android) &&(ue[\"$receive\"] = webview_android);", null);
			WebBackForwardList History = View.copyBackForwardList();
			onPageLoad(Url, false, History.getSize(), History.getCurrentIndex());
			super.onPageFinished(View,Url);
		}

		@Override
		public native void onReceivedError(WebView View, int ErrorCode, String Description, String Url);

		public native void onPageLoad(String Url, boolean bIsLoading, int HistorySize, int HistoryPosition);
		private native byte[] shouldInterceptRequestImpl(String Url);

		public long GetNativePtr()
		{
			return WebViewPlugin.this.nativePtr;
		}
	}

	private class ChromeClient
		extends WebChromeClient
	{
		public native boolean onJsAlert(WebView View, String Url, String Message, JsResult Result);
		public native boolean onJsBeforeUnload(WebView View, String Url, String Message, JsResult Result);
		public native boolean onJsConfirm(WebView View, String Url, String Message, JsResult Result);
		public native boolean onJsPrompt(WebView View, String Url, String Message, String DefaultValue, JsPromptResult Result);
		public native void onReceivedTitle(WebView View, String Title);

		public long GetNativePtr()
		{
			return WebViewPlugin.this.nativePtr;
		}

		@Override
		public boolean onCreateWindow(WebView View, boolean isDialog, boolean isUserGesture, Message resultMsg)
		{
			WebView newView = new WebView(WebViewEnv.GetGameActivity());
			View.addView(newView);
            WebView.WebViewTransport transport = (WebView.WebViewTransport) resultMsg.obj;
            transport.setWebView(newView);
            resultMsg.sendToTarget();
            return true;
		}
		@Override
		public void onPermissionRequest(PermissionRequest request) {
			WebViewEnv.GetGameActivity().runOnUiThread(new Runnable()
			{
				@Override
				public void run()
				{
					request.grant(request.getResources());
				}
			});
		}

		@Override
		public boolean onConsoleMessage(ConsoleMessage cm) {
			GameActivity.Log.warn(cm.message() + " -- From line "
				+ cm.lineNumber() + " of "
				+ cm.sourceId() );
			return true;
		}
	}
	public long GetNativePtr()
	{
		return nativePtr;
	}

	private WebViewDraw webViewDraw;
	public GLWebView webView;
//	private WebViewPluginVertScroll layoutScrollVert;
	private volatile boolean bClosed;
	private String NextURL;

	final private String LogTag="WebVP";
	private long downTime;
	private int ScrollX = 0;
	private int ScrollY = 0;
//	private String NextContent;
	
	// Address of the native SAndroidWebBrowserWidget object
	private long nativePtr;

}
