// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameModeTransitionConfig.generated.h"

USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FGameModeTransitionConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Game Mode Transition")
	float InitialGameModeTransitionTime = .5f;

	UPROPERTY(EditAnywhere, Category = "Game Mode Transition")
	float TransitionFadeInTime = 2.f;

	UPROPERTY(EditAnywhere, Category = "Game Mode Transition")
	float TransitionFadeOutTime = 1.f;
};