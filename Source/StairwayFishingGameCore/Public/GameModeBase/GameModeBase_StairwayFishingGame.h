// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_StairwayFishingGame.generated.h"

class ISwitchableFishingViewInterface;
class UDataAsset_GameModeTransitionConfig;
class APostProcessVolume;
/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API AGameModeBase_StairwayFishingGame : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeBase_StairwayFishingGame();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Transition")
	UDataAsset_GameModeTransitionConfig* GameModeTransitionConfigAsset = nullptr;

	virtual void BeginPlay() override;

	void OnFishingGameLoopStateChanged(const FGameplayTag& FishingGameLoopState);

	void TriggerScreenFadeInOut(APlayerCameraManager* InPlayerCameraManager, const FGameplayTag& InFishingGameLoopState, const float& TransitionFadeInTime, const float& TransitionFadeOutTime, ISwitchableFishingViewInterface* InSwitchableFishingView) const;

	void ListenForGameLoopStateChanges();

	void TogglePlayerControllerMode(APlayerController* InPlayerController, const bool& bIsEnabled) const;
};