// Copyright aXiuShen. All Rights Reserved.

#include "BaseBrowserModule.h"
#include "WebViewAssetManager.h"
#include "CoreWebLog.h"

#define LOCTEXT_NAMESPACE "FBaseBrowserModule"

DEFINE_LOG_CATEGORY(WebViewLog);

IBaseBrowserModule* IBaseBrowserModule::Get()
{
	return &FModuleManager::LoadModuleChecked<IBaseBrowserModule>("BaseBrowser");
}

void FBaseBrowserModule::StartupModule()
{

	if (WebViewAssetMgr == nullptr)
	{
		WebViewAssetMgr = NewObject<UWebViewAssetManager>((UObject*)GetTransientPackage(), NAME_None, RF_Transient | RF_Public);
		WebViewAssetMgr->LoadDefaultMaterials();
	}
}

void FBaseBrowserModule::ShutdownModule()
{

}

UMaterialInterface* FBaseBrowserModule::GetDefaultTranslucentMaterial() {
	if (WebViewAssetMgr == nullptr) return nullptr;
	return WebViewAssetMgr->GetDefaultMaterial();
}

UMaterialInterface* FBaseBrowserModule::GetDefaultMaterial() {
	if (WebViewAssetMgr == nullptr) return nullptr;
	return WebViewAssetMgr->GetDefaultTranslucentMaterial();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBaseBrowserModule, BaseBrowser)