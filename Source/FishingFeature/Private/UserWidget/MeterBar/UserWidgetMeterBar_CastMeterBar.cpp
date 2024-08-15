// Vanan Andreas - 2024


#include "UserWidget/MeterBar/UserWidgetMeterBar_CastMeterBar.h"

#include "FishingTags.h"
#include "Components/ProgressBar.h"
#include "Curves/CurveLinearColor.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"

void UUserWidgetMeterBar_CastMeterBar::NativeConstruct()
{
	Super::NativeConstruct();

	FGameplayTagContainer ChannelsToListenFor;
	ChannelsToListenFor.AddTag(FFishingTags::Get().Messaging_Fishing_Cast_Started);
	ChannelsToListenFor.AddTag(FFishingTags::Get().Messaging_Fishing_Cast_Held);
	ChannelsToListenFor.AddTag(FFishingTags::Get().Messaging_Fishing_Cast_Finished);

	FishingMessageListenerAsync =	 UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaMultipleChannels(this, ChannelsToListenFor);
	
	FishingMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(this, &ThisClass::OnFishingMessageReceived);

	FishingMessageListenerAsync->Activate();
}

void UUserWidgetMeterBar_CastMeterBar::NativeDestruct()
{
	if (FishingMessageListenerAsync)
	{
		FishingMessageListenerAsync->Cancel();
	}
	
	Super::NativeDestruct();
}

FLinearColor UUserWidgetMeterBar_CastMeterBar::GetColorForProgress(const float& InProgress, const FLinearColor& DefaultColor) const
{
	if (!CastMeterBarColorCurve)
	{
		UE_LOG(LogTemp, Warning, TEXT("CastMeterBarColorCurve is not set! Please make sure to set it in the details panel. Returning default color."));
		return DefaultColor;
	}

	float Progress = InProgress;
	Progress = FMath::Clamp(Progress, 0.f, 1.f);

	return CastMeterBarColorCurve->GetLinearColorValue(Progress);
}

void UUserWidgetMeterBar_CastMeterBar::SetProgressBarColor(const FLinearColor& InColor) const
{
	if (!MeterBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("MeterBar is not set! Please make sure to name it MeterBar in the details panel. Returning."));
		return;
	}

	MeterBar->SetFillColorAndOpacity(InColor);
}

void UUserWidgetMeterBar_CastMeterBar::OnFishingMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload)
{
	const bool bPayloadIsFloat = MessagePayload.Is<float>();
	if (!bPayloadIsFloat)
	{
		UE_LOG(LogTemp, Warning, TEXT("Expected payload for fishing is not a float! Ignoring message."));
		return;
	}
	
	const float Progress = MessagePayload.Get<float>();
	GEngine->AddOnScreenDebugMessage(2, .1f, FColor::Cyan, FString::Printf(TEXT("Progress: %f"), Progress));
	const FLinearColor Color = GetColorForProgress(Progress);
	
	SetProgress(Progress);
	SetProgressBarColor(Color);
}
