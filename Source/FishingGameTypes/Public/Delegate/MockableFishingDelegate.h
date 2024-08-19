// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Delegate/PlayerActionInputDelegate.h"

/*
 * Delegate for mock fishing, returns a bool value indicating if the mock was successful or not.
 */
DECLARE_DELEGATE_OneParam(FOnMockFishing, const bool& /*bSuccess*/);