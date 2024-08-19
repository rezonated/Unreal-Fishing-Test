// Vanan Andreas - 2024


#include "UserWidget/UserWidget_Button.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUserWidget_Button::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TextBlock_Current)
	{
		TextBlock_Current->SetText(ButtonText);
	}
}

void UUserWidget_Button::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Current)
	{
		Button_Current->OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked);
	}
}