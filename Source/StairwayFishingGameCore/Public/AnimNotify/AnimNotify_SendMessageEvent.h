// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SendMessageEvent.generated.h"

/**
 * Generic anim notify that sends a message via channel tag.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UAnimNotify_SendMessageEvent : public UAnimNotify
{
	GENERATED_BODY()

public:
	/*
	 * Sends the message via channel tag.
	 */
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	/*
	 * Channel tag for the message.
	 */
	UPROPERTY(EditAnywhere, Category = "Anim Notify | Send Message Event")
	FGameplayTag ChannelTag;
};