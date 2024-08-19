// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "SwitchableFishingViewInterface.generated.h"

UINTERFACE()
class FISHINGGAMETYPES_API USwitchableFishingViewInterface : public UInterface
{
	GENERATED_BODY()
};

/*
 * Interface for things that can switch the view
 */
class FISHINGGAMETYPES_API ISwitchableFishingViewInterface
{
	GENERATED_BODY()

public:
	/*
	 * Sets the fishing view based on the given fishing game loop state.
	 */
	virtual void SetFishingView(const FGameplayTag& InFishingGameLoopState) = 0;
};