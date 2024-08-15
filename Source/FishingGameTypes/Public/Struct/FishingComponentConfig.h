// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FishingComponentConfig.generated.h"

USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FFishingComponentConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	float MaximumTimeToCast = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	float MinimumCastDistance = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	float MaximumCastDistance = 600.f;

	UPROPERTY(EditDefaultsOnly, Category = "Decals")
	float CastRadius = 75.f;

	UPROPERTY(EditDefaultsOnly, Category = "Decals")
	float TimeToFish = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Decals")
	TSubclassOf<AActor> TargetActorDecalClass = nullptr;
};