// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/UserWidget_Button.h"
#include "UserWidgetButton_QuitGameButton.generated.h"

/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidgetButton_QuitGameButton : public UUserWidget_Button
{
	GENERATED_BODY()

protected:
	virtual void OnButtonClicked() override;
};
