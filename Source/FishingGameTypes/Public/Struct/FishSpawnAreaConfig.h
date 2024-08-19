// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FishSpawnAreaConfig.generated.h"

/*
 * Struct that holds data to configure the fish spawn area.
 */
USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FFishSpawnAreaConfig
{
	GENERATED_BODY()

	/*
	 * Fish actor class, used to spawn the fish actor.
	 * Needs to load the fish actor class from soft class pointer via async loading.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area", meta=(MustImplement="CatchableInterface"))
	TSoftClassPtr<AActor> FishActorClass = nullptr;

	/*
	 * Number of fish to spawn in the fish spawn area.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area")
	int32 FishSpawnAmount = 10;
};