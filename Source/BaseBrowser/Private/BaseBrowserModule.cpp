// Copyright aXiuShen. All Rights Reserved.

#include "BaseBrowserModule.h"
#include "CoreWebLog.h"

#define LOCTEXT_NAMESPACE "FBaseBrowserModule"

DEFINE_LOG_CATEGORY(WebViewLog);

void FBaseBrowserModule::StartupModule()
{

}

void FBaseBrowserModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBaseBrowserModule, BaseBrowser)