// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_FishSpawnArea.generated.h"

struct FStreamableHandle;
class UDataAsset_FishSpawnAreaConfig;
class UBoxComponent;

UCLASS()
class FISHINGFEATURE_API AActor_FishSpawnArea : public AActor
{
	GENERATED_BODY()

public:
	AActor_FishSpawnArea();
	
protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	void RequestLoadFishAssetSoftClass();
	void OnFishSpawnAssetLoaded();

	void SpawnFishes(const int32& InFishSpawnAmount, const FVector& InCenterLocation, const FVector& InBoxExtent, UClass* InFishActorClass);
	
	UPROPERTY(VisibleAnywhere, Category = "Fish Spawn Area")
	USceneComponent* SpawnAreaRoot = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Fish Spawn Area")
	UBoxComponent* SpawnAreaBox = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area")
	UDataAsset_FishSpawnAreaConfig* FishSpawnAreaConfigData = nullptr;

	TSharedPtr<FStreamableHandle> FishSpawnAssetHandle = nullptr;
};
