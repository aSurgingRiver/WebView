// Copyright aXiuShen. All Rights Reserved.
#include "WebViewTextureResource.h"

#include "DeviceProfiles/DeviceProfile.h"
#include "DeviceProfiles/DeviceProfileManager.h"
#include "ExternalTexture.h"
#include "PipelineStateCache.h"
#include "SceneUtils.h"
#include "Shader.h"
#include "StaticBoundShaderState.h"
#include "RenderUtils.h"
#include "RHIStaticStates.h"
#include "ExternalTexture.h"
#include "CoreWebLog.h"
#include "WebViewTexture.h"


#define WebViewTextureRESOURCE_TRACE_RENDER 0

/* FWebViewTextureResource structors
 *****************************************************************************/

FWebViewTextureResource::FWebViewTextureResource(UWebViewTexture& InOwner, FIntPoint& InOwnerDim, SIZE_T& InOwnerSize)
	: Cleared(false)
	, CurrentClearColor(FLinearColor::Transparent)
	, Owner(InOwner)
	, OwnerDim(InOwnerDim)
	, OwnerSize(InOwnerSize)
{
	UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:FWebViewTextureResource %d %d"), OwnerDim.X, OwnerDim.Y);
}


/* FWebViewTextureResource interface
 *****************************************************************************/

void FWebViewTextureResource::Render(const FRenderParams& Params)
{
	check(IsInRenderingThread());

	TSharedPtr<FWebViewTextureSampleQueue, ESPMode::ThreadSafe> SampleSource = Params.SampleSource.Pin();

	if (SampleSource.IsValid())
	{
		// get the most current sample to be rendered
		TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe> Sample;
		bool SampleValid = false;
		
		while (SampleSource->Peek(Sample) && Sample.IsValid())
		{
			SampleValid = SampleSource->Dequeue(Sample);
		}

		if (!SampleValid)
		{
			return; // no sample to render
		}

		check(Sample.IsValid());

		// render the sample
		CopySample(Sample, Params.ClearColor);

		if (!GSupportsImageExternal && Params.PlayerGuid.IsValid())
		{
			FTextureRHIRef VideoTexture = (FTextureRHIRef)Owner.TextureReference.TextureReferenceRHI;
			FExternalTextureRegistry::Get().RegisterExternalTexture(Params.PlayerGuid, VideoTexture, SamplerStateRHI, Sample->GetScaleRotation(), Sample->GetOffset());
		}
	}
	else if (!Cleared)
	{
		ClearTexture(Params.ClearColor);

		if (!GSupportsImageExternal && Params.PlayerGuid.IsValid())
		{
			FTextureRHIRef VideoTexture = (FTextureRHIRef)Owner.TextureReference.TextureReferenceRHI;
			FExternalTextureRegistry::Get().RegisterExternalTexture(Params.PlayerGuid, VideoTexture, SamplerStateRHI, FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
		}
	}
}


/* FRenderTarget interface
 *****************************************************************************/

FIntPoint FWebViewTextureResource::GetSizeXY() const
{
	return FIntPoint(Owner.GetWidth(), Owner.GetHeight());
}


/* FTextureResource interface
 *****************************************************************************/

FString FWebViewTextureResource::GetFriendlyName() const
{
	return Owner.GetPathName();
}


uint32 FWebViewTextureResource::GetSizeX() const
{
	return Owner.GetWidth();
}


uint32 FWebViewTextureResource::GetSizeY() const
{
	return Owner.GetHeight();
}


#if WEBVIEW_ENGINE_VERSION >= 50300
void FWebViewTextureResource::InitRHI(FRHICommandListBase& RHICmdList )
{
	// create the sampler state
	FSamplerStateInitializerRHI SamplerStateInitializer(
		(ESamplerFilter)UDeviceProfileManager::Get().GetActiveProfile()->GetTextureLODSettings()->GetSamplerFilter(&Owner),
		(Owner.AddressX == TA_Wrap) ? AM_Wrap : ((Owner.AddressX == TA_Clamp) ? AM_Clamp : AM_Mirror),
		(Owner.AddressY == TA_Wrap) ? AM_Wrap : ((Owner.AddressY == TA_Clamp) ? AM_Clamp : AM_Mirror),
		AM_Wrap
	);

	SamplerStateRHI = RHICreateSamplerState(SamplerStateInitializer);
}
#else
void FWebViewTextureResource::InitDynamicRHI()
{
	// create the sampler state
	FSamplerStateInitializerRHI SamplerStateInitializer(
		(ESamplerFilter)UDeviceProfileManager::Get().GetActiveProfile()->GetTextureLODSettings()->GetSamplerFilter(&Owner),
		(Owner.AddressX == TA_Wrap) ? AM_Wrap : ((Owner.AddressX == TA_Clamp) ? AM_Clamp : AM_Mirror),
		(Owner.AddressY == TA_Wrap) ? AM_Wrap : ((Owner.AddressY == TA_Clamp) ? AM_Clamp : AM_Mirror),
		AM_Wrap
	);

	SamplerStateRHI = RHICreateSamplerState(SamplerStateInitializer);
}
#endif


void FWebViewTextureResource::ReleaseRHI()
{
	Cleared = false;

	InputTarget.SafeRelease();
	OutputTarget.SafeRelease();
	RenderTargetTextureRHI.SafeRelease();
	TextureRHI.SafeRelease();

	UpdateTextureReference(nullptr);
}


/* FWebViewTextureResource implementation
 *****************************************************************************/

void FWebViewTextureResource::ClearTexture(const FLinearColor& ClearColor)
{
	UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:ClearTexture"));
#if WEBVIEW_ENGINE_VERSION>=50100
	// create output render target if we don't have one yet
	const ETextureCreateFlags OutputCreateFlags = ETextureCreateFlags::Dynamic | ETextureCreateFlags::SRGB;

	if ((ClearColor != CurrentClearColor) || !OutputTarget.IsValid() || !EnumHasAllFlags(OutputTarget->GetFlags(), OutputCreateFlags))
	{
		const FRHITextureCreateDesc Desc =
			FRHITextureCreateDesc::Create2D(TEXT("FWebViewTextureResource"))
			.SetExtent(2, 2)
			.SetFormat(PF_B8G8R8A8)
			.SetFlags(OutputCreateFlags | ETextureCreateFlags::RenderTargetable | ETextureCreateFlags::ShaderResource)
			.SetInitialState(ERHIAccess::SRVMask)
			.SetClearValue(FClearValueBinding(ClearColor));

		OutputTarget = RHICreateTexture(Desc);

		CurrentClearColor = ClearColor;
		UpdateResourceSize();
	}

	if (RenderTargetTextureRHI != OutputTarget)
	{
		UpdateTextureReference(OutputTarget);
	}

	// draw the clear color
	FRHICommandListImmediate& CommandList = FRHICommandListExecutor::GetImmediateCommandList();
	{
		CommandList.Transition(FRHITransitionInfo(RenderTargetTextureRHI, ERHIAccess::Unknown, ERHIAccess::RTV));
		ClearRenderTarget(CommandList, RenderTargetTextureRHI);
		CommandList.Transition(FRHITransitionInfo(RenderTargetTextureRHI, ERHIAccess::RTV, ERHIAccess::SRVMask));
	}

	Cleared = true;
#else

	FPlatformMisc::LowLevelOutputDebugStringf(TEXT("FWebBViewTextureResource:ClearTexture"));
	// create output render target if we don't have one yet
	const ETextureCreateFlags OutputCreateFlags = TexCreate_Dynamic | TexCreate_SRGB;

	if ((ClearColor != CurrentClearColor) || !OutputTarget.IsValid() || ((OutputTarget->GetFlags() & OutputCreateFlags) != OutputCreateFlags))
	{
#if WEBVIEW_ENGINE_VERSION>=50000
		FRHIResourceCreateInfo CreateInfo(TEXT("FWebViewTextureResource"), FClearValueBinding(ClearColor));
#else
		FRHIResourceCreateInfo CreateInfo = {
			FClearValueBinding(ClearColor)
		};
#endif
		TRefCountPtr<FRHITexture2D> DummyTexture2DRHI;

		RHICreateTargetableShaderResource2D(
			2,
			2,
			PF_B8G8R8A8,
			1,
			OutputCreateFlags,
			TexCreate_RenderTargetable,
			false,
			CreateInfo,
			OutputTarget,
			DummyTexture2DRHI
		);

		CurrentClearColor = ClearColor;
		UpdateResourceSize();
	}

	if (RenderTargetTextureRHI != OutputTarget)
	{
		UpdateTextureReference(OutputTarget);
	}

	// draw the clear color
	FRHICommandListImmediate& CommandList = FRHICommandListExecutor::GetImmediateCommandList();
	{
		FRHIRenderPassInfo RPInfo(RenderTargetTextureRHI, ERenderTargetActions::Clear_Store);
		CommandList.BeginRenderPass(RPInfo, TEXT("ClearTexture"));
		CommandList.EndRenderPass();

		CommandList.Transition(FRHITransitionInfo(RenderTargetTextureRHI, ERHIAccess::RTV, ERHIAccess::SRVMask));
	}
	Cleared = true;
#endif
}

void FWebViewTextureResource::CopySample(const TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe>& Sample, const FLinearColor& ClearColor)
{
	FRHITexture* SampleTexture = Sample->GetTexture();
#if WEBVIEW_ENGINE_VERSION >= 50500
	FRHITexture* SampleTexture2D = (SampleTexture != nullptr) ? SampleTexture->GetTexture2D() : nullptr;
#else
	FRHITexture2D* SampleTexture2D = (SampleTexture != nullptr) ? SampleTexture->GetTexture2D() : nullptr;
#endif
	
	// If the sample already provides a texture resource, we simply use that
	// as the output render target. If the sample only provides raw data, then
	// we create our own output render target and copy the data into it.
	if (SampleTexture2D != nullptr)
	{
		UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:CopySample 1"));
		// use sample's texture as the new render target.
		if (TextureRHI != SampleTexture2D)
		{
			UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:CopySample 11"));
			UpdateTextureReference(SampleTexture2D);

			OutputTarget.SafeRelease();
			UpdateResourceSize();
		}
	}
	else
	{
		UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:CopySample 2"));
		// create a new output render target if necessary
		const ETextureCreateFlags OutputCreateFlags = TexCreate_Dynamic | TexCreate_SRGB;
		const FIntPoint SampleDim = Sample->GetDim();

		if ((ClearColor != CurrentClearColor) || !OutputTarget.IsValid() || (OutputTarget->GetSizeXY() != SampleDim) || ((OutputTarget->GetFlags() & OutputCreateFlags) != OutputCreateFlags))
		{
			UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:CopySample 1"));

#if WEBVIEW_ENGINE_VERSION>=50100
			const FRHITextureCreateDesc Desc =
				FRHITextureCreateDesc::Create2D(TEXT("FWebViewTextureResource"))
				.SetExtent(SampleDim)
				.SetFormat(PF_B8G8R8A8)
				.SetFlags(OutputCreateFlags | ETextureCreateFlags::RenderTargetable | ETextureCreateFlags::ShaderResource)
				.SetInitialState(ERHIAccess::SRVMask)
				.SetClearValue(FClearValueBinding(ClearColor));

			OutputTarget = RHICreateTexture(Desc);
#else
			FPlatformMisc::LowLevelOutputDebugStringf(TEXT("FWebBrowserTextureResource:CopySample 1"));
			TRefCountPtr<FRHITexture2D> DummyTexture2DRHI;

#if WEBVIEW_ENGINE_VERSION>=50000
			FRHIResourceCreateInfo CreateInfo(TEXT("FWebViewTextureResource"), FClearValueBinding(ClearColor));
#else
			FRHIResourceCreateInfo CreateInfo = {
				FClearValueBinding(ClearColor)
			};
#endif

			RHICreateTargetableShaderResource2D(
				SampleDim.X,
				SampleDim.Y,
				PF_B8G8R8A8,
				1,
				OutputCreateFlags,
				TexCreate_RenderTargetable,
				false,
				CreateInfo,
				OutputTarget,
				DummyTexture2DRHI
			);
#endif

			CurrentClearColor = ClearColor;
			UpdateResourceSize();
		}

		if (RenderTargetTextureRHI != OutputTarget)
		{
			UpdateTextureReference(OutputTarget);
		}

		UE_LOG(WebViewLog, VeryVerbose, TEXT("WebViewTextureResource:CopySample: %d x %d"), SampleDim.X, SampleDim.Y);

		// copy sample data to output render target
		FUpdateTextureRegion2D Region(0, 0, 0, 0, SampleDim.X, SampleDim.Y);
		RHIUpdateTexture2D(RenderTargetTextureRHI.GetReference(), 0, Region, Sample->GetStride(), (uint8*)Sample->GetBuffer());
	}
	Cleared = false;
}


void FWebViewTextureResource::UpdateResourceSize()
{
	UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:UpdateResourceSize"));

	SIZE_T ResourceSize = 0;

	if (InputTarget.IsValid())
	{
		ResourceSize += CalcTextureSize(InputTarget->GetSizeX(), InputTarget->GetSizeY(), InputTarget->GetFormat(), 1);
	}

	if (OutputTarget.IsValid())
	{
		ResourceSize += CalcTextureSize(OutputTarget->GetSizeX(), OutputTarget->GetSizeY(), OutputTarget->GetFormat(), 1);
	}

	OwnerSize = ResourceSize;
}

#if WEBVIEW_ENGINE_VERSION>=50500
void FWebViewTextureResource::UpdateTextureReference(FRHITexture* NewTexture)
#else
void FWebViewTextureResource::UpdateTextureReference(FRHITexture2D* NewTexture)
#endif
{
	TextureRHI = NewTexture;
	RenderTargetTextureRHI = NewTexture;

	RHIUpdateTextureReference(Owner.TextureReference.TextureReferenceRHI, NewTexture);

	if (RenderTargetTextureRHI != nullptr)
	{
		OwnerDim = FIntPoint(RenderTargetTextureRHI->GetSizeX(), RenderTargetTextureRHI->GetSizeY());
	}
	else
	{
		OwnerDim = FIntPoint::ZeroValue;
	}
	UE_LOG(WebViewLog, VeryVerbose, TEXT("FWebViewTextureResource:UpdateTextureReference: %d x %d"), OwnerDim.X, OwnerDim.Y);
}
