// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/GameModeTransitionConfig.h"
#include "DataAsset_GameModeTransitionConfig.generated.h"

/**
 * Data asset for configuring the game mode transition.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UDataAsset_GameModeTransitionConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/*
	 * Returns the game mode transition config.
	 */
	FORCEINLINE FGameModeTransitionConfig GetGameModeTransitionConfig() const { return GameModeTransitionConfig; }

protected:
	/*
	 * The game mode transition config.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Transition")
	FGameModeTransitionConfig GameModeTransitionConfig;
};