// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "Runtime/VAAnyUnreal.h"
#include "AnimInstance_StairwayFishingGame.generated.h"

/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UAnimInstance_StairwayFishingGame : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AnimationSet")
	TMap<FGameplayTag, UAnimMontage*> TagToMontageMap;

	UPROPERTY()
	FGameplayTag StateTag;	
	
	UFUNCTION()
	void OnStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	void StateTagChanged();
};
