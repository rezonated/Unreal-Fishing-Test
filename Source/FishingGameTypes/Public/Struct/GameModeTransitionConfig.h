// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameModeTransitionConfig.generated.h"

/*
 * Struct that holds data to configure the game mode transition.
 */
USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FGameModeTransitionConfig
{
	GENERATED_BODY()

	/*
	 * Time for initial camera fade in.
	 */
	UPROPERTY(EditAnywhere, Category = "Game Mode Transition")
	float InitialGameModeTransitionTime = .5f;

	/*
	 * Time for camera fade in.
	 */
	UPROPERTY(EditAnywhere, Category = "Game Mode Transition")
	float TransitionFadeInTime = 2.f;

	/*
	 * Time for camera fade out.
	 */
	UPROPERTY(EditAnywhere, Category = "Game Mode Transition")
	float TransitionFadeOutTime = 1.f;
};