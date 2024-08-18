// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_MainOverlay.generated.h"

class UUserWidget_FishingDoneScreen;
/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_MainOverlay : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UUserWidget_FishingDoneScreen* UserCreated_FishingDoneScreen = nullptr;
};