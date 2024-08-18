// Vanan Andreas - 2024


#include "UserWidget/UserWidget_FishingDoneScreen.h"

void UUserWidget_FishingDoneScreen::CollapseWidgetButtonsContainer() const
{
	if (!Widget_ButtonsContainer)
	{
		UE_LOG(LogTemp, Error, TEXT("Widget_ButtonsContainer is not valid, have you set it up correctly in the Widget Blueprint?"));
		return;
	}
	
	Widget_ButtonsContainer->SetVisibility(ESlateVisibility::Collapsed);
}

void UUserWidget_FishingDoneScreen::NativePreConstruct()
{
	Super::NativePreConstruct();

	CollapseWidgetButtonsContainer();
}

void UUserWidget_FishingDoneScreen::NativeConstruct()
{
	Super::NativeConstruct();

	CollapseWidgetButtonsContainer();
}