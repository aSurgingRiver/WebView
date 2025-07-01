// Copyright aXiuShen. All Rights Reserved.
#include "BaseBrowser.h"
#include "Misc/ConfigCacheIni.h"
#include "WebViewLog.h"

webview::FOnTransparency SBaseBrowser::OnTransparencyDefault;

SBaseBrowser::SBaseBrowser() {
	FString category(TEXT("ue"));
	FString interface_name(TEXT("interface"));
	GConfig->GetString(TEXT("WebView"), TEXT("category"), category, GGameIni);
	GConfig->GetString(TEXT("WebView"), TEXT("interface_name"), interface_name, GGameIni);
	jsWindow = FString::Printf(TEXT("%s.%s"), *category, *interface_name);
}

SBaseBrowser::~SBaseBrowser() {

}


void SBaseBrowser::LoadURL(FString , FString , bool ) {
}
void SBaseBrowser::LoadString(FString , FString ) {
}

/**
	* reopen a new render to replace old render.
	* @param NewURL New URL to load.
	*        if NewURL is empty,will Assign old URL.
	*/
void SBaseBrowser::ReopenRender(FString ) {
}

/** Get the current title of the web page. */
FText SBaseBrowser::GetTitleText() const {
	return FText();
}

/** Stop loading the page. */
void SBaseBrowser::StopLoad() {
}
/** Reload the current page. */
void SBaseBrowser::Reload() {
}
void SBaseBrowser::ReloadNoCache() {
}
/** Reload the current page. */
bool SBaseBrowser::Isloaded() {
	return false;
}
/** Whether the document is currently being loaded. */
bool SBaseBrowser::IsLoading() const {
	return false;
}
/** Execute javascript on the current window */
void SBaseBrowser::ExecuteJavascript(const FString& ) {
}
/** Returns true if the browser can navigate backwards. */
bool SBaseBrowser::CanGoBack() const {
	return false;
}
/** Returns true if the browser can navigate f
	return false;orwards. */
bool SBaseBrowser::CanGoForward() const {
	return false;
}
/** Navigate backwards. */
void SBaseBrowser::GoBack() {
}

bool SBaseBrowser::CallJsonStr(const FString& Function, const FString& Data) {
	if (Function.IsEmpty())
		return false;
	FString TextScript;
	if (Data.Len() >= 2) {
		TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
			*jsWindow, *Function, *Data);
	}
	else {
		TextScript = FString::Printf(TEXT("%s['%s']()"),
			*jsWindow, *Function);
	}
	ExecuteJavascript(TextScript);
	return true;
}

bool SBaseBrowser::CallJson(const FString& Function, const FMatureJsonValue& Data) {
	if (Function.IsEmpty())
		return false;
	FString TextScript;
	if (!Data.IsEmpty()) {
		TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
			*jsWindow, *Function, *Data.SaveString());
	}
	else {
		TextScript = FString::Printf(TEXT("%s['%s']()"),
			*jsWindow, *Function);
	}
	ExecuteJavascript(TextScript);
	return true;
}

void SBaseBrowser::PopupURL(const FString& ) {
}
/**
 * Gets the currently loaded URL.
 * @return The URL, or empty string if no document is loaded.
 */
FString SBaseBrowser::GetUrl() const {
	return FString();
}
FString SBaseBrowser::GetTitle() const {
	return FString();
}
/** Navigate forwards. */
void SBaseBrowser::GoForward() {
}
/** Set Page Zoom level */
void SBaseBrowser::ZoomLevel(float ) {
}
/** Set Page pixel */
void SBaseBrowser::WebPixel(FIntPoint ) {
}
/** show or hide address bar */
void SBaseBrowser::ShowAddress(bool ) {
}
/**
 * Expose a UObject instance to the browser runtime.
 * Properties and Functions will be accessible from JavaScript side.
 * As all communication with the rendering procesis asynchronous, return values (both for properties and function results) are wrapped into JS Future objects.
 * @param Name The name of the object. The object will show up as window.ue4.{Name} on the javascript side. If there is an existing object of the same name, this object will replace it. If bIsPermanent is false and there is an existing permanent binding, the permanent binding will be restored when the temporary one is removed.
 * @param Object The object instance.
 * @param bIsPermanent If true, the object will be visible to all pages loaded through this browser widget, otherwise, it will be deleted when navigating away from the current page. Non-permanent bindings should be registered from inside an OnLoadStarted event handler in order to be available before JS code starts loading.
 */
void SBaseBrowser::BindUObject(const FString& , UObject* , bool ) {
	UE_LOG(WebViewLog,Error,TEXT("BindUObject,The current platform does not support"));
}

/**
 * Remove an existing script binding registered by BindUObject.
 * @param Name The name of the object to remove.
 * @param Object The object will only be removed if it is the same object as the one passed in.
 * @param bIsPermanent Must match the bIsPermanent argument passed to BindUObject.
 */
void SBaseBrowser::UnbindUObject(const FString& , UObject* , bool ) {
	UE_LOG(WebViewLog, Error, TEXT("UnbindUObject,The current platform does not support"));
}
//
void SBaseBrowser::StopRender(bool ) {
}
//
void SBaseBrowser::ShowDevTools() {
}
//
void SBaseBrowser::KeyboardMode(WebView_Penetrate_Mode) {
}
//
void SBaseBrowser::MouseMode(WebView_Penetrate_Mode) {
}
//
void SBaseBrowser::Close() {
}
//
void SBaseBrowser::Silent(bool  ) {
}
//
void SBaseBrowser::SetImitateInput(const FImitateInput& ) {
	UE_LOG(WebViewLog, Error, TEXT("SBaseBrowser::SetImitateInput,The current platform does not support"));
}
void SBaseBrowser::PenetrateThreshold(uint8_t value) {
}
void SBaseBrowser::FreshTexture(bool) {

}
webview::FOnTransparency& SBaseBrowser::OnTransparency() {
	return OnTransparencyDefault;
}
void SBaseBrowser::MouseTransparency(bool) {

}
void SBaseBrowser::Screen(bool touch){

}
void SBaseBrowser::SetSound(UWebViewSoundComponent* Sound) {
	UE_LOG(WebViewLog, Error, TEXT("SBaseBrowser::SetSound,The current platform does not support"));
}
void SBaseBrowser::CallParams(const FString& Function, const TArray<FString>& Params) {
	if (Function.IsEmpty())
		return;
	FString strParam;
	for (auto& parm : Params) {
		if (!strParam.IsEmpty())strParam.Append(TEXT(","));
		strParam.Append(TEXT("\'")).Append(parm).Append(TEXT("\'"));
	}
	FString TextScript;
	TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
		*jsWindow, *Function, *strParam);
	ExecuteJavascript(TextScript);
}
bool SBaseBrowser::IsInteractable() const {
	return false;
}
