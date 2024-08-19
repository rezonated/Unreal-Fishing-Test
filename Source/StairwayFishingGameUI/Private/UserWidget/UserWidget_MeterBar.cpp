// Vanan Andreas - 2024


#include "UserWidget/UserWidget_MeterBar.h"
#include "Components/ProgressBar.h"

void UUserWidget_MeterBar::SetProgress(const float InProgress)
{
	if (!ProgressBar_MeterBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("MeterBar is not set! Please make sure to name it ProgressBar_MeterBar in the details panel. Returning."));
		return;
	}

	ProgressBar_MeterBar->SetPercent(InProgress);
}

void UUserWidget_MeterBar::ToggleVisibility(const bool bInShouldBeVisible)
{
	if (!ProgressBar_MeterBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("MeterBar is not set! Please make sure to name it ProgressBar_MeterBar in the details panel. Returning."));
		return;
	}

	const ESlateVisibility NewVisibility = bInShouldBeVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;

	const ESlateVisibility CurrentVisibility = ProgressBar_MeterBar->GetVisibility();

	if (NewVisibility == CurrentVisibility)
	{
		return;
	}

	ProgressBar_MeterBar->SetVisibility(NewVisibility);
}