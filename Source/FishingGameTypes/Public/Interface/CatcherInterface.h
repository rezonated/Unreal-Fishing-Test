// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CatcherInterface.generated.h"

UINTERFACE()
class FISHINGGAMETYPES_API UCatcherInterface : public UInterface
{
	GENERATED_BODY()
};

/*
 * Interface for things that can catch catchables
 */
class FISHINGGAMETYPES_API ICatcherInterface
{
	GENERATED_BODY()

public:
	/*
	 * Throws the catcher at the given location.
	 */
	virtual void Throw(const FVector& InCastLocation) = 0;

	/*
	 * Reels the catcher back.
	 */
	virtual void ReelBack() = 0;

	/*
	 * Returns the delegate for when the catcher or its component lands on water.
	 */
	virtual FSimpleDelegate& OnLandsOnWater() = 0;

	/*
	 * Returns the attach point for the catchable.
	 */
	virtual USceneComponent* GetCatchableAttachPoint() = 0;

	/*
	 * Toggles the visibility of the bobber.
	 */
	virtual void ToggleBobberVisibility(const bool& bInShouldBeVisible) = 0;

	/*
	 * Toggles the visibility of the catcher itself.
	 */
	virtual void ToggleCatcherVisibility(const bool& bInShouldBeVisible) = 0;
};