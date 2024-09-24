// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/SlateDelegates.h"
#include "Styling/SlateTypes.h"
#include "Widgets/Text/STextBlock.h"
#include "BaseBrowser.h"
#ifdef USING_WEBBROWSER

class SWebBrowserView;
class IWebBrowserWindow;
class SProxyWeb
	: public SBaseBrowser
{
public:
	BASEBROWSER_PARAMS(SProxyWeb)

	/**
		* Load the specified URL.
		* @param NewURL New URL to load.
		*/
	virtual void LoadURL(FString NewURL) override;

	virtual void LoadString(FString NewURL,FString content) override;

	/**
		* reopen a new render to replace old render.
		* @param NewURL New URL to load.
		*        if NewURL is empty,will Assign old URL.
		*/
	virtual void ReopenRender(FString NewURL) override;

	/** Get the current title of the web page. */
	virtual FText GetTitleText() const override;

	/** Stop loading the page. */
	virtual void StopLoad() override;
	/** Reload the current page. */
	virtual void Reload() override;
	/** Whether the document is currently being loaded. */
	virtual bool IsLoading() const override;
	/** Execute javascript on the current window */
	virtual void ExecuteJavascript(const FString& ScriptText) override;
	/** Returns true if the browser can navigate backwards. */
	virtual bool CanGoBack() const override;
	/** Returns true if the browser can navigate forwards. */
	virtual bool CanGoForward() const override;
	/** Navigate backwards. */
	virtual void GoBack() override;
	/**
	 * Gets the currently loaded URL.
	 * @return The URL, or empty string if no document is loaded.
	 */
	virtual FString GetUrl() const override;
	/** Navigate forwards. */
	virtual void GoForward() override;
	/** Set Page Zoom level */
	virtual void ZoomLevel(float zoomlevel) override;
	/** Set Page pixel */
	virtual void WebPixel(FIntPoint pixel) override;
	/** show or hide address bar */
	virtual void ShowAddress(bool isShow) override;
	/**
	 * Expose a UObject instance to the browser runtime.
	 * Properties and Functions will be accessible from JavaScript side.
	 * As all communication with the rendering procesis asynchronous, return values (both for properties and function results) are wrapped into JS Future objects.
	 * @param Name The name of the object. The object will show up as window.ue4.{Name} on the javascript side. If there is an existing object of the same name, this object will replace it. If bIsPermanent is false and there is an existing permanent binding, the permanent binding will be restored when the temporary one is removed.
	 * @param Object The object instance.
	 * @param bIsPermanent If true, the object will be visible to all pages loaded through this browser widget, otherwise, it will be deleted when navigating away from the current page. Non-permanent bindings should be registered from inside an OnLoadStarted event handler in order to be available before JS code starts loading.
	 */
	virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;

	/**
	 * Remove an existing script binding registered by BindUObject.
	 * @param Name The name of the object to remove.
	 * @param Object The object will only be removed if it is the same object as the one passed in.
	 * @param bIsPermanent Must match the bIsPermanent argument passed to BindUObject.
	 */
	virtual void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;
	//virtual bool SupportsKeyboardFocus() const override { return true; }
public:
	/** Default constructor. */
	SProxyWeb();
	~SProxyWeb();
	/**
	 * Construct the widget.
	 * @param InArgs  Declaration from which to construct the widget.
	 */
	void Construct(const FArguments& InArgs);
private:
	// 
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);
	virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)override;
	EVisibility GetViewportVisibility() const;
	bool ReadTexturePixel(FVector2D& LocalUV, FColor& MousePixel);

	FString dns_to_local(FString url)const;
	FString local_to_dns(FString url)const;
private:
	TSharedPtr<SWebBrowserView>   BrowserView;
	TSharedPtr<IWebBrowserWindow> BrowserWindow;

	bool  bMouseTransparency;
	uint8 TransparencyThreadshold;
	FColor LastMousePixel;
	float        sumDelay;
	int32        preMouseX;
	int32        preMouseY;
	FString      local_domain;
	const FString local_dns;
//#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
//	TMap<TWeakPtr<IWebBrowserWindow>, TWeakPtr<SWindow>> BrowserWindowWidgets;
//#endif
};

#endif