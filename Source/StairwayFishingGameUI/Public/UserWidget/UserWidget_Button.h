// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Button.generated.h"

class UOverlay;
class UTextBlock;
class UButton;
/**
 * Generic user widget for the button containing a button and a text block that already have a virtual function for when the button is clicked.
 * Inherited class can override the virtual function to handle the button click.
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_Button : public UUserWidget
{
	GENERATED_BODY()
protected:
	/*
	 * Forces the construction of the widget to set the text of the button based on button text upon pre-construction of the widget.
	 */
	virtual void NativePreConstruct() override;

	/*
	 * Forces the construction of the widget to set the text of the button based on button text upon construction of the widget.
	 */
	virtual void NativeConstruct() override;

	/*
	 * Virtual function for when the button is clicked, inherited class can override this function to handle the button click.
	 */
	UFUNCTION()
	virtual void OnButtonClicked(){}

	/*
	 * Current button for the button widget.
	 */
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* Button_Current = nullptr;

	/*
	 * Current text block for the button widget.
	 */
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* TextBlock_Current = nullptr;

	/*
	 * Text for the button.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category = "Button")
	FText ButtonText = FText();
};