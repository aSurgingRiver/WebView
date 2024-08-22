// Copyright aXiuShen. All Rights Reserved.

#include "WebView.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Materials/Material.h"
#ifdef WEBVIEW_CUSTOMIZED_CORE
#include "WebModule.h"
#include "cef3lib.h"
#include "cefcorelib.h"
#if WITH_EDITOR
#include "Editor.h"
#endif
#endif

#define LOCTEXT_NAMESPACE "FWebViewModule"

class FWebViewModule : public IWebViewModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
};

void FWebViewModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  
	// For modules that support dynamic reloading,
	// we call this function before unloading the module.
#ifndef USING_WEBBROWSER
	webview::IBrowserInstance::Get().UnLoad();
#endif
}

void FWebViewModule::StartupModule()
{
#ifndef USING_WEBBROWSER
	ICEF3LIB::get()->LoadCEF3Modules();
#if WITH_EDITOR 
	ICefCoreLIB::get()->Load();
#endif
	webview::IBrowserInstance::Get().check_brand(ICEF3LIB::get()->Branch());
	webview::IBrowserInstance::Get().Load();
#if WITH_EDITOR 
	FEditorDelegates::PausePIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnEndPIE(); });
	FEditorDelegates::BeginPIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnBeginPIE(); });
	FEditorDelegates::EndPIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnEndPIE(); });
	FEditorDelegates::ResumePIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnBeginPIE(); });
#endif
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWebViewModule, WebView)