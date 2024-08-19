// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_PlayAudioRanged.generated.h"

/**
 * Generic anim notify state that plays an audio from begin notify to end notify.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UAnimNotifyState_PlayAudioRanged : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	/*
	 * Starts playing the audio.
	 */
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	/*
	 * Stops playing the audio.
	 */
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	/*
	 * Sound to play.
	 */
	UPROPERTY(EditAnywhere, Category = "Anim Notify State | Play Audio Ranged")
	USoundBase* SoundToPlay = nullptr;

	UPROPERTY(Transient)
	UAudioComponent* CurrentAudioComponent = nullptr;
};