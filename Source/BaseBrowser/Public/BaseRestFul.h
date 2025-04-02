// Copyright aXiuShen. All Rights Reserved.
#pragma once

#include "WebViewEvent.h"
#include "ImitateInput.h"

class BASEBROWSER_API IBaseRestFul
{
public:

	IBaseRestFul(); 
	virtual ~IBaseRestFul();

	virtual void Request(const FString& URL, const FMatureJsonValue& Data);

	virtual void SetMode(WebView_RestFul_Mode Mode);

	virtual webview::FOnRestFul& OnRestFul();

	virtual void BeginDestroy();

	std::string GetModeStr();

protected:
	WebView_RestFul_Mode Mode;
	//FString URL;
	webview::FOnRestFul on_resetful;
};
