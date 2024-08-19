// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Delegate/PlayerActionInputDelegate.h"
#include "UObject/Interface.h"
#include "PlayerActionInputInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class FISHINGGAMETYPES_API UPlayerActionInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FISHINGGAMETYPES_API IPlayerActionInputInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FOnPlayerActionInput& OnCastActionStarted() = 0;
	virtual FOnPlayerActionInput& OnCastActionTriggered() = 0;
	virtual FOnPlayerActionInput& OnCastActionCompleted() = 0;
};