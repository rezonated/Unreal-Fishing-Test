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

	UPROPERTY(EditAnywhere, Category = "Fish")
	float FishRotationSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Fish")
	float FishMoveSpeed = .1f;

	UPROPERTY(EditAnywhere, Category = "Fish")
	float FishWanderTargetRadius = 10.f;
};