// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Materials/MaterialInterface.h"

class BASEBROWSER_API IBaseBrowserModule : public IModuleInterface
{
public:
	static IBaseBrowserModule* Get();
	virtual UMaterialInterface* GetDefaultTranslucentMaterial() = 0;
	virtual UMaterialInterface* GetDefaultMaterial() = 0;
};
