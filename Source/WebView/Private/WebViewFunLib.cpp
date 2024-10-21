// Copyright aXiuShen. All Rights Reserved.

#include "WebViewFunLib.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "WebCookie.h"
#ifdef WEBVIEW_CEF
#include "CefWebViewFunLib.h"
#include "ImitateInput.h"
#include "CefZipReader.h"
#endif
#include "cefcorelib.h"

bool UWebViewFunLib::SetCookie(const FString& URL, const FWebCookie& Cookie) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::SetCookie(URL, Cookie);
#else
	return false;
#endif
}

bool UWebViewFunLib::DeleteCookies(const FString& URL, const FString& CookieName) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::DeleteCookies(URL, CookieName);
#else
	return false;
#endif
}

void UWebViewFunLib::PopupURL(const FString& URL) {
#ifdef WEBVIEW_CEF
	UWebViewFunLibImp::PopupURL(URL);
#else
	return;
#endif
}

FString UWebViewFunLib::EncodeURL(const FString& URL, const bool use_plus) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::EncodeURL(URL, use_plus);
#else
	return FString();
#endif
}

FString UWebViewFunLib::Base64Encode(const FString& data) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::Base64Encode(data);
#else
	return FString();
#endif
}

FString UWebViewFunLib::Base64Decode(const FString& base64) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::Base64Decode(base64);
#else
	return FString();
#endif
}

FString UWebViewFunLib::Base64EncodeFile(const FString& file) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::Base64EncodeFile(file);
#else
	return FString();
#endif
}

bool UWebViewFunLib::Base64DecodeFile(const FString& base64,const FString& file) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::Base64DecodeFile(base64, file);
#else
	return false;
#endif

}

bool UWebViewFunLib::Zip(const FString& Dir, const FString& ZipFile, const bool IncludeHiddenFiles) {
#ifdef WEBVIEW_CEF
	return UWebViewFunLibImp::Zip(Dir, ZipFile, IncludeHiddenFiles);
#else
	return false;
#endif
}


bool UWebViewFunLib::UnZip(const FString& zipFile, const FString& passwd,UZipReader*& Reader) {
#ifdef WEBVIEW_CEF
	Reader = NewObject<UZipReader>();
	return Reader->Open(zipFile, passwd);
#else
	return false;
#endif
}



FImitateInput& UWebViewFunLib::AddMouse(FImitateInput& screen, const WebView_ImitateInput_Mouse mouse, const FIntPoint& p) {
	//FImitateInput screen = _screen;
	FString type;
	switch (mouse) {
	case WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Down:type = TEXT("mouse_down"); break;
	case WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Up:type = TEXT("mouse_up"); break;
	case WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Move:type = TEXT("mouse_move"); break;
	default :return screen;
	}
	FString cmd = FString::Printf(TEXT("{\"type\":\"%s\",\"pos\":{\"x\":%d,\"y\":%d}}"), *type, p.X, p.Y);
	screen.Event.Push(cmd);
	return screen;
}

FImitateInput& UWebViewFunLib::AddClicked(FImitateInput& screen, const FIntPoint& p) {
	/*FImitateInput screen =*/ AddMouse(screen, WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Down, p);
	return AddMouse(screen, WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Up, p);
}

FImitateInput& UWebViewFunLib::AddText(FImitateInput& screen, const FString& text) {
	FString cmd = FString::Printf(TEXT("{\"type\":\"input\",\"text\":\"%s\"}"), *text);
	//FImitateInput screen(screen);
	screen.Event.Push(cmd);
	return screen;
}

FImitateInput& UWebViewFunLib::AddDelay(FImitateInput& screen, const int ms) {
	FString cmd = FString::Printf(TEXT("{\"type\":\"delay\",\"ms\":%d}"), ms);
	//FImitateInput screen(_screen);
	screen.Event.Push(cmd);
	return screen;
}

FImitateInput& UWebViewFunLib::AddKeystroke(FImitateInput& screen, const WebView_ImitateInput_Key keyboard, const FKey& key, const TArray<FKey>& CombinKey) {
	FString type; 
	//FImitateInput screen(_screen);
	switch (keyboard) {
	case WebView_ImitateInput_Key::WebView_ImitateInput_Key_Down:type = TEXT("key_down"); break;
	case WebView_ImitateInput_Key::WebView_ImitateInput_Key_Up:type = TEXT("key_up"); break;
	case WebView_ImitateInput_Key::WebView_ImitateInput_Key_Char:type = TEXT("key_char"); break;
	default:return screen;
	}
	const uint32* pcode = 0;// key.GetFName();
	const uint32* pcharacter = 0;
	int modify = 0 ;
#ifdef WEBVIEW_CEF
	modify = UWebViewFunLibImp::KeytoInner(CombinKey);
#endif
	FKey inK = key;
	FInputKeyManager::Get().GetCodesFromKey(inK, pcode, pcharacter);
	uint32 code = 0;
	uint32 character = 0;
	if (pcode)code = *pcode;
	if (pcharacter)character = *pcharacter;
	if (keyboard != WebView_ImitateInput_Key::WebView_ImitateInput_Key_Char)character = code;
	FString cmd = FString::Printf(TEXT("{\"type\":\"%s\",\"code\":%d,\"character\":%d,\"modify\":%d}"), *type, code, character, modify);
	screen.Event.Push(cmd);
	return screen;

}

FImitateInput& UWebViewFunLib::AddKey(FImitateInput& screen, const FKey& key, const TArray<FKey> CombinKey) {
	/*FImitateInput screen  =*/ AddKeystroke(screen, WebView_ImitateInput_Key::WebView_ImitateInput_Key_Down, key, CombinKey);
	AddKeystroke(screen, WebView_ImitateInput_Key::WebView_ImitateInput_Key_Char, key, CombinKey);
	return AddKeystroke(screen, WebView_ImitateInput_Key::WebView_ImitateInput_Key_Up, key, CombinKey);
}

FImitateInput& UWebViewFunLib::ShowLog(FImitateInput& screen, bool show) {
	//FImitateInput screen(_screen);
	if (show) {
		screen.Event.Add(TEXT(""));
		return screen;
	}
	for (int32 Index = screen.Event.Num() - 1; Index >= 0; --Index) {
		auto& onEv = screen.Event[Index];
		if (onEv.Len() == 0)screen.Event.RemoveAt(Index);
	}
	return screen;
}
FImitateInput& UWebViewFunLib::Clear(FImitateInput& _screen) {
	//FImitateInput screen(_screen);
	_screen.Event.Empty();
	return _screen;
}

