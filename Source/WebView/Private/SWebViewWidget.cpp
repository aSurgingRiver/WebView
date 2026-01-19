// Copyright aXiuShen. All Rights Reserved.

#include "SWebViewWidget.h"
#include "Styling/AppStyle.h"
#include "Misc/ConfigCacheIni.h"
#if defined WEBVIEW_CEF 
#include "SCefBrowser.h"
#elif defined WEBVIEW_ANDROID
#include "SAndroidWeb.h"
#elif defined WEBVIEW_APPLE
#include "AppleBrowser.h"
#else
#include "SProxyWeb.h"
#endif

#define LOCTEXT_NAMESPACE "SWebViewWidget"

SWebViewWidget::SWebViewWidget(){
	SetCanTick(true);
}

SWebViewWidget::~SWebViewWidget() {
}

void SWebViewWidget::Construct(const FArguments& InArgs)
{
#if defined USING_WEBBROWSER
	using SBrowserImp = SProxyWeb;
#elif defined WEBVIEW_CEF
	using SBrowserImp = SCefBrowser;
#elif defined WEBVIEW_ANDROID
	using SBrowserImp = SAndroidWeb;
#elif defined WEBVIEW_APPLE
	typedef SAppleBrowser SBrowserImp;
#else
	using SBrowserImp = SProxyWeb;
#endif
	m_OnUrlChanged = InArgs._OnUrlChanged;
	m_browser = SNew(SBrowserImp)
		.ShowAddressBar(true)
		.BackgroundColor(FColor(255,255,255,255))
		.ShowControls(true)
		.RightKeyPopup(false)
		.BrowserFrameRate(30)
		.TextStyle(FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))
		.EnableMouseTransparency(InArgs._EnableMouseTransparency)
		.SwitchInputMethod(true)
		.ViewportSize(GetDesiredSize())
		.Pixel( FIntPoint( 8,4))
		.zoom(1.0)
		.Touch(true)
		.downloadTip(true)
		.using_json_object(true)
		.Visibility(EVisibility::Visible)
		.OnUrlChanged_Raw(this,&SWebViewWidget::HandleOnUrlChanged)
		.OnBeforePopup_Raw(this, &SWebViewWidget::HandleOnBeforePopup)
		.OnPostResponse(InArgs._OnPostResponse)
		.OnWebError(InArgs._OnWebError)
		.OnResourceLoad(InArgs._OnResourceLoad)
		.OnTitleChanged_Raw(this, &SWebViewWidget::HandleOnTitleChanged)
		.OnJsStr(InArgs._OnJsStr)
		.OnJs(InArgs._OnJs)
		.OnJsBegin(InArgs._OnJsBegin)
		.OnLoadState(InArgs._OnLoadState)
		.OnTexture(InArgs._OnTexture)
		.OnDownloadComplete(InArgs._OnDownloadComplete);
	FString editor_url = TEXT("https://weixin.qq.com/");
	GConfig->GetString(TEXT("WebView"), TEXT("editor_url"), editor_url, GGameIni);
	m_browser->LoadURL(editor_url);
	ChildSlot[
		m_browser.ToSharedRef()
	];
}

void SWebViewWidget::LoadURL(FString NewURL, FString PostData, bool need_response)
{
	if (m_browser)m_browser->LoadURL(NewURL, PostData, need_response);
}

void SWebViewWidget::LoadString(FString NewURL, FString Content)
{
	if (m_browser)m_browser->LoadString(NewURL, Content);
}

void SWebViewWidget::ReopenRender(FString NewURL) {
	if (m_browser)m_browser->ReopenRender(NewURL);
}

void SWebViewWidget::Reload()
{
	if (m_browser)m_browser->Reload();
}

void SWebViewWidget::ReloadNoCache()
{
	if (m_browser)m_browser->ReloadNoCache();
}

/** Reload the current page. */
bool SWebViewWidget::Isloaded() {
	if (m_browser)return m_browser->Isloaded();
	return false;
}

void SWebViewWidget::StopLoad(){
	if (m_browser)m_browser->StopLoad();
}

FText SWebViewWidget::GetTitleText() const {
	if (m_browser)return m_browser->GetTitleText();
	return FText();
}

FString SWebViewWidget::GetUrl() const
{
	if (m_browser)return m_browser->GetUrl();
	return FString();
}

FString SWebViewWidget::GetTitle() const
{
	if (m_browser)return m_browser->GetTitle();
	return FString();
}
bool SWebViewWidget::IsLoading() const
{
	if (m_browser)return m_browser->IsLoading();
	return false;
}

bool SWebViewWidget::CanGoBack() const
{
	if (m_browser)return m_browser->CanGoBack();
	return false;
}

void SWebViewWidget::GoBack()
{
	if (m_browser)m_browser->GoBack();
}


bool SWebViewWidget::CanGoForward() const {
	if (m_browser)return m_browser->CanGoForward();
	return false;
}

void SWebViewWidget::GoForward() {
	if (m_browser)m_browser->GoForward();
}

void SWebViewWidget::ZoomLevel(float zoomlevel) {
	if (m_browser)m_browser->ZoomLevel(zoomlevel);
}

void SWebViewWidget::WebPixel(FIntPoint pixel) {
	if (m_browser)m_browser->WebPixel(pixel);
}

void SWebViewWidget::ExecuteJavascript(const FString& ScriptText){
	if (m_browser)m_browser->ExecuteJavascript(ScriptText);
}

bool SWebViewWidget::CallJsonStr(const FString& Function, const FString& Data) {
	if (m_browser)return m_browser->CallJsonStr(Function, Data);
	return false;
}

bool SWebViewWidget::CallJson(const FString& Function, const FMatureJsonValue& Data) {
	if (m_browser)return m_browser->CallJson(Function, Data);
	return false;
}

void SWebViewWidget::BindUObject(const FString& Name, UObject* Object, bool bIsPermanent){
	if (m_browser)m_browser->BindUObject(Name, Object, bIsPermanent);
}

void SWebViewWidget::UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent){
	if (m_browser)m_browser->UnbindUObject(Name, Object, bIsPermanent);
}

void SWebViewWidget::StopRender(bool hidden) {
	if (m_browser)m_browser->StopRender(hidden);
}


void SWebViewWidget::ShowDevTools() {
	if (m_browser)m_browser->ShowDevTools();
}

void SWebViewWidget::Silent(bool onoff) {
	if (m_browser)m_browser->Silent(onoff);
}

void SWebViewWidget::PopupURL(const FString& URL) {
	if (m_browser)m_browser->PopupURL(URL);
}

void SWebViewWidget::ShowAddress(bool isShow) {
	if (m_browser)m_browser->ShowAddress(isShow);
}


//
void SWebViewWidget::KeyboardMode(WebView_Penetrate_Mode mode) {
	if (m_browser)m_browser->KeyboardMode(mode);
}

//
void SWebViewWidget::MouseMode(WebView_Penetrate_Mode mode) {
	if (m_browser)m_browser->MouseMode(mode);
}
//
void SWebViewWidget::Close() {
	if (m_browser)m_browser->Close();
}
//

void SWebViewWidget::SetImitateInput(const FImitateInput& Input) {
	if (m_browser)m_browser->SetImitateInput(Input);
}


void SWebViewWidget::PenetrateThreshold(uint8_t value) {
	if (m_browser)m_browser->PenetrateThreshold(value);
}

void SWebViewWidget::FreshTexture(bool yes) {
	if (m_browser)m_browser->FreshTexture(yes);
}
webview::FOnTransparency& SWebViewWidget::OnTransparency() {
	if (m_browser)return m_browser->OnTransparency();
	return SBaseBrowser::OnTransparency();
}

void SWebViewWidget::MouseTransparency(bool yes) {
	if (m_browser)m_browser->MouseTransparency(yes);
}
void SWebViewWidget::Screen(bool touch) {
	if (m_browser)m_browser->Screen(touch);
}
void SWebViewWidget::SetSound(UWebViewSoundComponent* Sound) {
	if (m_browser)m_browser->SetSound(Sound);
}

void SWebViewWidget::HandleOnUrlChanged(const FString& Text) {
	auto docktab = m_docktab.Pin();
	if (docktab) {
		auto title = GetTitle();
		if (!title.IsEmpty()) {
			docktab->SetLabel(FText::FromString(title));
		}
	}
	m_OnUrlChanged.ExecuteIfBound(Text);
}

void SWebViewWidget::HandleOnTitleChanged(FString title) {
	auto docktab = m_docktab.Pin();
	if (title.IsEmpty()) {
		title = GetUrl();
	}
	if (docktab) {
		docktab->SetLabel(FText::FromString(title));
	}
}

bool SWebViewWidget::HandleOnBeforePopup(FString URL, FString Frame) {
	LoadURL(URL);
	return true;
}

void SWebViewWidget::SetDockTab(TWeakPtr<SDockTab> docktab) {
	m_docktab = docktab;
}

#undef LOCTEXT_NAMESPACE


//#endif