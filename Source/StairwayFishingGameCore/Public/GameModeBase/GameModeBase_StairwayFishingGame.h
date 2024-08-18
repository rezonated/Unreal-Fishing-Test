// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Enum/FishingGameLoopState.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_StairwayFishingGame.generated.h"

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

	void OnFishingGameLoopStateChanged(const EFishingGameLoopState& FishingGameLoopState);

	void ListenForGameLoopStateChanges();
};