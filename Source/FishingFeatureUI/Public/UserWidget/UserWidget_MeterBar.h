// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_MeterBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class FISHINGFEATUREUI_API UUserWidget_MeterBar : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void SetProgress(const float InProgress);

	virtual void ToggleVisibility(const bool bInShouldBeVisible);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Meter Bar", meta = (BindWidget))
	UProgressBar* ProgressBar_MeterBar = nullptr;
};
