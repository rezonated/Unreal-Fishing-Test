// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/GameModeTransitionConfig.h"
#include "DataAsset_GameModeTransitionConfig.generated.h"

/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API UDataAsset_GameModeTransitionConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE FGameModeTransitionConfig GetGameModeTransitionConfig() const { return GameModeTransitionConfig; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Transition")
	FGameModeTransitionConfig GameModeTransitionConfig;
};