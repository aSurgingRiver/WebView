// Copyright aXiuShen. All Rights Reserved.
#include "WebViewTextureSample.h"
#include "CoreTypes.h"
#include "CoreGlobals.h"
#include "Containers/Queue.h"
#include "Math/IntPoint.h"
#include "Math/Range.h"
#include "MediaObjectPool.h"
#include "RHI.h"
#include "RHIUtilities.h"
#include "Templates/SharedPointer.h"

/** Default constructor. */
FWebViewTextureSample::FWebViewTextureSample()
	: Buffer(nullptr)
	, BufferSize(0)
	, Dim(FIntPoint::ZeroValue)
	, ScaleRotation(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f))
	, Offset(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f))
{ }

/** Virtual destructor. */
FWebViewTextureSample::~FWebViewTextureSample()
{
	if (BufferSize > 0)
	{
		FMemory::Free(Buffer);
	}
}


/**
* Get a writable pointer to the sample buffer.
*
* @return Sample buffer.
*/
void* FWebViewTextureSample::GetMutableBuffer()
{
	return Buffer;
}

/**
* Initialize the sample.
*
* @param InDim The sample buffer's width and height (in pixels).
* @param InDuration The duration for which the sample is valid.
* @return true on success, false otherwise.
*/
bool FWebViewTextureSample::Initialize(const FIntPoint& InDim)
{
	if (InDim.GetMin() <= 0)
	{ 
		return false;
	}

	Dim = InDim;

	return true;
}

/**
* Initialize the sample with a memory buffer.
*
* @param InBuffer The buffer containing the sample data.
* @param Copy Whether the buffer should be copied (true) or referenced (false).
* @see InitializeTexture
*/
void FWebViewTextureSample::InitializeBuffer(void* InBuffer, bool Copy)
{
	if (Copy)
	{
		SIZE_T RequiredBufferSize = Dim.X * Dim.Y * sizeof(int32);
		if (BufferSize < RequiredBufferSize)
		{
			if (BufferSize == 0)
			{
				Buffer = FMemory::Malloc(RequiredBufferSize);
			}
			else
			{
				Buffer = FMemory::Realloc(Buffer, RequiredBufferSize);
			}

			BufferSize = RequiredBufferSize;
		}

		FMemory::Memcpy(Buffer, InBuffer, RequiredBufferSize);
	}
	else
	{
		if (BufferSize > 0)
		{
			FMemory::Free(Buffer);
			BufferSize = 0;
		}

		Buffer = InBuffer;
	}
}

/**
* Initialize the sample for copy externally.
*
* @return The size of the buffer
* @see InitializeTexture
*/
int32 FWebViewTextureSample::InitializeBufferForCopy()
{
	SIZE_T RequiredBufferSize = Dim.X * Dim.Y * sizeof(int32);
	if (BufferSize < RequiredBufferSize)
	{
		if (BufferSize == 0)
		{
			Buffer = FMemory::Malloc(RequiredBufferSize);
		}
		else
		{
			Buffer = FMemory::Realloc(Buffer, RequiredBufferSize);
		}

		BufferSize = RequiredBufferSize;
	}
	return BufferSize;
}

/**
* Initialize the sample with a texture resource.
*
* @return The texture resource object that will hold the sample data.
* @note This method must be called on the render thread.
* @see InitializeBuffer
*/
#if WEBVIEW_ENGINE_VERSION>=50500
FRHITexture* FWebViewTextureSample::InitializeTexture()
#else
FRHITexture2D* FWebViewTextureSample::InitializeTexture()
#endif
{
	check(IsInRenderingThread());

	if (Texture.IsValid() && (Texture->GetSizeXY() == Dim))
	{
		return Texture;
	}

#if WEBVIEW_ENGINE_VERSION>=50100
	const FRHITextureCreateDesc Desc =
		FRHITextureCreateDesc::Create2D(TEXT("FWebViewTextureSample"))
		.SetExtent(Dim)
		.SetFormat(PF_B8G8R8A8)
		.SetFlags(ETextureCreateFlags::Dynamic | ETextureCreateFlags::SRGB | ETextureCreateFlags::RenderTargetable | ETextureCreateFlags::ShaderResource)
		.SetInitialState(ERHIAccess::SRVMask);

	Texture = RHICreateTexture(Desc);
#else
	const ETextureCreateFlags CreateFlags = TexCreate_Dynamic | TexCreate_SRGB;
	TRefCountPtr<FRHITexture2D> DummyTexture2DRHI;
#if WEBVIEW_ENGINE_VERSION>=50000
	FRHIResourceCreateInfo CreateInfo(TEXT("FWebViewTextureSample"));
#else
	FRHIResourceCreateInfo CreateInfo;
#endif
	RHICreateTargetableShaderResource2D(
		Dim.X,
		Dim.Y,
		PF_B8G8R8A8,
		1,
		CreateFlags,
		TexCreate_RenderTargetable,
		false,
		CreateInfo,
		Texture,
		DummyTexture2DRHI
	);
#endif
	return Texture;
}

/**
* Set the sample Scale, Rotation, Offset.
*
* @param InScaleRotation The sample scale and rotation transform (2x2).
* @param InOffset The sample offset.
*/
void FWebViewTextureSample::SetScaleRotationOffset(FVector4& InScaleRotation, FVector4& InOffset)
{
	ScaleRotation = FLinearColor(InScaleRotation.X, InScaleRotation.Y, InScaleRotation.Z, InScaleRotation.W);
	Offset = FLinearColor(InOffset.X, InOffset.Y, InOffset.Z, InOffset.W);
}

//~ IMediaTextureSample interface

const void* FWebViewTextureSample::GetBuffer()
{
	return Buffer;
}

FIntPoint FWebViewTextureSample::GetDim() const
{
	return Dim;
}

uint32 FWebViewTextureSample::GetStride() const
{
	return Dim.X * sizeof(int32);
}

#if WITH_ENGINE

FRHITexture* FWebViewTextureSample::GetTexture() const
{
	return Texture.GetReference();
}

#endif //WITH_ENGINE

FLinearColor FWebViewTextureSample::GetScaleRotation() const
{
	return ScaleRotation;
}

FLinearColor FWebViewTextureSample::GetOffset() const
{
	return Offset;
}

/** Default constructor. */
FWebViewTextureSampleQueue::FWebViewTextureSampleQueue()
	: NumSamples(0)
	, PendingFlushes(0)
{ }

/** Virtual destructor. */
FWebViewTextureSampleQueue::~FWebViewTextureSampleQueue() { }

/**
* Get the number of samples in the queue.
*
* @return Number of samples.
* @see Enqueue, Dequeue, Peek
*/
int32 FWebViewTextureSampleQueue::Num() const
{
	return NumSamples;
}

//~ TMediaSampleSource interface (to be called only from consumer thread)

bool FWebViewTextureSampleQueue::Dequeue(TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe>& OutSample)
{
	DoPendingFlushes();

	TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe> Sample;

	if (!Samples.Peek(Sample))
	{
		return false; // empty queue
	}

	if (!Sample.IsValid())
	{
		return false; // pending flush
	}

	Samples.Pop();

	FPlatformAtomics::InterlockedDecrement(&NumSamples);
	check(NumSamples >= 0);

	OutSample = Sample;

	return true;
}

bool FWebViewTextureSampleQueue::Peek(TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe>& OutSample)
{
	DoPendingFlushes();

	TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe> Sample;

	if (!Samples.Peek(Sample))
	{
		return false; // empty queue
	}

	if (!Sample.IsValid())
	{
		return false; // pending flush
	}

	OutSample = Sample;

	return true;
}

bool FWebViewTextureSampleQueue::Pop()
{
	TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe> Sample;

	if (!Samples.Peek(Sample))
	{
		return false; // empty queue
	}

	if (!Sample.IsValid())
	{
		return false; // pending flush
	}

	Samples.Pop();

	FPlatformAtomics::InterlockedDecrement(&NumSamples);
	check(NumSamples >= 0);

	return true;
}

//~ TMediaSampleSink interface (to be called only from producer thread)

bool FWebViewTextureSampleQueue::Enqueue(const TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe>& Sample)
{
	if (Sample.IsValid())
	{
		FPlatformAtomics::InterlockedIncrement(&NumSamples);
	}

	if (!Samples.Enqueue(Sample))
	{
		if (Sample.IsValid())
		{
			FPlatformAtomics::InterlockedDecrement(&NumSamples);
		}

		return false;
	}

	return true;
}

void FWebViewTextureSampleQueue::RequestFlush()
{
	Samples.Enqueue(nullptr); // insert flush marker
	FPlatformAtomics::InterlockedIncrement(&PendingFlushes);
}

/** Perform any pending flushes. */
void FWebViewTextureSampleQueue::DoPendingFlushes()
{
	TSharedPtr<FWebViewTextureSample, ESPMode::ThreadSafe> Sample;

	while ((PendingFlushes > 0) && Samples.Dequeue(Sample))
	{
		if (Sample.IsValid())
		{
			FPlatformAtomics::InterlockedDecrement(&NumSamples);
			check(NumSamples >= 0);
		}
		else
		{
			FPlatformAtomics::InterlockedDecrement(&PendingFlushes);
		}
	}
}


//FFWebViewTextureSamplePool::FFWebViewTextureSamplePool() {
//}
//FFWebViewTextureSamplePool::~FFWebViewTextureSamplePool() {
//}

