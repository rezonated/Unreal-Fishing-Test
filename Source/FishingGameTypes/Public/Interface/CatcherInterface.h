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

class FISHINGGAMETYPES_API ICatcherInterface
{
	GENERATED_BODY()
public:
	virtual void Throw(const FVector& InCastLocation) = 0;

	virtual void ReelBack() = 0;

	virtual FSimpleDelegate& OnLandsOnWater() = 0;

	virtual USceneComponent* GetCatchableAttachPoint() = 0;

	virtual void ToggleBobberVisibility(const bool& bInShouldBeVisible) = 0;
};
