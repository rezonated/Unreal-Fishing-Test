// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "ActorFishConfig.generated.h"

/*
 * Struct that holds data to configure the fish actor.
 */
USTRUCT(BlueprintType)
struct FISHINGGAMETYPES_API FActorFishConfig
{
	GENERATED_BODY()

	/*
	 * Curve float for when the fish is reeling in.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish")
	UCurveFloat* FishReelingInCurve = nullptr;

	/*
	 * Curve float for when the fish escaped.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish")
	UCurveFloat* FishEscapedCurve = nullptr;

	/*
	 * Rotation speed of the fish.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish")
	float FishRotationSpeed = 1.f;

	/*
	 * Move speed of the fish.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish")
	float FishMoveSpeed = .1f;

	/*
	 * Wander target radius of the fish.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish")
	float FishWanderTargetRadius = 10.f;

	/*
	 * Sound for when the fish bites when it is caught.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish")
	USoundBase* FishBiteSound = nullptr;
};