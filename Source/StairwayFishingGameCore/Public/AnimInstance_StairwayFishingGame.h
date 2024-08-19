// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "Runtime/VAAnyUnreal.h"
#include "AnimInstance_StairwayFishingGame.generated.h"

class UVAGameplayMessaging_ListenForGameplayMessages;
/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UAnimInstance_StairwayFishingGame : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;

	virtual void BeginDestroy() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AnimationSet")
	TMap<FGameplayTag, UAnimMontage*> TagToMontageMap;

	UPROPERTY(Transient)
	FGameplayTag StateTag;

	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* StateChangeMessageListenerAsync = nullptr;

	UFUNCTION()
	void OnStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	void StateTagChanged();
};