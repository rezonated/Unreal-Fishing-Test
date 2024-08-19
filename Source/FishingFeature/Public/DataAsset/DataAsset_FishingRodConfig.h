// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/FishingRodConfig.h"
#include "DataAsset_FishingRodConfig.generated.h"

/**
 * 
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_FishingRodConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE FFishingRodConfig GetFishingRodConfig() const { return FishingRodConfig; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Bobber Curve")
	FFishingRodConfig FishingRodConfig;
};