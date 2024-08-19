// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Button.generated.h"

class UOverlay;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_Button : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnButtonClicked(){}

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* Button_Current = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* TextBlock_Current = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category = "Button")
	FText ButtonText = FText();
};