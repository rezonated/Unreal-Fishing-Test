// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Delegate/PlayerActionInputDelegate.h"
#include "UObject/Interface.h"
#include "PlayerActionInputInterface.generated.h"

UINTERFACE()
class FISHINGGAMETYPES_API UPlayerActionInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for player action input, handles the player action input events.
 */
class FISHINGGAMETYPES_API IPlayerActionInputInterface
{
	GENERATED_BODY()

public:
	/*
	 * Returns the delegate for when the player action input starts.
	 */
	virtual FOnPlayerActionInput& OnCastActionStarted() = 0;

	/*
	 * Returns the delegate for when the player action input is triggered.
	 */
	virtual FOnPlayerActionInput& OnCastActionTriggered() = 0;

	/*
	 * Returns the delegate for when the player action input is completed.
	 */
	virtual FOnPlayerActionInput& OnCastActionCompleted() = 0;
};