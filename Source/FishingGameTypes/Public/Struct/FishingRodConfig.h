// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FishingRodConfig.generated.h"

USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FFishingRodConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UCurveFloat* BobberReelInCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UCurveFloat* BobberReelOutCurve = nullptr;
};