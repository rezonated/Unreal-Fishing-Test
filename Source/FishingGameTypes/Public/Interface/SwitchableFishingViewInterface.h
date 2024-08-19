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

class FISHINGGAMETYPES_API ISwitchableFishingViewInterface
{
	GENERATED_BODY()

public:
	virtual void SetFishingView(const FGameplayTag& InFishingGameLoopState) = 0;
};