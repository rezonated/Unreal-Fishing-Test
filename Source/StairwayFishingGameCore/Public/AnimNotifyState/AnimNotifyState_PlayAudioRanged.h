// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_PlayAudioRanged.generated.h"

/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UAnimNotifyState_PlayAudioRanged : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float                                        TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Anim Notify State | Play Audio Ranged")
	USoundBase* SoundToPlay = nullptr;

	UPROPERTY(Transient)
	UAudioComponent* CurrentAudioComponent = nullptr;
};