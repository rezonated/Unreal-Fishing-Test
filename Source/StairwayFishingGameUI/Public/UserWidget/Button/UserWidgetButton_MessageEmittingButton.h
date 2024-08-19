// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Runtime/VAAnyUnreal.h"
#include "UserWidget/UserWidget_Button.h"
#include "UserWidgetButton_MessageEmittingButton.generated.h"

/**
 * Button widget to emit a message via channel and a payload.
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidgetButton_MessageEmittingButton : public UUserWidget_Button
{
	GENERATED_BODY()
protected:
	/*
	 * Channel tag for the message.
	 */
	UPROPERTY()
	FGameplayTag ChannelTag;

	/*
	 * Payload for the message.
	 */
	UPROPERTY()
	FVAAnyUnreal MessagePayload = FGameplayTag();

	/*
	 * Overrides the button clicked function to emit the message.
	 */
	virtual void OnButtonClicked() override;
};
