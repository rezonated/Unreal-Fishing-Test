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

class FISHINGGAMETYPES_API IMockableFishingInterface
{
	GENERATED_BODY()
public:
	virtual void MockCast(const float& InElapsedTime) = 0;

	virtual void MockCastEnd() = 0;

	virtual FOnMockFishing& OnMockAbleToCatchFishDone() = 0;

	virtual FOnMockFishing& OnMockBobberLandsOnWater() = 0;

	virtual FOnMockFishing& OnMockReelInDone() = 0;
};
