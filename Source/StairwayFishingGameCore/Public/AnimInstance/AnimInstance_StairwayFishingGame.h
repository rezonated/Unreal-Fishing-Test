// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "Runtime/VAAnyUnreal.h"
#include "AnimInstance_StairwayFishingGame.generated.h"

class UVAGameplayMessaging_ListenForGameplayMessages;
/**
 * Anim instance class for the game pawn. Handles the fishing game loop state and play the appropriate anim montage from the tag to montage map.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UAnimInstance_StairwayFishingGame : public UAnimInstance
{
	GENERATED_BODY()

public:
	/*
	 * Listens for the game loop state change message and changes the state tag to the default state of idling.
	 */
	virtual void NativeBeginPlay() override;

	/*
	 * Cleans up the state change message listener async.
	 */
	virtual void BeginDestroy() override;

protected:
	/*
	 * Map of fishing game loop state to anim montage.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "AnimationSet")
	TMap<FGameplayTag, UAnimMontage*> TagToMontageMap;

	/*
	 * Current fishing game loop state.
	 */
	UPROPERTY(Transient)
	FGameplayTag StateTag;

	/*
	 * Cached state change message listener async.
	 */
	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* StateChangeMessageListenerAsync = nullptr;

	/*
	 * Handles the state change message.
	 */
	UFUNCTION()
	void OnStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	/*
	 * Handles when the state tag changes, play the appropriate anim montage.
	 */
	void StateTagChanged();
};