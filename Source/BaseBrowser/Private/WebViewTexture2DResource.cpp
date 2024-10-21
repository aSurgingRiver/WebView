// Copyright aXiuShen. All Rights Reserved.

#include "WebViewTexture2DResource.h"
#include "WebViewTexture2D.h"

#include "ExternalTexture.h"
#include "Modules/ModuleManager.h"
#include "RenderUtils.h"
#include "RenderingThread.h"
#include "UObject/WeakObjectPtrTemplates.h"


FWebViewTexture2DResource::FWebViewTexture2DResource(UWebViewTexture2D* texture, SYTextureRHIRef _RHITexture)
	: OwnerTexture(texture)
{
	ExternalTexture = _RHITexture;
}

void FWebViewTexture2DResource::InitRHI(
#if WEBVIEW_ENGINE_VERSION>=50300
	FRHICommandListBase& RHICmdList
#endif
) {
	auto SamplerAddressMode = OwnerTexture->SamplerAddressMode;
	auto SamplerFilter = OwnerTexture->SamplerFilter;
	FSamplerStateInitializerRHI SamplerStateInitializer
	(
		SamplerFilter,
		SamplerAddressMode,
		SamplerAddressMode,
		SamplerAddressMode
	);
	SamplerStateRHI = GetOrCreateSamplerState(SamplerStateInitializer);

	TextureRHI = ExternalTexture;
	RHIUpdateTextureReference(OwnerTexture->TextureReference.TextureReferenceRHI, ExternalTexture);
}

/** Returns the width of the texture in pixels. */
uint32 FWebViewTexture2DResource::GetSizeX() const
{
	return OwnerTexture->Width;
}

/** Returns the height of the texture in pixels. */
uint32 FWebViewTexture2DResource::GetSizeY() const
{
	return OwnerTexture->Height;
}

/** Called when the resource is released. This is only called by the rendering thread. */
void FWebViewTexture2DResource::ReleaseRHI()
{
	RHIUpdateTextureReference(OwnerTexture->TextureReference.TextureReferenceRHI, nullptr);
	FTextureResource::ReleaseRHI();
	ExternalTexture.SafeRelease();
}
