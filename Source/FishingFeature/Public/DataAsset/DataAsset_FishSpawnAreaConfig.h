// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/FishSpawnAreaConfig.h"
#include "DataAsset_FishSpawnAreaConfig.generated.h"

/**
 * Data asset for configuring the fish spawn area.
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_FishSpawnAreaConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/*
	 * Returns the fish spawn area config.
	 */
	FORCEINLINE FFishSpawnAreaConfig GetFishSpawnAreaConfig() const { return FishSpawnAreaConfig; }

protected:
	/*
	 * The fish spawn area config.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area Config")
	FFishSpawnAreaConfig FishSpawnAreaConfig;
};