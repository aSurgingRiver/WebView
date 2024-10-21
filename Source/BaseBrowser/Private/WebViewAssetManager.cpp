// Copyright aXiuShen. All Rights Reserved.

#include "WebViewAssetManager.h"

#if WITH_EDITOR || PLATFORM_ANDROID || PLATFORM_IOS
#include "Materials/Material.h"
#include "WebViewTexture.h"
#endif

/////////////////////////////////////////////////////
// WebBrowserAssetManager

UWebViewAssetManager::UWebViewAssetManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) ,
	DefaultMaterial(FSoftObjectPath(FString(TEXT("/WebView/Texture/WebTexture_M.WebTexture_M")))) ,
	DefaultTranslucentMaterial(FSoftObjectPath(FString(TEXT("/WebView/Texture/WebTexture_TM.WebTexture_TM"))))
{
#if WITH_EDITOR || PLATFORM_ANDROID || PLATFORM_IOS
	UWebViewTexture::StaticClass();
#endif
};

void UWebViewAssetManager::LoadDefaultMaterials()
{
	DefaultMaterial.LoadSynchronous();
	DefaultTranslucentMaterial.LoadSynchronous();
}

UMaterial* UWebViewAssetManager::GetDefaultMaterial()
{
	return DefaultMaterial.Get();
}

UMaterial* UWebViewAssetManager::GetDefaultTranslucentMaterial()
{
	return DefaultTranslucentMaterial.Get();
}
