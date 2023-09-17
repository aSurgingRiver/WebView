// Copyright aSurgingRiver, Inc. All Rights Reserved.

#include "WebView.h"
#include "Modules/ModuleManager.h"
#include "Materials/Material.h"
#if CEF_NEW_VERSION
#include "WebModule.h"
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
}

void FWebViewModule::StartupModule()
{
#if WITH_EDITOR && CEF_NEW_VERSION
	FEditorDelegates::PausePIE.AddLambda([](bool) {IWebModule::Get().OnEndPIE(); });
	FEditorDelegates::BeginPIE.AddLambda([](bool) {IWebModule::Get().OnBeginPIE(); });
	FEditorDelegates::EndPIE.AddLambda([](bool) {IWebModule::Get().OnEndPIE(); });
	FEditorDelegates::ResumePIE.AddLambda([](bool) {IWebModule::Get().OnBeginPIE(); });
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWebViewModule, WebView)