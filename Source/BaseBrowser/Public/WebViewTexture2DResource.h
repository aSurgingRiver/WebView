// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreTypes.h"
#include "Containers/Queue.h"
#include "Logging/LogMacros.h"
#include "Math/Color.h"
#include "Misc/Guid.h"
#include "Misc/Timespan.h"
#include "Templates/RefCounting.h"
#include "Templates/SharedPointer.h"
#include "TextureResource.h"
#include "Rendering/StreamableTextureResource.h"
#include "UnrealClient.h"

class FTexture2DDynamicResource;
class UWebViewTexture2D;
class BASEBROWSER_API FWebViewTexture2DResource : public FTextureResource
{
public:

#if WEBVIEW_ENGINE_VERSION>=50500
	using SYTextureRHIRef = FTextureRHIRef;
#else
	using SYTextureRHIRef = FTexture2DRHIRef;
#endif
	FWebViewTexture2DResource(UWebViewTexture2D* texture,SYTextureRHIRef RHITexture);
#if WEBVIEW_ENGINE_VERSION>=50300
	virtual void InitRHI(FRHICommandListBase& RHICmdList) override;
#else
	virtual void InitRHI() override;
#endif
	/** Returns the width of the texture in pixels. */
	virtual uint32 GetSizeX() const override;

	/** Returns the height of the texture in pixels. */
	virtual uint32 GetSizeY() const override;

	/** Called when the resource is released. This is only called by the rendering thread. */
	virtual void ReleaseRHI() override;

private:
	SYTextureRHIRef ExternalTexture;
	UWebViewTexture2D* OwnerTexture;
};
