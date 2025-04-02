// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SynthComponent.h"
#include "Sound/SoundGenerator.h"
#include "Components/AudioComponent.h"
#include <memory>
#include "WebViewSoundActor.generated.h"

namespace webview {
	struct Frame {
		TArray<float> Data;
		int64_t pts;
	};
	typedef std::shared_ptr<Frame> FramePtr;
}

UCLASS()
class BASEBROWSER_API USoundWaveProceduralWebView : public USoundWaveProcedural {
	GENERATED_BODY()
public:
	using FramePtr = webview::FramePtr;
	using Frame = webview::Frame;
public:
	USoundWaveProceduralWebView(const FObjectInitializer& ObjectInitializer);

	int32 OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples);
	void  AddAudioData(const float* AudioData, size_t NFrames, size_t NChannels, int64_t pts);
	int32 GetFrameNum();
protected:
	virtual Audio::EAudioMixerStreamDataFormat::Type GetGeneratedPCMDataFormat() const;
private:
	FramePtr Buffer;
	TQueue<FramePtr> QBuffer;
};

UCLASS(ClassGroup = Synth)
class BASEBROWSER_API UWebViewSoundComponent : public UAudioComponent
{
	GENERATED_UCLASS_BODY()
	friend class AWebViewSoundActor;
public:
	void AddAudio(const float* AudioData, size_t NFrames, int64_t pts);
	int32 GetSampleRate();
	int32 GetChannels();
	int32 GetFrameNum();
protected:
	void InitSound(int32 SampleRate, int32 Channels);
	int32 OnGenerateAudio(float* OutAudio, int32 NumSamples);
	void BeginDestroy();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
protected:
	int32 sample_rate;

	UPROPERTY()
	USoundWaveProceduralWebView* SoundWaveProcedural;
};

UCLASS()
class BASEBROWSER_API AWebViewSoundActor : public AActor
{
	GENERATED_UCLASS_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UWebViewSoundComponent* GetSoundComponent();
protected:
	UPROPERTY()
	UWebViewSoundComponent* SoundComponent;
};
