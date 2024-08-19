// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"

/*
 * Delegate for player action input, returns a float value indicating the elapsed time of the player action input.
 */
DECLARE_DELEGATE_OneParam(FOnPlayerActionInput, const float& /*ElapsedTime*/);