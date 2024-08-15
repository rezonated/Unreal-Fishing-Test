// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerActionInterface.generated.h"

DECLARE_DELEGATE_OneParam(FPlayerActionDelegate, float /*ElapsedTime*/);

UINTERFACE()
class UPlayerActionInterface : public UInterface
{
	GENERATED_BODY()
};

class STAIRWAYFISHINGGAMECORE_API IPlayerActionInterface
{
	GENERATED_BODY()

public:
	virtual FPlayerActionDelegate GetOnCastStartedDelegate() const = 0;
	virtual FPlayerActionDelegate GetOnTriggeredDelegate() const = 0;
	virtual FPlayerActionDelegate GetOnCastFinishedDelegate() const = 0;
};
