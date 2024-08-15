// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_MeterBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS(Abstract)
class FISHINGFEATURE_API UUserWidget_MeterBar : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void SetProgress(const float InProgress);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Meter Bar", meta = (BindWidget))
	UProgressBar* MeterBar = nullptr;
};
