// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Runtime/VAAnyUnreal.h"
#include "UserWidget/UserWidget_MeterBar.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"
#include "UserWidgetMeterBar_CastMeterBar.generated.h"

class UCurveLinearColor;
/**
 * 
 */
UCLASS()
class FISHINGFEATUREUI_API UUserWidgetMeterBar_CastMeterBar : public UUserWidget_MeterBar
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	FLinearColor GetColorForProgress(const float& InProgress, const FLinearColor& DefaultColor = FLinearColor::White) const;

	void SetProgressBarColor(const FLinearColor& InColor) const;

	UPROPERTY(EditDefaultsOnly, Category = "Cast Meter Bar")
	UCurveLinearColor* CastMeterBarColorCurve;
private:
	UFUNCTION()
	void OnFishingMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UPROPERTY()
	UVAGameplayMessaging_ListenForGameplayMessages* FishingMessageListenerAsync;

};
