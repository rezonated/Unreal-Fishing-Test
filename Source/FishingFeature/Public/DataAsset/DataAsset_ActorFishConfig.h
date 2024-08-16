// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/ActorFishConfig.h"
#include "DataAsset_ActorFishConfig.generated.h"

/**
 * 
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_ActorFishConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE FActorFishConfig GetActorFishConfig() const { return ActorFishConfig; }
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Fish")
	FActorFishConfig ActorFishConfig;
};
