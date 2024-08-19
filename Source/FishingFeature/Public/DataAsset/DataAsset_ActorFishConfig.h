// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/ActorFishConfig.h"
#include "DataAsset_ActorFishConfig.generated.h"

/**
 * Data asset for configuring the fish actor.
 */
UCLASS()
class FISHINGFEATURE_API UDataAsset_ActorFishConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/*
	 * Returns the actor fish config.
	 */
	FORCEINLINE FActorFishConfig GetActorFishConfig() const { return ActorFishConfig; }

protected:
	/*
	 * The actor fish config.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Fish")
	FActorFishConfig ActorFishConfig;
};