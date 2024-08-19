// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Delegate/MockableFishingDelegate.h"
#include "UObject/Interface.h"
#include "MockableFishingInterface.generated.h"

UINTERFACE()
class FISHINGGAMETYPES_API UMockableFishingInterface : public UInterface
{
	GENERATED_BODY()
};

/*
 * Interface for mock fishing components.
 */
class FISHINGGAMETYPES_API IMockableFishingInterface
{
	GENERATED_BODY()
public:
	/*
	 * Mocks the casting of the fishing rod.
	 */
	virtual void MockCast(const float& InElapsedTime) = 0;

	/*
	 * Mocks the end of the casting of the fishing rod.
	 */
	virtual void MockCastEnd() = 0;

	/*
	 * Returns the mock able to catch fish done delegate.
	 */
	virtual FOnMockFishing& OnMockAbleToCatchFishDone() = 0;

	/*
	 * Returns the mock bobber lands on water delegate.
	 */
	virtual FOnMockFishing& OnMockBobberLandsOnWater() = 0;

	/*
	 * Returns the mock reel in done delegate.
	 */
	virtual FOnMockFishing& OnMockReelInDone() = 0;
};
