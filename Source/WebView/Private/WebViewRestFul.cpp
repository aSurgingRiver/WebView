
#include "WebViewRestFul.h"

#if defined WEBVIEW_CEF
#include "CefRestFul.h"
#endif

#if PLATFORM_WINDOWS
#endif

UWebViewRestFul::UWebViewRestFul(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	resetful = nullptr;
}

UWebViewRestFul::~UWebViewRestFul() {
	resetful = nullptr;
}

TSharedPtr<IBaseRestFul> UWebViewRestFul::RestFul() {
	if (resetful) return resetful;
#if defined WEBVIEW_CEF 
	resetful = MakeShared<CCefRestFul>();
#else
	resetful = MakeShared<IBaseRestFul>();
#endif
	resetful->OnRestFul().BindUObject(this,&UWebViewRestFul::OnRestFulHandle);
	return resetful;
}

void UWebViewRestFul::BeginDestroy() {
	Super::BeginDestroy();
	if (!resetful)return;
	resetful->BeginDestroy();
}

void UWebViewRestFul::SetMode(WebView_RestFul_Mode Mode) {
	RestFul()->SetMode(Mode);
}

void UWebViewRestFul::Request(const FString& URL, const FMatureJsonValue& PostData) {
	RestFul()->Request(URL, PostData);
}

void UWebViewRestFul::OnRestFulHandle(const FString& url, const FMatureJsonValue& value) {
	if (OnRestFul.IsBound())OnRestFul.Broadcast(url, value);
}
