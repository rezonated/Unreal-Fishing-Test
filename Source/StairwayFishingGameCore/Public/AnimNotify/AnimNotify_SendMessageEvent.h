// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SendMessageEvent.generated.h"

/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UAnimNotify_SendMessageEvent : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Anim Notify | Send Message Event")
	FGameplayTag MessageTag;
};
