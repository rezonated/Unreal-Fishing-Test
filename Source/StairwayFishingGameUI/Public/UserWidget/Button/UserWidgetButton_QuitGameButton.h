// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/UserWidget_Button.h"
#include "UserWidgetButton_QuitGameButton.generated.h"

/**
 * Button widget to quit the game.
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidgetButton_QuitGameButton : public UUserWidget_Button
{
	GENERATED_BODY()

protected:
	/*
	 * Overrides the button clicked function to quit the game.
	 */
	virtual void OnButtonClicked() override;
};
