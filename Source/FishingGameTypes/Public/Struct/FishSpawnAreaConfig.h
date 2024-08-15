﻿#pragma once

#include "CoreMinimal.h"
#include "FishSpawnAreaConfig.generated.h"

USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FFishSpawnAreaConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area")
	TSoftClassPtr<AActor> FishActorClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area")
	int32 FishSpawnAmount = 10;
};