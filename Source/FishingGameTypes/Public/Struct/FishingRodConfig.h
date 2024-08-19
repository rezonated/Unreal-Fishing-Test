// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FishingRodConfig.generated.h"

/*
 * Struct that holds data to configure the fishing rod.
 */
USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FFishingRodConfig
{
	GENERATED_BODY()

	/*
	 * Curve float for when the bobber is reeling in.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UCurveFloat* BobberReelInCurve = nullptr;

	/*
	 * Curve float for when the bobber is reeling out.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UCurveFloat* BobberReelOutCurve = nullptr;
};