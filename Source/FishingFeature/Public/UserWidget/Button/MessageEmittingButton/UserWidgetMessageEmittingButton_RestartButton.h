// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "StairwayFishingGameUI/Public/UserWidget/Button/UserWidgetButton_MessageEmittingButton.h"
#include "UserWidgetMessageEmittingButton_RestartButton.generated.h"

/**
 * User widget generic button class that emits a restart message when clicked.
 * By default, the button is configured to emit the fishing game loop state fishing message to restart the fishing game loop.
 */
UCLASS()
class FISHINGFEATURE_API UUserWidgetMessageEmittingButton_RestartButton : public UUserWidgetButton_MessageEmittingButton
{
	GENERATED_BODY()
protected:
	/*
	 * Sets up the button pre construct by setting the channel tag and message payload for restarting the fishing game loop.
	 */
	virtual void NativePreConstruct() override;
};
