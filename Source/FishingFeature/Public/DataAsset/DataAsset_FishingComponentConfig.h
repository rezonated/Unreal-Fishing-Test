// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/FishingComponentConfig.h"
#include "DataAsset_FishingComponentConfig.generated.h"

/**
 * Data asset for configuring the fishing component.
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_FishingComponentConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/*
	 * Returns the fishing component config.
	 */
	FORCEINLINE FFishingComponentConfig GetFishingComponentConfig() const { return FishingComponentConfig; }

protected:
	/*
	 * The fishing component config.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Fishing Component Config")
	FFishingComponentConfig FishingComponentConfig;
};