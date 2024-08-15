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
	float MinimumCastDistance = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	float MaximumCastDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Decals")
	TSubclassOf<AActor> TargetActorDecalClass;
};