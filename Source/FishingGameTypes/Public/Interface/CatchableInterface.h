// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CatchableInterface.generated.h"

UINTERFACE()
class FISHINGGAMETYPES_API UCatchableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for things that can be caught.
 */
class FISHINGGAMETYPES_API ICatchableInterface
{
	GENERATED_BODY()

public:
	/*
	 * Reel in self to the given location.
	 */
	virtual void ReeledIn(const FVector& RodLocation) = 0;

	/*
	 * Handle reel out.
	 */
	virtual void Escape() = 0;

	/*
	 * Handle when catchable is caught.
	 */
	virtual void Catch(USceneComponent* InCatchingRod) = 0;

	/*
	 * Sets the spawn area center and extent.
	 */
	virtual void SetSpawnAreaCenterAndExtent(const FVector& InCenter, const FVector& InContainingSpawnAreaBoxExtent) = 0;
};