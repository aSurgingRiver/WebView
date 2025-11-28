
#include "BaseRestFul.h"
#include "WebViewLog.h"

IBaseRestFul::IBaseRestFul() {
	Mode = WebView_RestFul_Mode::WebView_RestFul_Mode_Post;
}

IBaseRestFul::~IBaseRestFul() {
}


void IBaseRestFul::Request(const FString& URL, const FMatureJsonValue& Data) {
	UE_LOG(WebViewLog,Log,TEXT("IBaseRestFul::Request trigered!"));
} 

void IBaseRestFul::SetMode(WebView_RestFul_Mode M) { 
}

webview::FOnRestFul& IBaseRestFul::OnRestFul() {
	return on_resetful;
}

void IBaseRestFul::BeginDestroy() {

}

std::string IBaseRestFul::GetModeStr() {
	switch (Mode) {
	case WebView_RestFul_Mode::WebView_RestFul_Mode_Get: return ("GET");
	case WebView_RestFul_Mode::WebView_RestFul_Mode_Post: return ("POST");
	case WebView_RestFul_Mode::WebView_RestFul_Mode_Put: return ("PUT");
	case WebView_RestFul_Mode::WebView_RestFul_Mode_Delete: return ("DELETE");
	}
	return ("POST");
}