// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IBaseBrowserModule.h"
#include "WebViewAssetManager.h"

class FBaseBrowserModule : public IBaseBrowserModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual UMaterialInterface* GetDefaultTranslucentMaterial() ;
	virtual UMaterialInterface* GetDefaultMaterial() ;

private:
	UWebViewAssetManager* WebViewAssetMgr;
};
