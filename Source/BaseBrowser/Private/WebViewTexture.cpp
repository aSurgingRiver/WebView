// Copyright Epic Games, Inc. All Rights Reserved.

#include "WebViewTexture.h"

#include "ExternalTexture.h"
#include "Modules/ModuleManager.h"
#include "RenderUtils.h"
#include "RenderingThread.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "WebViewTextureResource.h"
//#include "IWebViewWindow.h"

/* UWebViewTexture structors
*****************************************************************************/

UWebViewTexture::UWebViewTexture(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AddressX(TA_Clamp)
	, AddressY(TA_Clamp)
	, ClearColor(FLinearColor::Black)
	, Size(0)
{
	SampleQueue = MakeShared<FWebViewTextureSampleQueue, ESPMode::ThreadSafe>();
	WebPlayerGuid = FGuid::NewGuid();
	NeverStream = true;
}

/* UWebViewTexture interface
*****************************************************************************/

float UWebViewTexture::GetAspectRatio() const
{
	if (Dimensions.Y == 0)
	{
		return 0.0f;
	}

	return (float)(Dimensions.X) / Dimensions.Y;
}

int32 UWebViewTexture::GetHeight() const
{
	return Dimensions.Y;
}

int32 UWebViewTexture::GetWidth() const
{
	return Dimensions.X;
}

/* UTexture interface
*****************************************************************************/

FTextureResource* UWebViewTexture::CreateResource()
{
	return new FWebViewTextureResource(*this, Dimensions, Size);
}

EMaterialValueType UWebViewTexture::GetMaterialType() const
{
	return MCT_TextureExternal;
}

float UWebViewTexture::GetSurfaceWidth() const
{
	return Dimensions.X;
}

float UWebViewTexture::GetSurfaceHeight() const
{
	return Dimensions.Y;
}

FGuid UWebViewTexture::GetExternalTextureGuid() const
{
	return WebPlayerGuid;
}

void UWebViewTexture::SetExternalTextureGuid(FGuid guid)
{
	WebPlayerGuid = guid;
}

/* UObject interface
*****************************************************************************/

void UWebViewTexture::BeginDestroy()
{
	UnregisterPlayerGuid();

	Super::BeginDestroy();
}

FString UWebViewTexture::GetDesc()
{
	return FString::Printf(TEXT("%ix%i [%s]"), Dimensions.X, Dimensions.Y, GPixelFormats[PF_B8G8R8A8].Name);
}


void UWebViewTexture::GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize)
{
	Super::GetResourceSizeEx(CumulativeResourceSize);
	CumulativeResourceSize.AddUnknownMemoryBytes(Size);
}

/* UWebViewTexture implementation
*****************************************************************************/


void UWebViewTexture::TickResource(TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe> Sample)
{
#if WEBVIEW_ENGINE_VERSION>=42700
	if (GetResource() == nullptr)
#else
	if (Resource == nullptr)
#endif
	{
		return;
	}
	
	check(SampleQueue.IsValid());

	if (Sample.IsValid())
	{
		SampleQueue.Get()->Enqueue(Sample);
	}

	// issue a render command to render the current sample
	FWebViewTextureResource::FRenderParams RenderParams;
	{
		RenderParams.ClearColor = ClearColor;
		RenderParams.PlayerGuid = GetExternalTextureGuid();
		RenderParams.SampleSource = SampleQueue;
	}
#if WEBVIEW_ENGINE_VERSION>=42700
	FWebViewTextureResource* ResourceParam = (FWebViewTextureResource*)GetResource();
#else
	FWebViewTextureResource* ResourceParam = (FWebViewTextureResource*)Resource;
	if (Resource == nullptr)
#endif
	ENQUEUE_RENDER_COMMAND(UWebViewTextureResourceRender)(
		[ResourceParam, RenderParams](FRHICommandListImmediate& RHICmdList)
		{
			ResourceParam->Render(RenderParams);
		});
}

void UWebViewTexture::UnregisterPlayerGuid()
{
	if (!WebPlayerGuid.IsValid())
	{
		return;
	}

	FGuid PlayerGuid = WebPlayerGuid;
	ENQUEUE_RENDER_COMMAND(UWebViewTextureUnregisterPlayerGuid)(
		[PlayerGuid](FRHICommandListImmediate& RHICmdList)
		{
			FExternalTextureRegistry::Get().UnregisterExternalTexture(PlayerGuid);
		});
}
