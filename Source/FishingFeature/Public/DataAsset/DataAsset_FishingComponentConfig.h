// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/FishingComponentConfig.h"
#include "DataAsset_FishingComponentConfig.generated.h"

/**
 * 
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_FishingComponentConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE FFishingComponentConfig GetFishingComponentConfig() const { return FishingComponentConfig; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Fishing Component Config")
	FFishingComponentConfig FishingComponentConfig;
};
