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
UCLASS(Blueprintable)
class STAIRWAYFISHINGGAMEUI_API UUserWidgetButton_MessageEmittingButton : public UUserWidget_Button
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Message Emitting Button", meta=(ExposeOnSpawn = true))
	FGameplayTag ChannelTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Message Emitting Button", meta=(ExposeOnSpawn = true))
	FVAAnyUnreal MessagePayload;
	
protected:
	virtual void OnButtonClicked() override;
};
