// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FishingGameLoopState.generated.h"

UENUM(BlueprintType)
enum class EFishingGameLoopState : uint8
{
	Fishing UMETA(DisplayName = "Fishing"),
	ShowFish UMETA(DisplayName = "Show Fish")
};