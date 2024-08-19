// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CatchableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class FISHINGGAMETYPES_API UCatchableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FISHINGGAMETYPES_API ICatchableInterface
{
	GENERATED_BODY()

public:
	virtual void ReeledIn(const FVector& RodLocation) = 0;
	virtual void Escape() = 0;
	virtual void Catch(USceneComponent* InCatchingRod) = 0;

	virtual void SetSpawnAreaCenterAndExtent(const FVector& InCenter, const FVector& InContainingSpawnAreaBoxExtent) = 0;
};