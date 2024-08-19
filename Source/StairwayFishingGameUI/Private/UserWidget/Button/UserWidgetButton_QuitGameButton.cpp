// Vanan Andreas - 2024


#include "UserWidget/Button/UserWidgetButton_QuitGameButton.h"

#include "Kismet/KismetSystemLibrary.h"

void UUserWidgetButton_QuitGameButton::OnButtonClicked()
{
	Super::OnButtonClicked();

	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}