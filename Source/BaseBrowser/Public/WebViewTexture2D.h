// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreTypes.h"
#include "Containers/EnumAsByte.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "Math/Color.h"
#include "Math/IntPoint.h"
#include "Misc/Timespan.h"
#include "Templates/SharedPointer.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "WebViewTextureSample.h"

#include "WebViewTexture2D.generated.h"

class UTexture2DDynamic;
class FWebViewTexture2DResource;
/**
* Implements a texture asset for rendering mobilebrowser output for Android.
* 
*  probably should have derived from UTexture2DDynamic (not UTexture)
*/
UCLASS()
class BASEBROWSER_API UWebViewTexture2D
	: public UTexture
{
	GENERATED_UCLASS_BODY()
public:
#if WEBVIEW_ENGINE_VERSION>=50500
	using SYTextureRHIRef = FTextureRHIRef;
#else
	using SYTextureRHIRef = FTexture2DRHIRef;
#endif
	void Init(SYTextureRHIRef InRHITexture, int w,int h, EPixelFormat InFormat);

	//~ Begin UTexture Interface.
	virtual FTextureResource* CreateResource() override;
	virtual EMaterialValueType GetMaterialType() const override;
	virtual float GetSurfaceWidth() const override;
	virtual float GetSurfaceHeight() const override;
#if WEBVIEW_ENGINE_VERSION>=50100
	virtual ETextureClass GetTextureClass() const override;
	virtual float GetSurfaceDepth() const override;
	virtual uint32 GetSurfaceArraySize() const override;
#endif
	/** The width of the texture. */
	UPROPERTY(BlueprintReadOnly, Category = "Web View|Texture2D")
	int32 Width;
	/** The height of the texture. */
	UPROPERTY(BlueprintReadOnly, Category = "Web View|Texture2D")
	int32 Height;
	/** The format of the texture. */
	UPROPERTY(BlueprintReadOnly, Category = "Web View|Texture2D")
	TEnumAsByte<enum EPixelFormat> Format;

	/** The sampler default address mode for this texture. */
	ESamplerAddressMode SamplerAddressMode;
	/** The sampler filter for this texture. */
	ESamplerFilter SamplerFilter;
protected:

	SYTextureRHIRef ExternalTexture;
	friend class FWebViewTexture2DResource;
};
