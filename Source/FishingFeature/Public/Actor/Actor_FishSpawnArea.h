// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_FishSpawnArea.generated.h"

struct FStreamableHandle;
class UDataAsset_FishSpawnAreaConfig;
class UBoxComponent;

/*
 * Fish spawn area actor class, handles fish spawning and spawning fishes inside a box component as a fish spawn area and area for fish to swim in.
 *
 * It has a scene component for the box component and a data asset for the fish spawn area config data. Tweak the data asset to your liking.
 *
 * Keep in mind that the fish is stored as a soft class, so it's not possible to spawn fishes from the fish spawn area actor class directly.
 * It's recommended to use async load via StreamableManager instead.
 */
UCLASS()
class FISHINGFEATURE_API AActor_FishSpawnArea : public AActor
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, constructs the subobjects and components necessary.
	 */
	AActor_FishSpawnArea();

protected:
	/*
	 * Begin play, requests the fish asset soft class and loads it.
	 */
	virtual void BeginPlay() override;

	/*
	 * Begin destroy, cancels the fish asset soft class request.
	 */
	virtual void BeginDestroy() override;

	/*
	 * Requests the fish asset soft class and attempts loads it.
	 */
	void RequestLoadFishAssetSoftClass();

	/*
	 * Called when the fish asset soft class is loaded, spawns fishes inside the fish spawn area and gets the fish spawn area config data.
	 */
	void OnFishSpawnAssetLoaded();

	/*
	 * Actual fish spawning function, spawns fishes inside the fish spawn area and initializes the fishes with the fish spawn area config data.
	 */
	void SpawnFishes(const int32& InFishSpawnAmount, const FVector& InCenterLocation, const FVector& InBoxExtent, UClass* InFishActorClass);

	/*
	 * The fish spawn area's root scene component, acts as the fish spawn area's center.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Fish Spawn Area")
	USceneComponent* SpawnAreaRoot = nullptr;

	/*
	 * The fish spawn area's box component, acts as the fish spawn area's extent and area for fish to swim and spawn in.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Fish Spawn Area")
	UBoxComponent* SpawnAreaBox = nullptr;

	/*
	 * The fish spawn area's data asset, contains the fish spawn area's configuration data. Tweak the data asset to your liking.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish Spawn Area")
	UDataAsset_FishSpawnAreaConfig* FishSpawnAreaConfigData = nullptr;

	/*
	 * The fish spawn area's asset handle, used for the fish asset soft class request.
	 */
	TSharedPtr<FStreamableHandle> FishSpawnAssetHandle = nullptr;
};