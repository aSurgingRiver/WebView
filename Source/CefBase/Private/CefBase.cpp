// Copyright aXiuShen. All Rights Reserved.

#include "CefBase.h"
#include "cef3lib.h"

#define LOCTEXT_NAMESPACE "FCefBaseModule"

void FCefBaseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#ifdef WEBVIEW_CUSTOMIZED_CORE
	//ICEF3LIB::get()->LoadCEF3Modules();
#endif
}

void FCefBaseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
#ifdef WEBVIEW_CUSTOMIZED_CORE
	//ICEF3LIB::get()->UnloadCEF3Modules();
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCefBaseModule, CefBase)