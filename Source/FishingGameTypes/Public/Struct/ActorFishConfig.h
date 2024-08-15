// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "ActorFishConfig.generated.h"

USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FActorFishConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Fish")
	UCurveFloat* FishReelingInCurve = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fish")
	UCurveFloat* FishEscapedCurve = nullptr;
};