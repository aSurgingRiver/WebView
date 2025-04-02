// Copyright aXiuShen. All Rights Reserved.

#include "BaseBrowserModule.h"
//#include "WebViewAssetManager.h"
#include "WebViewLog.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "FBaseBrowserModule"

DEFINE_LOG_CATEGORY(WebViewLog);

namespace webview {
	void PrintScreen(FString Content, FColor color, float time) {
		if (!GEngine)return;
		GEngine->AddOnScreenDebugMessage(
			-1,               // Key (使用 -1 表示不需要唯一标识)
			time,              // 显示时间（秒）
			color,   // 颜色
			Content           // 要显示的字符串
		);
	}
}

IBaseBrowserModule* IBaseBrowserModule::Get()
{
	return &FModuleManager::LoadModuleChecked<IBaseBrowserModule>("BaseBrowser");
}

void FBaseBrowserModule::StartupModule()
{

	//if (WebViewAssetMgr == nullptr)
	//{
	//	WebViewAssetMgr = NewObject<UWebViewAssetManager>((UObject*)GetTransientPackage(), NAME_None, RF_Transient | RF_Public);
	//	WebViewAssetMgr->LoadDefaultMaterials();
	//}
}

void FBaseBrowserModule::ShutdownModule()
{

}

UMaterialInterface* FBaseBrowserModule::GetDefaultTranslucentMaterial() {
	return nullptr;
}

UMaterialInterface* FBaseBrowserModule::GetDefaultMaterial() {
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBaseBrowserModule, BaseBrowser)