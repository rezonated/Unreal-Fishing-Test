// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_MeterBar.generated.h"

class UProgressBar;
/**
 * Generic user widget for the meter bar containing progress bar.
 * Only bare necessities are implemented, setting the progress and toggling the visibility.
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_MeterBar : public UUserWidget
{
	GENERATED_BODY()

public:
	/*
	 * Sets the progress value of the progress bar.
	 */
	virtual void SetProgress(const float InProgress);

	/*
	 * Toggles the visibility of the progress bar.
	 */
	virtual void ToggleVisibility(const bool bInShouldBeVisible);

protected:
	/*
	 * Progress bar for the meter bar.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Meter Bar", meta = (BindWidget))
	UProgressBar* ProgressBar_MeterBar = nullptr;
};