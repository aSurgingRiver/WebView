// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "UObject/SoftObjectPtr.h"
#include "Materials/Material.h"
#include "WebViewAssetManager.generated.h"

class UMaterial;
/**
 * 
 */
UCLASS()
class BASEBROWSER_API UWebViewAssetManager : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void LoadDefaultMaterials();

	UMaterial* GetDefaultMaterial(); 
	UMaterial* GetDefaultTranslucentMaterial(); 

protected:
	UPROPERTY()
	TSoftObjectPtr<UMaterial> DefaultMaterial;
	TSoftObjectPtr<UMaterial> DefaultTranslucentMaterial;
};
