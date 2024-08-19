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
 * Game mode that handles the game loop state changes and transition based on it.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API AGameModeBase_StairwayFishingGame : public AGameModeBase
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, disables the ticking.
	 */
	AGameModeBase_StairwayFishingGame();

protected:
	/*
	 * Cached game mode transition config asset, tweak the data asset to your liking.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Transition")
	UDataAsset_GameModeTransitionConfig* GameModeTransitionConfigAsset = nullptr;

	/*
	 * Listens for the game loop state changes and do the initial fade in.
	 */
	virtual void BeginPlay() override;

	/*
	 * Handles the game loop state changes.
	 */
	void OnFishingGameLoopStateChanged(const FGameplayTag& FishingGameLoopState);

	/*
	 * Triggers the screen fade in out.
	 */
	void TriggerScreenFadeInOut(APlayerCameraManager* InPlayerCameraManager, const FGameplayTag& InFishingGameLoopState, const float& TransitionFadeInTime, const float& TransitionFadeOutTime, ISwitchableFishingViewInterface* InSwitchableFishingView) const;

	/*
	 * Listens for the game loop state changes.
	 */
	void ListenForGameLoopStateChanges();

	/*
	 * Toggles the player controller mode.
	 */
	void TogglePlayerControllerMode(APlayerController* InPlayerController, const bool& bIsEnabled) const;

	/*
	 * Initial fade in.
	 */
	void InitialFadeIn();
};