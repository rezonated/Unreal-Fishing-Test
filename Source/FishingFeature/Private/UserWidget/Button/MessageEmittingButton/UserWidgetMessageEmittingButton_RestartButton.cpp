// Vanan Andreas - 2024


#include "UserWidget/Button/MessageEmittingButton/UserWidgetMessageEmittingButton_RestartButton.h"

#include "FishingTags.h"

void UUserWidgetMessageEmittingButton_RestartButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	ChannelTag = FFishingTags::Get().Messaging_GameState_StateChange;
	MessagePayload = FFishingTags::Get().FishingGameLoopState_Fishing;
}
