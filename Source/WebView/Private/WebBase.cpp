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

#if defined WEBVIEW_CEF
#include "SCefBrowser.h"
#elif defined WEBVIEW_ANDROID
#include "SAndroidWeb.h"
#else
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
{
	stop_render = false;
	WebWidget = nullptr;
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
	json_object = false;
	eKeyboradModeTransparency = WebView_Keyboard_Mode::WebView_Keyboard_Mode_Blend;
}

void UWebBase::LoadURL(const FString& NewURL,FString PostData, bool need_response)
{
	if (WebWidget)WebWidget->LoadURL(NewURL, PostData, need_response);
}

void UWebBase::LoadString(const FString& NewURL, const  FString& Content)
{
	if (WebWidget)WebWidget->LoadString(NewURL, Content);
}

void UWebBase::ExecuteJavascript(const FString& ScriptText)
{
	if (WebWidget)WebWidget->ExecuteJavascript(ScriptText);
}

void UWebBase::CallJsonStr(const FString& Function, const FString& Data)
{
	if (Function.IsEmpty())
		return;
	FString TextScript;
	if (!WebWidget || WebWidget->CallJsonStr(Function, Data))return;
	if (Data.Len() >= 2) {
		TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
			*jsWindow, *Function, *Data);
	}
	else {
		TextScript = FString::Printf(TEXT("%s['%s']()"),
			*jsWindow, *Function);
	}
	if(WebWidget)WebWidget->ExecuteJavascript(TextScript);
}


void UWebBase::CallJson(const FString& Function, FMatureJsonValue Data)
{
	if (Function.IsEmpty())
		return;
	FString TextScript;
	if (!WebWidget || WebWidget->CallJson(Function, Data))return;
	if (!Data.IsEmpty()) {
		TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
			*jsWindow, *Function, *Data.SaveString());
	}
	else {
		TextScript = FString::Printf(TEXT("%s['%s']()"),
			*jsWindow, *Function);
	}
	if (WebWidget)WebWidget->ExecuteJavascript(TextScript);
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
	if (WebWidget)WebWidget->ExecuteJavascript(TextScript);
}

FString UWebBase::GetUrl() const {
	if (WebWidget)WebWidget->GetUrl();
	return FString();
}

/** Reload the current page. */
void UWebBase::Reload() {
	if (WebWidget)WebWidget->Reload();
}

bool UWebBase::Isloaded() {
	if (WebWidget)return WebWidget->Isloaded();
	return true;
}

void UWebBase::ZoomLevel(float zoom) const {
	if (WebWidget)WebWidget->ZoomLevel(zoom);
}

void UWebBase::Silent(bool onoff) {
	if (WebWidget)WebWidget->Silent(onoff);
}

void UWebBase::WebPixel(FIntPoint pixel) const {
	if (WebWidget)WebWidget->WebPixel(pixel);
}

void UWebBase::BindUObject(const FString& VarName, UObject* Object, bool bIsPermanent) {
	if (WebWidget)WebWidget->BindUObject(VarName, Object, bIsPermanent);
}

void UWebBase::UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent) {
	if (WebWidget)WebWidget->UnbindUObject(Name, Object, bIsPermanent);
}

void UWebBase::BeginDestroy() {
	if (WebWidget) {
		WebWidget->Close();
		WebWidget->SetCanTick(false);
		WebWidget.Reset();
	}
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
#if defined WEBVIEW_CEF
	using SBrowserImp = SCefBrowser;
#elif defined WEBVIEW_ANDROID
	using SBrowserImp = SAndroidWeb;
#else
	using SBrowserImp = SProxyWeb;
#endif

//#ifdef WEBVIEW_CEF
	auto WebWidgetImp = SNew(SBrowserImp)
		.ShowAddressBar(addressShow)
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
		.using_json_object(json_object)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.OnUrlChanged_UObject(this, &UWebBase::HandleOnUrlChanged)
		.OnBeforePopup_UObject(this, &UWebBase::HandleOnBeforePopup)
		.OnPostResponse_UObject(this, &UWebBase::HandleOnPostResponse)
		.OnWebError_UObject(this, &UWebBase::HandleOnWebError)
		.OnResourceLoad_UObject(this, &UWebBase::HandleOnResourceLoad)
		.OnJsStr_UObject(this, &UWebBase::HandleAsyn)
		.OnJs_UObject(this, &UWebBase::HandleAsynJson)
		.OnLoadState_UObject(this, &UWebBase::HandleOnLoadState)
		.OnTexture_UObject(this, &UWebBase::HandleOnTexture)
		.OnDownloadComplete_UObject(this, &UWebBase::HandleOnDownloadTip);
//#else 
//	auto WebWidgetImp = SNew(SProxyWeb)
//		.ShowAddressBar(addressShow)
//		.BackgroundColor(ColorBackground)
//		.ShowControls(controlShow)
//		.RightKeyPopup(RightKeyPopup)
//		.BrowserFrameRate(RateFrame)
//		.TextStyle(styleText)
//		.EnableMouseTransparency(bEnableMouseTransparency)
//		.SwitchInputMethod(SwitchInputMethod)
//		.ViewportSize(GetDesiredSize())
//		.Pixel(_Pixel)
//		.zoom(_Zoom)
//		.downloadTip(downloadTip)
//		.Visibility(EVisibility::SelfHitTestInvisible)
//		.OnUrlChanged_UObject(this, &UWebBase::HandleOnUrlChanged)
//		.OnBeforePopup_UObject(this, &UWebBase::HandleOnBeforePopup)
//		.OnLoadState_UObject(this, &UWebBase::HandleOnLoadState)
//		.OnDownloadComplete_UObject(this, &UWebBase::HandleOnDownloadTip);
//#endif
	WebWidget = WebWidgetImp;
	_ViewObject = NewObject<UWebViewObject>();// 隔离JS和UE4之间的数据。
	if (_ViewObject) {
		_ViewObject->SetJsonObject(json_object);
		_ViewObject->SetUMG(this);
		BindUObject("$receive", _ViewObject);
	}
	WebWidget->FreshTexture(OnTexture.IsBound());
	WebWidget->LoadURL(urlInitial);
	return WebWidget.ToSharedRef();
}

bool UWebBase::Asyn(const FString& Name, FString& Data, const FString& Callback) {
	if (!OnJsEventStr.IsBound())return false;
	OnJsEventStr.Broadcast(Name, Data, Callback);
	return true;
}

bool UWebBase::Asyn(const FString& Name, FMatureJsonValue& json, const FString& Callback) {
	if (!OnJsEventStr.IsBound())return false;
	OnJsEvent.Broadcast(Name, json, Callback);
	return true;
}

void UWebBase::StopRender(bool hidden) {
	stop_render = hidden;
	if(WebWidget)WebWidget->StopRender(hidden);
}

void UWebBase::Penetrate(int Threshold) {
	if (WebWidget)WebWidget->PenetrateThreshold(FMath::Clamp(Threshold,0,255));
}

void UWebBase::HandleOnUrlChanged(const FString& InText) {
	if(OnUrlChanged.IsBound()) OnUrlChanged.Broadcast(FText::FromString(InText));
}
void UWebBase::HandleOnTexture(UTexture* texture) {
	if (OnTexture.IsBound()) OnTexture.Broadcast(texture);
}

void UWebBase::HandleOnLoadState(const EWebView_DocumentState state) {
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
	if (WebWidget)WebWidget->ShowAddress(show);
}

void UWebBase::ReopenRender(FString NewURL) {
	if (WebWidget)WebWidget->ReopenRender(NewURL);
}

void UWebBase::ShowDevTools() {
	if (WebWidget)WebWidget->ShowDevTools();
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

void UWebBase::HandleAsynJson(const FString& Name, const FMatureJsonValue& json, const FString& Callback) {
	//FString Json = Data;
	FMatureJsonValue bpjson = json;
	Asyn(Name, bpjson, Callback);
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
	if (stop_render)return;
	if (WebWidget) {
		WebWidget->StopRender(false);
		WebWidget->Close();
	}
	if (_ViewObject)_ViewObject = nullptr;
}

void UWebBase::KeyboardMode(WebView_Keyboard_Mode KeyMode) {
	if (WebWidget)WebWidget->KeyboardMode(KeyMode);
}
void UWebBase::GoBack() {
	if (WebWidget)WebWidget->GoBack();
}
void UWebBase::GoForward() {
	if (WebWidget)WebWidget->GoForward();
}
bool UWebBase::CanGoBack() {
	if (WebWidget)return WebWidget->CanGoBack();
	return false;
}

bool UWebBase::CanGoForward() {
	if (WebWidget)return WebWidget->CanGoForward();
	return false;
}

void UWebBase::SetImitateInput(const FImitateInput& ImitateInput) {
	if (WebWidget)WebWidget->SetImitateInput(ImitateInput);
}

void UWebBase::FreshTexture(bool yes) {
	if (WebWidget)WebWidget->FreshTexture(yes);
}

#undef LOCTEXT_NAMESPACE






