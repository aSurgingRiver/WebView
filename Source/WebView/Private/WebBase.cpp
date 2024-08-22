// Copyright aXiuShen. All Rights Reserved.

#include "WebBase.h"
#include "Async/Async.h"
#include "WebViewObject.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Async/TaskGraphInterfaces.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/ConfigCacheIni.h"
#if WITH_EDITOR
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialExpressionMaterialFunctionCall.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Materials/MaterialFunction.h"
#include "Factories/MaterialFactoryNew.h"
//#include "AssetRegistryModule.h"
#include "PackageHelperFunctions.h"
#endif
#include "cefcorelib.h"

#ifdef WEBVIEW_CUSTOMIZED_CORE
#include "SCefBrowser.h"
#endif
#ifdef USING_WEBBROWSER
#include "SProxyWeb.h"
#endif

#define LOCTEXT_NAMESPACE "WebBase"


/////////////////////////////////////////////////////
// UWebBase

void UHtmlHeaders::ExistAppend(const FString& Key, const FString& Value) {
	if (!Headers.Contains(Key))return;
	FString &V= Headers[Key];
	V = V + TEXT(" ") +Value;
}

void UHtmlHeaders::Replace(const FString& Key, const FString& Value) {
	if (!Headers.Contains(Key)) {
		Headers.Add(Key, Value);
		return;
	}
	Headers[Key] = Value;
}

UWebBase::UWebBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, styleText(FTextBlockStyle::GetDefault())
	, ColorBackground(255, 255, 255, 254)
	, _Pixel(8, 4)
	, _Zoom(1.0f)
	//, jsWindow(TEXT("ue"))
{
	CefWidget = nullptr;
	ProxyWidget = nullptr;
	WebWidget = nullptr;
	_Touch = false;
	bIsVariable = true;
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	FString category(TEXT("ue"));
	FString object(TEXT("interface"));
	GConfig->GetString(TEXT("WebView"), TEXT("category"), category, GGameIni);
	GConfig->GetString(TEXT("WebView"), TEXT("object"), object, GGameIni);
	jsWindow = FString::Printf(TEXT("%s.%s"),*category,*object);
	styleText.ColorAndOpacity = FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f));
	styleText.Font.Size = 20;
	bIsVariable = true;
	eKeyboradModeTransparency = WebView_Keyboard_Mode::WebView_Keyboard_Mode_Blend;
}

void UWebBase::LoadURL(const FString& NewURL,FString PostData, bool need_response)
{
#ifdef USING_WEBBROWSER
	if (ProxyWidget)ProxyWidget->LoadURL(NewURL);
#else
	if (CefWidget)CefWidget->LoadURL(NewURL, PostData, need_response);
#endif
}

void UWebBase::LoadString(const FString& NewURL, const  FString& Content)
{
#ifdef USING_WEBBROWSER
	if (ProxyWidget)ProxyWidget->LoadString(NewURL, Content);
#else
	if (CefWidget)CefWidget->LoadString(NewURL, Content);
#endif
}

void UWebBase::ExecuteJavascript(const FString& ScriptText)
{
#ifdef USING_WEBBROWSER
	if (ProxyWidget)ProxyWidget->ExecuteJavascript(ScriptText);
#else
	if (CefWidget)CefWidget->ExecuteJavascript(ScriptText);
#endif
}

void UWebBase::CallJsonStr(const FString& Function, const FString& Data)
{
	if (Function.IsEmpty())
		return;
	FString TextScript;
#ifndef USING_WEBBROWSER
	if (!CefWidget || CefWidget->CallJsonStr(Function, Data))return;
#endif
	if (Data.Len() >= 2) {
		TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
			*jsWindow, *Function, *Data);
	}
	else {
		TextScript = FString::Printf(TEXT("%s['%s']()"),
			*jsWindow, *Function);
	}
#ifdef USING_WEBBROWSER
	if(ProxyWidget)ProxyWidget->ExecuteJavascript(TextScript);
#else
	if(CefWidget)CefWidget->ExecuteJavascript(TextScript);
#endif
}

void UWebBase::CallParams(const FString& Function, const TArray<FString>& Params) {
	if (Function.IsEmpty())
		return;
	FString strParam;
	for (auto& parm: Params) {
		if (!strParam.IsEmpty())strParam.Append(TEXT(","));
		strParam.Append(TEXT("\'")).Append(parm).Append(TEXT("\'"));
	}
	FString TextScript;
	TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
		*jsWindow, *Function, *strParam);
#ifdef USING_WEBBROWSER
	if (ProxyWidget)ProxyWidget->ExecuteJavascript(TextScript);
#else
	if (CefWidget)CefWidget->ExecuteJavascript(TextScript);
#endif
}

FString UWebBase::GetUrl() const {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->GetUrl();
#endif
	return FString();
}

/** Reload the current page. */
void UWebBase::Reload() {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->Reload();
#endif
}

bool UWebBase::Isloaded() {
#ifndef USING_WEBBROWSER
	if (CefWidget)return CefWidget->Isloaded();
#endif
	return true;
}

void UWebBase::ZoomLevel(float zoom) const {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->ZoomLevel(zoom);
#endif
}

void UWebBase::Silent(bool onoff) {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->Silent(onoff);
#endif
}

void UWebBase::WebPixel(FIntPoint pixel) const {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->WebPixel(pixel);
#endif
}

void UWebBase::BindUObject(const FString& VarName, UObject* Object, bool bIsPermanent) {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->BindUObject(VarName, Object, bIsPermanent);
#else 
	if (ProxyWidget)ProxyWidget->BindUObject(VarName, Object, bIsPermanent);
#endif
}

void UWebBase::UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent) {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->UnbindUObject(Name, Object, bIsPermanent);
#else 
	if (ProxyWidget)ProxyWidget->UnbindUObject(Name, Object, bIsPermanent);
#endif
}

void UWebBase::BeginDestroy() {
#ifndef USING_WEBBROWSER
	if (CefWidget) {
		CefWidget->Close();
		CefWidget->SetCanTick(false);
		CefWidget.Reset();
	}
#else 
	if (ProxyWidget) {
		ProxyWidget->SetCanTick(false);
		ProxyWidget.Reset();
	}
#endif
	CefWidget.Reset();
	Super::BeginDestroy();
}

TSharedRef<SWidget> UWebBase::RebuildWidget() {
	if (IsDesignTime() || IsDefaultSubobject()) {
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("WebView", "WebView"))
			];
	}
	if (OnPreReBuild.IsBound())OnPreReBuild.Broadcast();
#ifndef USING_WEBBROWSER
	CefWidget = SNew(SCefBrowser)
		.ShowAddressBar(addressShow)
		//.InitialURL(urlInitial)
		.BackgroundColor(ColorBackground)
		.ShowControls(controlShow)
		.RightKeyPopup(RightKeyPopup)
		.BrowserFrameRate(RateFrame)
		.TextStyle(styleText)
		.EnableMouseTransparency(bEnableMouseTransparency)
		.SwitchInputMethod(SwitchInputMethod)
		.ViewportSize(GetDesiredSize())
		.Pixel(_Pixel)
		.zoom(_Zoom)
		.Touch(_Touch)
		.downloadTip(downloadTip)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.OnUrlChanged_UObject(this, &UWebBase::HandleOnUrlChanged)
		.OnBeforePopup_UObject(this, &UWebBase::HandleOnBeforePopup)
		.OnPostResponse_UObject(this, &UWebBase::HandleOnPostResponse)
		.OnWebError_UObject(this, &UWebBase::HandleOnWebError)
		.OnResourceLoad_UObject(this, &UWebBase::HandleOnResourceLoad)
		.OnJsStr_UObject(this, &UWebBase::HandleAsyn)
		.OnLoadState_UObject(this, &UWebBase::HandleOnLoadState)
		.OnDownloadComplete_UObject(this, &UWebBase::HandleOnDownloadTip);
	CefWidget->KeyboardMode(webview::toInner(eKeyboradModeTransparency));
	WebWidget = CefWidget;
#else 
	ProxyWidget = SNew(SProxyWeb)
		.ShowAddressBar(addressShow)
		//.InitialURL(urlInitial)
		.BackgroundColor(ColorBackground)
		.ShowControls(controlShow)
		.RightKeyPopup(RightKeyPopup)
		.BrowserFrameRate(RateFrame)
		.TextStyle(styleText)
		.EnableMouseTransparency(bEnableMouseTransparency)
		.SwitchInputMethod(SwitchInputMethod)
		.ViewportSize(GetDesiredSize())
		.Pixel(_Pixel)
		.zoom(_Zoom)
		.downloadTip(downloadTip)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.OnUrlChanged_UObject(this, &UWebBase::HandleOnUrlChanged)
		.OnBeforePopup_UObject(this, &UWebBase::HandleOnBeforePopup)
		.OnLoadState_UObject(this, &UWebBase::HandleOnLoadState)
		.OnDownloadComplete_UObject(this, &UWebBase::HandleOnDownloadTip);
	WebWidget = ProxyWidget;
#endif
	_ViewObject = NewObject<UWebViewObject>();// 隔离JS和UE4之间的数据。
	if (_ViewObject) {
		_ViewObject->SetUMG(this);
		BindUObject("$receive", _ViewObject);
	}
#ifndef USING_WEBBROWSER
	CefWidget->LoadURL(urlInitial);
#else 
	ProxyWidget->LoadURL(urlInitial);
#endif
	return WebWidget.ToSharedRef();
}

bool UWebBase::Asyn(const FString& Name, FString& Data, const FString& Callback) {
	if (!OnJsEventStr.IsBound())return false;
	OnJsEventStr.Broadcast(Name, Data, Callback);
	return true;
}

void UWebBase::StopRender(bool hidden) {
#ifndef USING_WEBBROWSER
	if(CefWidget)CefWidget->StopRender(hidden);
#endif
}

void UWebBase::HandleOnUrlChanged(const FText& InText) {
	if(OnUrlChanged.IsBound()) OnUrlChanged.Broadcast(InText);
}

void UWebBase::HandleOnLoadState(const int state) {
	if (OnLoadState.IsBound()) OnLoadState.Broadcast(state);
}

bool UWebBase::HandleOnBeforePopup(FString URL, FString Frame) {
	if (!OnBeforePopup.IsBound()) {// 如果没有绑定事件则自动跳转URL
		LoadURL(URL);
		return true;
	}
	OnBeforePopup.Broadcast(URL, Frame);
	return true;
}

void UWebBase::ShowAddress(bool show) {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->ShowAddress(show);
#endif
}

void UWebBase::ReopenRender(FString NewURL) {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->ReopenRender(NewURL);
#endif
}

void UWebBase::ShowDevTools() {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->ShowDevTools();
#endif
}

void UWebBase::HandleOnDownloadTip(FString URL, FString File) {
	if (!OnDownloadComplete.IsBound()) return;
	OnDownloadComplete.Broadcast(URL, File);
}

void UWebBase::HandleOnPostResponse(const FString& URL, const FString& PostResponse) {
	if (!OnPostResponse.IsBound()) return;
	OnPostResponse.Broadcast(URL, PostResponse);
}

void UWebBase::HandleOnWebError(const FString& Url, const FString& Desc, const FString& Source, const int line) {
	if (!OnWebError.IsBound()) return;
	OnWebError.Broadcast(Desc, Source, line);
}

void UWebBase::HandleAsyn(const FString& Name, const FString& Data, const FString& Callback) {
	FString Json = Data;
	Asyn(Name, Json, Callback);
}

bool UWebBase::HandleOnResourceLoad(FString URL, int ResourceType, TMap<FString, FString>& HtmlHeaders) {
	if (!OnBeforeRequest.IsBound()) return false;
	UHtmlHeaders* Headers = NewObject<UHtmlHeaders>(this);
	Headers->Headers = HtmlHeaders;
	OnBeforeRequest.Broadcast(URL, ResourceType, Headers);
	HtmlHeaders = Headers->Headers;
	return true;
}
void UWebBase::ReleaseSlateResources(bool bReleaseChildren) {

#ifndef USING_WEBBROWSER
	if (CefWidget) {
		CefWidget->StopRender(false);
		CefWidget->Close();
	}
#endif
	WebWidget.Reset();
	if (_ViewObject)_ViewObject = nullptr;
}

void UWebBase::KeyboardMode(WebView_Keyboard_Mode KeyMode) {
	eKeyboradModeTransparency = KeyMode;
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->KeyboardMode(webview::toInner(eKeyboradModeTransparency));
#endif
}
void UWebBase::GoBack() {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->GoBack();
#else
	if (ProxyWidget)ProxyWidget->GoBack();
#endif
}
void UWebBase::GoForward() {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->GoForward();
#else
	if (ProxyWidget)ProxyWidget->GoForward();
#endif
}
bool UWebBase::CanGoBack() {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->CanGoBack();
#else
	if (ProxyWidget)ProxyWidget->CanGoBack();
#endif
	return false;
}

bool UWebBase::CanGoForward() {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->CanGoForward();
#else
	if (ProxyWidget)ProxyWidget->CanGoForward();
#endif
	return false;
}

void UWebBase::SetImitateInput(const FImitateInput& ImitateInput) {
#ifndef USING_WEBBROWSER
	if (CefWidget)CefWidget->SetImitateInput(webview::toInner(ImitateInput));
#endif
}

#undef LOCTEXT_NAMESPACE






