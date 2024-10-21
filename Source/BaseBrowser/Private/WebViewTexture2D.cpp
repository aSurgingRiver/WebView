// Copyright aXiuShen. All Rights Reserved.

#include "WebViewTexture2D.h"
#include "WebViewTexture2DResource.h"

#include "ExternalTexture.h"
#include "Modules/ModuleManager.h"
#include "RenderUtils.h"
#include "RenderingThread.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "WebViewTextureResource.h"
//#include "IWebViewWindow.h"

/* UWebViewTexture2D structors
*****************************************************************************/

UWebViewTexture2D::UWebViewTexture2D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SamplerAddressMode = ESamplerAddressMode::AM_Clamp;
	SamplerFilter = ESamplerFilter::SF_AnisotropicLinear;
}

class FTextureResource* UWebViewTexture2D::CreateResource() {
	return new FWebViewTexture2DResource(this, ExternalTexture);
}

EMaterialValueType UWebViewTexture2D::GetMaterialType() const
{
	return EMaterialValueType::MCT_TextureExternal;//
}

void UWebViewTexture2D::Init(SYTextureRHIRef InRHITexture, int w, int h, EPixelFormat InFormat) {
	ExternalTexture = InRHITexture;
	Width = w;
	Height = h;
	Format = InFormat;
}

float UWebViewTexture2D::GetSurfaceWidth() const {
	return Width;
}
float UWebViewTexture2D::GetSurfaceHeight() const {
	return Height;
}
#if WEBVIEW_ENGINE_VERSION>=50100
ETextureClass UWebViewTexture2D::GetTextureClass() const {
	return ETextureClass::Other2DNoSource;//
}

float UWebViewTexture2D::GetSurfaceDepth() const {
	return 0; 
}
uint32 UWebViewTexture2D::GetSurfaceArraySize() const {
	return 0; 
}
#endif