// Copyright aXiuShen. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "ImitateInput.h"
#include "MatureJsonValue.h"
#include "Widgets/SCompoundWidget.h"

#define BASEBROWSER_PARAMS(CLASSNAME) \
	DECLARE_DELEGATE_RetVal_OneParam(bool, FOnKeyUp, const FKeyEvent&); \
	DECLARE_DELEGATE_RetVal_OneParam(bool, FOnKeyDown, const FKeyEvent&); \
	DECLARE_DELEGATE_RetVal_OneParam(bool, FOnKeyChar, const FCharacterEvent&); \
	DECLARE_DELEGATE_OneParam(FOnLoadState, const int); \
	DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforePopup, FString, FString); \
	DECLARE_DELEGATE_TwoParams(FOnPostResponse, const FString&, const FString&); \
	DECLARE_DELEGATE_TwoParams(FOnDownloadComplete, FString, FString); \
	/*DECLARE_DELEGATE_TwoParams(FOnTextureChanged, UTexture2D*, UTexture2D*);*/ \
	DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnResourceLoad, FString, int, RequestHeaders&); \
	DECLARE_DELEGATE_ThreeParams(FOnJsStr, const FString&, const FString&, const FString&); \
	DECLARE_DELEGATE_ThreeParams(FOnJs, const FString&, const FMatureJsonValue&, const FString&); \
	DECLARE_DELEGATE_FourParams(FOnWebError, const FString&, const FString&, const FString&, int); \
	\
	SLATE_BEGIN_ARGS(CLASSNAME) \
		: _ViewportSize(FVector2D::ZeroVector)  \
		, _SwitchInputMethod(false)  \
		, _EnableMouseTransparency(false)  \
		, _InitialURL(TEXT("")) \
		, _BackgroundColor(255, 255, 255, 255) \
		, _ShowControls(true) \
		, _ShowAddressBar(false) \
		, _Touch(false) \
		, _BrowserFrameRate(30)  \
	{  \
		_Bridge = false;  \
		_Visibility = EVisibility::SelfHitTestInvisible;  \
	} \
	 \
		/* this party for event */  \
		/** Called before a popup window happens */  \
		SLATE_EVENT(FOnBeforePopup, OnBeforePopup) \
		/** Called when post response */ \
		SLATE_EVENT(FOnPostResponse, OnPostResponse) \
		/** Called when document loading change. */ \
		SLATE_EVENT(FOnLoadState, OnLoadState) \
		/** Called when the Url changes. */ \
		SLATE_EVENT(FOnTextChanged, OnUrlChanged) \
		/** Called when the Texture changes. */ \
		/*SLATE_EVENT(FOnTextureChanged, OnTextureChanged) */ \
		/** Called when file download finish. */ \
		SLATE_EVENT(FOnDownloadComplete, OnDownloadComplete) \
		/** Called when resource download finish before load. */ \
		SLATE_EVENT(FOnResourceLoad, OnResourceLoad) \
		/** Called when web has error . */ \
		SLATE_EVENT(FOnWebError, OnWebError) \
		/** Called when web has error . */ \
		SLATE_EVENT(FOnJsStr, OnJsStr) \
		/** Called when web has error . */ \
		SLATE_EVENT(FOnJs, OnJs) \
		 \
		/* this party for params */ \
		/** Control and Editor show text style  */ \
		SLATE_ARGUMENT(FTextBlockStyle, TextStyle) \
		/** Desired size of the web browser viewport. */ \
		SLATE_ARGUMENT(FVector2D, ViewportSize) \
		/** Desired size of the web browser viewport. */ \
		SLATE_ARGUMENT(bool, SwitchInputMethod) \
		/** allow mouse transcparency webpage */ \
		SLATE_ARGUMENT(bool, EnableMouseTransparency) \
		/** URL that the browser will initially navigate to. The URL should include the protocol, eg http:// */ \
		SLATE_ARGUMENT(FString, InitialURL) \
		/** Opaque background color used before a document is loaded and when no document color is specified. */ \
		SLATE_ARGUMENT(FColor, BackgroundColor) \
		/** Whether to show standard controls like Back, Forward, Reload etc. */ \
		SLATE_ARGUMENT(bool, ShowControls) \
		/** Whether to show an address bar. */ \
		SLATE_ARGUMENT(bool, RightKeyPopup) \
		/** Whether to show an address bar. */ \
		SLATE_ARGUMENT(bool, ShowAddressBar) \
		SLATE_ARGUMENT(bool, Touch) \
		SLATE_ARGUMENT(bool, Bridge) \
		/** The frames per second rate that the browser will attempt to use. */ \
		SLATE_ARGUMENT(int, BrowserFrameRate) \
		/** fixed pixel. */ \
		SLATE_ARGUMENT(FIntPoint, Pixel) \
		/** zoom level*/ \
		SLATE_ARGUMENT(float, zoom) \
		/** download show tip */ \
		SLATE_ARGUMENT(bool, downloadTip) \
		SLATE_ARGUMENT(bool, using_json_object) \
		/*SLATE_ARGUMENT(float, zoomlevel)*/ \
	SLATE_END_ARGS() \


class BASEBROWSER_API SBaseBrowser
	: public SCompoundWidget
{
public:

	typedef TMap<FString, FString> RequestHeaders;


	SBaseBrowser();
	virtual ~SBaseBrowser();
	/**
	* Load the specified URL.
	* @param NewURL New URL to load.
	*/
	virtual void LoadURL(FString NewURL, FString PostData = FString(), bool need_response = false);
	virtual void LoadString(FString DummyURL, FString Content);

	/**
		* reopen a new render to replace old render.
		* @param NewURL New URL to load.
		*        if NewURL is empty,will Assign old URL.
		*/
	virtual void ReopenRender(FString NewURL);

	/** Get the current title of the web page. */
	virtual FText GetTitleText() const;

	/** Stop loading the page. */
	virtual void StopLoad();
	/** Reload the current page. */
	virtual void Reload();
	/** Reload the current page. */
	virtual bool Isloaded();
	/** Whether the document is currently being loaded. */
	virtual bool IsLoading() const;
	/** Execute javascript on the current window */
	virtual void ExecuteJavascript(const FString& ScriptText);
	/** Returns true if the browser can navigate backwards. */
	virtual bool CanGoBack() const;
	/** Returns true if the browser can navigate forwards. */
	virtual bool CanGoForward() const;
	/** Navigate backwards. */
	virtual void GoBack();

	virtual bool CallJsonStr(const FString& Function, const FString& Data);
	virtual bool CallJson(const FString& Function, const FMatureJsonValue& Data);

	virtual void PopupURL(const FString& URL);
	/**
	 * Gets the currently loaded URL.
	 * @return The URL, or empty string if no document is loaded.
	 */
	virtual FString GetUrl() const;
	/** Navigate forwards. */
	virtual void GoForward();
	/** Set Page Zoom level */
	virtual void ZoomLevel(float zoomlevel);
	/** Set Page pixel */
	virtual void WebPixel(FIntPoint pixel);
	/** show or hide address bar */
	virtual void ShowAddress(bool isShow);
	/**
	 * Expose a UObject instance to the browser runtime.
	 * Properties and Functions will be accessible from JavaScript side.
	 * As all communication with the rendering procesis asynchronous, return values (both for properties and function results) are wrapped into JS Future objects.
	 * @param Name The name of the object. The object will show up as window.ue4.{Name} on the javascript side. If there is an existing object of the same name, this object will replace it. If bIsPermanent is false and there is an existing permanent binding, the permanent binding will be restored when the temporary one is removed.
	 * @param Object The object instance.
	 * @param bIsPermanent If true, the object will be visible to all pages loaded through this browser widget, otherwise, it will be deleted when navigating away from the current page. Non-permanent bindings should be registered from inside an OnLoadStarted event handler in order to be available before JS code starts loading.
	 */
	virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true);

	/**
	 * Remove an existing script binding registered by BindUObject.
	 * @param Name The name of the object to remove.
	 * @param Object The object will only be removed if it is the same object as the one passed in.
	 * @param bIsPermanent Must match the bIsPermanent argument passed to BindUObject.
	 */
	virtual void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true);
	//
	virtual void StopRender(bool hidden);
	//
	virtual void ShowDevTools();
	//
	virtual void KeyboardMode(WebView_Keyboard_Mode);
	//
	virtual void Close();
	//
	virtual void Silent(bool onoff = true);
	//
	virtual void SetImitateInput(const FImitateInput& ImitateInput);
	//
	virtual void PenetrateThreshold(uint8_t value);
};