// Fill out your copyright notice in the Description page of Project Settings.


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

#if CEF_NEW_VERSION
#include "SCefBrowser.h"
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
	//, jsWindow(TEXT("ue"))
{
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

void UWebBase::LoadURL(const FString& NewURL,FString PostData)
{
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->LoadURL(NewURL, PostData);
}

void UWebBase::LoadString(const FString& NewURL, const  FString& Content)
{
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->LoadURL(NewURL, Content);
}

void UWebBase::ExecuteJavascript(const FString& ScriptText)
{
	if (!CefCoreWidget.IsValid())return;
	return CefCoreWidget->ExecuteJavascript(ScriptText);
}

void UWebBase::CallJsonStr(const FString& Function, const FString& Data)
{
	if (!CefCoreWidget.IsValid() || Function.IsEmpty())
		return;
	FString TextScript;
	if (CefCoreWidget->CallJsonStr(Function, Data))return;
	if (Data.Len() >= 2) {
		TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
			*jsWindow, *Function, *Data);
	}
	else {
		TextScript = FString::Printf(TEXT("%s['%s']()"),
			*jsWindow, *Function);
	}
	CefCoreWidget->ExecuteJavascript(TextScript);
}

void UWebBase::CallParams(const FString& Function, const TArray<FString>& Params) {
	if (!CefCoreWidget.IsValid() || Function.IsEmpty())
		return;
	FString strParam;
	for (auto& parm: Params) {
		if (!strParam.IsEmpty())strParam.Append(TEXT(","));
		strParam.Append(TEXT("\'")).Append(parm).Append(TEXT("\'"));
	}
	FString TextScript;
	TextScript = FString::Printf(TEXT("%s['%s'](%s)"),
		*jsWindow, *Function, *strParam);
	CefCoreWidget->ExecuteJavascript(TextScript);
}

FString UWebBase::GetUrl() const {
	if (!CefCoreWidget.IsValid())return FString();
	return CefCoreWidget->GetUrl();
}

/** Reload the current page. */
void UWebBase::Reload() {
	if (!CefCoreWidget.IsValid())return ;
	CefCoreWidget->Reload();
}

bool UWebBase::Isloaded() {
	if (!CefCoreWidget.IsValid())return false;
	return CefCoreWidget->Isloaded();
}

void UWebBase::ZoomLevel(float zoom) const {
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->ZoomLevel(zoom);
}

void UWebBase::Silent(bool onoff) {
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->Silent(onoff);
}

void UWebBase::WebPixel(FIntPoint pixel) const {
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->WebPixel(pixel);
}

void UWebBase::BindUObject(const FString& VarName, UObject* Object, bool bIsPermanent) {
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->BindUObject(VarName, Object, bIsPermanent);
}

void UWebBase::UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent) {
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->UnbindUObject(Name, Object, bIsPermanent);
}

void UWebBase::BeginDestroy() {
	if (CefCoreWidget) {
		CefCoreWidget->SetCanTick(false);
		CefCoreWidget->Close();
		CefCoreWidget.Reset();
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
	CefCoreWidget = SNew(SCefBrowser)
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
//#if !PLATFORM_ANDROID
//		.ImitateInput(ImitateInput)
//#endif
		//.webCursor(webCursor)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.OnUrlChanged_UObject(this, &UWebBase::HandleOnUrlChanged)
		.OnBeforePopup_UObject(this, &UWebBase::HandleOnBeforePopup)
		.OnLoadState_UObject(this, &UWebBase::HandleOnLoadState)
		.OnDownloadComplete_UObject(this, &UWebBase::HandleOnDownloadTip)
		.OnTextureChanged_UObject(this, &UWebBase::HandleOnTextureChanged)
		.OnWebError_UObject(this, &UWebBase::HandleOnWebError)
		.OnResourceLoad_UObject(this, &UWebBase::HandleOnResourceLoad)
		.OnJsStr_UObject(this, &UWebBase::HandleAsyn);
	_ViewObject = NewObject<UWebViewObject>();// 隔离JS和UE4之间的数据。
	if (_ViewObject) {
		_ViewObject->SetUMG(this);
		BindUObject("$receive", _ViewObject);
	}
	CefCoreWidget->KeyboardMode(eKeyboradModeTransparency);
	CefCoreWidget->LoadURL(urlInitial);
	return CefCoreWidget.ToSharedRef();
}

bool UWebBase::Asyn(const FString& Name, FString& Data, const FString& Callback) {
	if (!OnJsEventStr.IsBound())return false;
	OnJsEventStr.Broadcast(Name, Data, Callback);
	return true;
}

void UWebBase::SetVisibility(ESlateVisibility InVisibility) {
	Super::SetVisibility(InVisibility);
	if (!CefCoreWidget.IsValid())return;
	bool isShow = true;
	if (InVisibility == ESlateVisibility::Hidden || InVisibility == ESlateVisibility::Collapsed) {
		isShow = false;
	}
	CefCoreWidget->StopRender(isShow);
}

void UWebBase::HandleOnUrlChanged(const FText& InText) {
	if(OnUrlChanged.IsBound()) OnUrlChanged.Broadcast(InText);
}

void UWebBase::HandleOnLoadState(const int state) {
	if (OnLoadState.IsBound()) OnLoadState.Broadcast(state);
}

void UWebBase::HandleOnTextureChanged(UTexture2D* OLD, UTexture2D* NEW) {
	if (OnTextureChanged.IsBound()) OnTextureChanged.Broadcast(OLD, NEW);
}

bool UWebBase::HandleOnBeforePopup(FString URL, FString Frame) {
	if (!OnBeforePopup.IsBound()) {// 如果没有绑定事件则自动跳转URL
		CefCoreWidget->LoadURL(URL, FString());
		return true;
	}
	OnBeforePopup.Broadcast(URL, Frame);
	return true;
}

void UWebBase::ShowAddress(bool show) {
	if (CefCoreWidget)
	CefCoreWidget->ShowAddress(show);
}

void UWebBase::ReopenRender(FString NewURL) {
	if (CefCoreWidget)
	CefCoreWidget->ReopenRender(NewURL);
}

void UWebBase::ShowDevTools() {
	if (CefCoreWidget)
	CefCoreWidget->ShowDevTools();
}

void UWebBase::HandleOnDownloadTip(FString URL, FString File) {
	if (!OnDownloadComplete.IsBound()) return;
	OnDownloadComplete.Broadcast(URL, File);
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
	if (CefCoreWidget) {
		CefCoreWidget->SetCanTick(false);
		CefCoreWidget->Close();
		CefCoreWidget.Reset();
	}
	if (_ViewObject)_ViewObject = nullptr;
}

void UWebBase::KeyboardMode(WebView_Keyboard_Mode KeyMode) {
	eKeyboradModeTransparency = KeyMode;
	if(CefCoreWidget)
	CefCoreWidget->KeyboardMode(eKeyboradModeTransparency);
}
void UWebBase::GoBack() {
	if (CefCoreWidget)
	CefCoreWidget->GoBack();
}
void UWebBase::GoForward() {
	if (CefCoreWidget)
	CefCoreWidget->GoForward();
}
bool UWebBase::CanGoBack() {
	if (!CefCoreWidget.IsValid())return false;
	return CefCoreWidget->CanGoBack();
}
bool UWebBase::CanGoForward() {
	if (!CefCoreWidget.IsValid())return false;
	return CefCoreWidget->CanGoForward();
}

void UWebBase::SetImitateInput(const FImitateInput* ImitateInput) {
	if (!CefCoreWidget.IsValid())return;
	CefCoreWidget->SetImitateInput(ImitateInput);
}

#undef LOCTEXT_NAMESPACE






