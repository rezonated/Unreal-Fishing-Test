// Vanan Andreas - 2024


#include "UserWidget/Button/UserWidgetButton_MessageEmittingButton.h"

#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"

void UUserWidgetButton_MessageEmittingButton::OnButtonClicked()
{
	Super::OnButtonClicked();

	if (!ChannelTag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Channel Tag is not valid, have you set it up correctly in the component?"));
		return;
	}
	
	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, ChannelTag, MessagePayload);
}