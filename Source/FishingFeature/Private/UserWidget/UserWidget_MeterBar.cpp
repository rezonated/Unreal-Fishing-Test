// Vanan Andreas - 2024


#include "UserWidget/UserWidget_MeterBar.h"

#include "Components/ProgressBar.h"

void UUserWidget_MeterBar::SetProgress(const float InProgress)
{
	if (!MeterBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("MeterBar is not set! Please make sure to name it MeterBar in the details panel. Returning."));
		return;
	}

	MeterBar->SetPercent(InProgress);
}
