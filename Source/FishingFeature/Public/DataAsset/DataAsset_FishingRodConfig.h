// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/FishingRodConfig.h"
#include "DataAsset_FishingRodConfig.generated.h"

/**
 * Data asset for configuring the fishing rod.
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_FishingRodConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/*
	 * Returns the fishing rod config.
	 */
	FORCEINLINE FFishingRodConfig GetFishingRodConfig() const { return FishingRodConfig; }

protected:
	/*
	 * The fishing rod config.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Bobber Curve")
	FFishingRodConfig FishingRodConfig;
};