// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Runtime/VAAnyUnreal.h"
#include "UserWidget/UserWidget_Button.h"
#include "UserWidgetButton_MessageEmittingButton.generated.h"

/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidgetButton_MessageEmittingButton : public UUserWidget_Button
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FGameplayTag ChannelTag;

	UPROPERTY()
	FVAAnyUnreal MessagePayload = FGameplayTag();
	
	virtual void OnButtonClicked() override;
};
