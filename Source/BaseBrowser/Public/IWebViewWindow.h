// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/CursorReply.h"
#include "Input/Reply.h"
#include "Widgets/SWindow.h"
#include "Widgets/SViewport.h"
#include "ImitateInput.h"
#include "WebViewEnum.h"
#include "MatureJsonValue.h"
#include "WebViewEvent.h"
#include <memory>

class FWebViewJSScripting;

//using EWebCoreDocumentState = EWebView_DocumentState;
typedef TMap<FString, FString> HtmlHeaders;
/**
 * Interface for dealing with a Web View window
 */
class BASEBROWSER_API IWebViewWindow
{
public:
	/**
	 * Load the specified URL
	 * @param NewURL New URL to load
	 */
	virtual void LoadURL(FString NewURL,FString, bool) = 0;
	virtual void LoadString(FString DummyURL, FString) =0;

	/**
	 * Load a string as data to create a web page
	 * @param Contents String to load
	 * @param DummyURL Dummy URL for the page
	 */
	//virtual void LoadString(FString Contents, FString DummyURL) = 0;

	/**
	 * Set the desired size of the web browser viewport
	 * @param WindowSize Desired viewport size
	 */
	virtual void SetViewportSize(FIntPoint WindowSize, FIntPoint WindowPos = FIntPoint::NoneValue,float geomScale = 1.0f) = 0;

	/**
	* Gets the current size of the web browser viewport if available, FIntPoint::NoneValue otherwise
	* @param WindowSize Desired viewport size
	*/
	virtual FIntPoint GetViewportSize() const = 0;

	/**
	 * Checks whether the web browser is valid and ready for use
	 */
	virtual bool IsValid() const = 0;

	/**
	 * Checks whether the web browser has finished loaded the initial page.
	 */
	virtual bool IsInitialized() const = 0;

	/**
	 * Gets the currently loaded URL.
	 *
	 * @return The URL, or empty string if no document is loaded.
	 */
	virtual FString GetUrl() const = 0;
	virtual FString GetTitle() = 0;

	/**
	 * Notify the browser that a key has been pressed
	 *
	 * @param  InKeyEvent  Key event
	 */
	virtual bool OnKeyDown(const FKeyEvent& InKeyEvent) = 0;

	/**
	 * Notify the browser that a key has been released
	 *
	 * @param  InKeyEvent  Key event
	 */
	virtual bool OnKeyUp(const FKeyEvent& InKeyEvent) = 0;

	/**
	 * Notify the browser of a character event
	 *
	 * @param InCharacterEvent Character event
	 */
	virtual bool OnKeyChar(const FCharacterEvent& InCharacterEvent) = 0;

	/**
	 * Notify the browser that a mouse button was pressed within it
	 *
	 * @param MyGeometry The Geometry of the browser
	 * @param MouseEvent Information about the input event
	 * @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false.
	 *
	 * @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
	 */
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;

	/**
	 * Notify the browser that a mouse button was released within it
	 *
	 * @param MyGeometry The Geometry of the browser
	 * @param MouseEvent Information about the input event
	 * @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false.
	 *
	 * @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
	 */
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;


	virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) ;

	virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) ;

	virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) ;

	virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;

	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) = 0;

	virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;

	/**
	 * The system asks each widget under the mouse to provide a cursor. This event is bubbled.
	 * 
	 * @return FCursorReply::Unhandled() if the event is not handled; return FCursorReply::Cursor() otherwise.
	 */
	virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) ;

	/**
	 * Called when browser receives/loses focus
	 * @param SetFocus Whether the window gained or lost focus.
	 * @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false.
	 */
	virtual void OnFocus(bool SetFocus, bool bIsPopup) = 0;

	/** Called when Capture lost */
	virtual void OnCaptureLost() = 0;

	/**
	 * Returns true if the browser can navigate backwards.
	 */
	virtual bool CanGoBack() const = 0;

	/** Navigate backwards. */
	virtual void GoBack() = 0;

	/**
	 * Returns true if the browser can navigate forwards.
	 */
	virtual bool CanGoForward() const = 0;

	/** Navigate forwards. */
	virtual void GoForward() = 0;

	/**
	 * Returns true if the browser is currently loading.
	 */
	virtual bool IsLoading() const ;

	/** Reload the current page. */
	virtual void Reload() = 0;

	/** Reload the current page. */
	virtual bool Isloaded() ;

	/** Stop loading the page. */
	virtual void StopLoad() = 0;

	/** Execute Javascript on the page. */
	virtual void ExecuteJavascript(const FString& Script) = 0;

	virtual bool CallJsonStr(const FString& Function, const FString& Data) = 0;

	virtual bool CallJson(const FString& Function, const FMatureJsonValue& Json) = 0;

	/** 
	 * Expose a UObject instance to the browser runtime.
	 * Properties and Functions will be accessible from JavaScript side.
	 * As all communication with the rendering procesis asynchronous, return values (both for properties and function results) are wrapped into JS Future objects.
	 * @param Name The name of the object. The object will show up as window.ue4.{Name} on the javascript side. If there is an existing object of the same name, this object will replace it. If bIsPermanent is false and there is an existing permanent binding, the permanent binding will be restored when the temporary one is removed.
	 * @param Object The object instance.
	 * @param bIsPermanent If true, the object will be visible to all pages loaded through this browser widget, otherwise, it will be deleted when navigating away from the current page. Non-permanent bindings should be registered from inside an OnLoadStarted event handler in order to be available before JS code starts loading.
	 */
	virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) = 0;

	/**
	 * Remove an existing script binding registered by BindUObject.
	 * @param Name The name of the object to remove.
	 * @param Object The object will only be removed if it is the same object as the one passed in.
	 * @param bIsPermanent Must match the bIsPermanent argument passed to BindUObject.
	 */
	virtual void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) = 0;

	virtual void SetKeyboardMode(WebView_Keyboard_Mode mode) = 0;

	virtual FWebViewJSScripting* GetJsScripting()=0;
	virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) ;
	virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) ;
	virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) ;
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) ;
	virtual float DPIScaleFactor() = 0;
	virtual void ZoomLevel(float level)=0;
	virtual void WebPixel(FIntPoint pixel) =0;
	virtual void StopRender(bool Visibility) ;
	virtual void ShowDevTools();
	virtual void Silent(bool onoff);
	virtual void Rate(int r);
public:
	webview::FOnWebState& OnWebState();
	webview::FOnTitleChanged& OnTitleChanged();
	webview::FOnUrlChanged& OnUrlChanged();
	webview::FOnChkTrans& OnChkTrans();
	webview::FOnBeforePopupDelegate& OnBeforePopup();
	webview::FOnDownloadComplete& OnDownloadComplete();
	webview::FOnPostResponse& OnPostResponse();
	webview::FOnDragEvent& OnDragEvent();
	webview::FOnRenderCrash& OnRenderCrash();
	webview::FOnResourceLoad& OnResourceLoad();
	webview::FOnNeedsRedraw& OnNeedsRedraw();
	webview::FOnJsStr& OnJsStr();
	webview::FOnJs& OnJs();
	webview::FOnWebError& OnWebError();
protected:

	/** Virtual Destructor. */
	virtual ~IWebViewWindow();
	IWebViewWindow() ;
protected:
	webview::FOnWebState _OnWebState;
	webview::FOnTitleChanged _OnTitleChanged;
	webview::FOnUrlChanged _OnUrlChanged;
	webview::FOnChkTrans _OnChkTrans;
	webview::FOnBeforePopupDelegate _OnBeforePopup;
	webview::FOnDownloadComplete _OnDownloadComplete;
	webview::FOnPostResponse _OnPostResponse;
	webview::FOnDragEvent _OnDragEvent;
	webview::FOnRenderCrash _OnRenderCrash;
	webview::FOnResourceLoad _OnResourceLoad;
	webview::FOnNeedsRedraw _OnNeedsRedraw;
	webview::FOnJsStr _OnJsStr;
	webview::FOnJs _OnJs;
	webview::FOnWebError _OnWebError;
};
