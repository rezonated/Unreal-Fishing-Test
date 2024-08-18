// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_FishingDoneScreen.generated.h"

class UUserWidget_Button;
/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_FishingDoneScreen : public UUserWidget
{
	GENERATED_BODY()
protected:
	void         CollapseWidgetButtonsContainer() const;
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UWidget* Widget_ButtonsContainer = nullptr;
};
