// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FishingComponentConfig.generated.h"

/*
 * Struct that holds data to configure the fishing component.
 */
USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FFishingComponentConfig
{
	GENERATED_BODY()

	/*
	 * Maximum time to cast the fishing rod, used to clamp the casting time.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	float MaximumTimeToCast = 3.f;

	/*
	 * Minimum cast distance of the fishing rod, used to clamp the casting distance.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	float MinimumCastDistance = 150.f;

	/*
	 * Maximum cast distance of the fishing rod, used to clamp the casting distance.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	float MaximumCastDistance = 600.f;

	/*
	 * Cast radius of the fishing rod, used to determine how big the area around the casting location is to get nearest catchable.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Decals")
	float CastRadius = 75.f;

	/*
	 * Time to fish, used to determine how long player should wait before reeling in the fish.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Decals")
	float TimeToFish = 3.f;

	/*
	 * Decal actor class, used to spawn the decal actor.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Decals")
	TSubclassOf<AActor> TargetActorDecalClass = nullptr;

	/*
	 * Owner skeletal mesh, used to get the skeletal mesh component info for fishing pole and carry fish socket names.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	USkeletalMesh* OwnerSkeletalMesh = nullptr;

	/*
	 * Fishing pole socket name, used to get the skeletal mesh component info for fishing pole and carry fish socket names.
	 * Set from custom detail panel based on the skeletal mesh assigned.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	FName FishingPoleSocketName = "";

	/*
	 * Carry fish socket name, used to get the skeletal mesh component info for fishing pole and carry fish socket names.
	 * Set from custom detail panel based on the skeletal mesh assigned.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	FName CarryFishSocketName = "";

	/*
	 * Fishing rod actor class, used to spawn the fishing rod actor.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta=(MustImplement="CatcherInterface"))
	TSoftClassPtr<AActor> FishingRodActorClass = nullptr;
};