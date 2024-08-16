// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/FishSpawnAreaConfig.h"
#include "DataAsset_FishSpawnAreaConfig.generated.h"

/**
 * 
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_FishSpawnAreaConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE FFishSpawnAreaConfig GetFishSpawnAreaConfig() const { return FishSpawnAreaConfig; }
protected:
	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area Config")
	FFishSpawnAreaConfig FishSpawnAreaConfig;
};
