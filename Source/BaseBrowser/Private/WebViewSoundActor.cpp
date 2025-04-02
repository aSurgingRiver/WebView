// Copyright aXiuShen. All Rights Reserved.


#include "WebViewSoundActor.h"
#include "WebViewLog.h"
#include "AudioDevice.h"
#include <memory>
#include <chrono>

USoundWaveProceduralWebView::USoundWaveProceduralWebView(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SampleByteSize = sizeof(float);
	NumBufferUnderrunSamples = 1024;
	NumSamplesToGeneratePerCallback = 2048;
	Duration = INDEFINITELY_LOOPING_DURATION;
	bLooping = false;
	bProcedural = true;
}

Audio::EAudioMixerStreamDataFormat::Type USoundWaveProceduralWebView::GetGeneratedPCMDataFormat()const {
	return Audio::EAudioMixerStreamDataFormat::Type::Float;
}

int32 USoundWaveProceduralWebView::OnGeneratePCMAudio(TArray<uint8>& OutBuffer, int32 NumSamples) {
	int64_t milli = (FDateTime::UtcNow() - FDateTime(1970, 1, 1)).GetTotalMilliseconds();
	int64_t diff = 9;
	int32 ReadNum = 0;
	int32 ArrayRead = 0;
	int32_t ReadLine = 0;
	for (; ArrayRead < NumSamples; ArrayRead += ReadNum, ReadLine++) {
		if (((Buffer == nullptr) || (Buffer->Data.Num() == 0)) && !QBuffer.Dequeue(Buffer)) {
			break;
		}
		diff = milli - Buffer->pts;
		if (milli < Buffer->pts) break;
		QueueAudio((uint8_t*)Buffer->Data.GetData(), Buffer->Data.Num()*sizeof(float));
		Buffer = nullptr;
	}
	return 0;
}
void  USoundWaveProceduralWebView::AddAudioData(const float* AudioData, size_t NFrames, size_t NChannels, int64_t pts) {
	int NSamples = NFrames * NumChannels;
	FramePtr frame = std::make_shared<Frame>();
	frame->pts = pts;
	frame->Data.SetNumUninitialized(NSamples);
	FMemory::Memcpy(frame->Data.GetData(), AudioData, NSamples * sizeof(float));
	QBuffer.Enqueue(MoveTemp(frame));
}
int32 USoundWaveProceduralWebView::GetFrameNum() {
	return NumSamplesToGeneratePerCallback;
}

/*
* Component that recieves audio from a remote webrtc connection and outputs it into UE using a "synth component".
*/

UWebViewSoundComponent::UWebViewSoundComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SoundWaveProcedural = nullptr;
	sample_rate = 0;
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);
	bAutoActivate = true;
#if 50000<=WEBVIEW_ENGINE_VERSION
	bStopWhenOwnerDestroyed = false;
	bCanPlayMultipleInstances = false;
	bDisableParameterUpdatesWhilePlaying = false;
#endif
};

void UWebViewSoundComponent::InitSound(int32 SampleRate, int32 Channels) {
	sample_rate = SampleRate;
	SoundWaveProcedural = Cast<USoundWaveProceduralWebView>(Sound);
}

void UWebViewSoundComponent::AddAudio(const float* AudioData, size_t NFrames, int64_t pts) {
	SoundWaveProcedural->AddAudioData(AudioData, NFrames,0, pts);
}
int32 UWebViewSoundComponent::GetSampleRate() {
	return sample_rate;
}
int32 UWebViewSoundComponent::GetChannels() {
	return SoundWaveProcedural->NumChannels;
}
int32 UWebViewSoundComponent::GetFrameNum() {
	return SoundWaveProcedural->GetFrameNum();
}

int32 UWebViewSoundComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples) {
#if WEBVIEW_ENGINE_VERSION<50000
	//SoundWaveProcedural->
	return 0;
#else
	return 0;
#endif
}
void UWebViewSoundComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if (0) {
		UE_LOG(WebViewLog,Log,TEXT(""));
	}
}
void UWebViewSoundComponent::BeginDestroy()
{
	Super::BeginDestroy();
}
AWebViewSoundActor::AWebViewSoundActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
};

// Called when the game starts or when spawned
void AWebViewSoundActor::BeginPlay()
{
	Super::BeginPlay();
	//GetSoundComponent()->SetupAttachment(RootComponent);
	GetSoundComponent()->Play();
}

UWebViewSoundComponent* AWebViewSoundActor::GetSoundComponent() {
	if (!SoundComponent) {
		int NumChannels = 1;
		uint32 SampleRate = 48000;
		USoundWaveProceduralWebView* SoundWaveProcedural = NewObject<USoundWaveProceduralWebView>(this);
		SoundWaveProcedural->NumChannels = NumChannels;
		SoundWaveProcedural->SetSampleRate(SampleRate);
		SoundWaveProcedural->Duration = INDEFINITELY_LOOPING_DURATION;
		SoundWaveProcedural->bLooping = false;
		SoundWaveProcedural->bProcedural = true;

		FAudioDevice::FCreateComponentParams params(GetWorld(),this);
		params.bAutoDestroy = false;
		params.bPlay = false;
		params.AudioComponentClass = UWebViewSoundComponent::StaticClass();
		SoundComponent = Cast<UWebViewSoundComponent>(FAudioDevice::CreateComponent(SoundWaveProcedural, params));
		SoundComponent->SetVolumeMultiplier(1.0f);
		SoundComponent->SetPitchMultiplier(1.0f);
		SoundComponent->bAllowSpatialization = true;
		SoundComponent->bIsUISound = true;
		SoundComponent->bAutoDestroy = true;
		SoundComponent->bIgnoreForFlushing = false;
		SoundComponent->SubtitlePriority = SoundWaveProcedural->GetSubtitlePriority();
		SoundComponent->bStopWhenOwnerDestroyed = true;
		SoundComponent->InitSound(SampleRate, NumChannels);
		SoundComponent->RegisterComponent();
	}
	return SoundComponent;
}

