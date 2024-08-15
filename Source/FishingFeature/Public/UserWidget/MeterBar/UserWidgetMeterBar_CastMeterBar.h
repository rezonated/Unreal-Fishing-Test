// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Runtime/VAAnyUnreal.h"
#include "UserWidget/UserWidget_MeterBar.h"
#include "UserWidgetMeterBar_CastMeterBar.generated.h"

class UVAGameplayMessaging_ListenForGameplayMessages;
/**
 * 
 */
UCLASS()
class FISHINGFEATURE_API UUserWidgetMeterBar_CastMeterBar : public UUserWidget_MeterBar
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game Meter Bar")
	UCurveLinearColor* CastMeterBarColorCurve;

	FLinearColor GetColorForProgress(const float& InProgress, const FLinearColor& DefaultColor = FLinearColor::White) const;

	void SetProgressBarColor(const FLinearColor& InColor) const;

private:
	UFUNCTION()
	void OnFishingMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UPROPERTY()
	UVAGameplayMessaging_ListenForGameplayMessages* FishingMessageListenerAsync;
};
