// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_MainOverlay.generated.h"

class UUserWidget_FishingDoneScreen;
/**
 * Main overlay widget for the game. Contains the fishing done screen widget for now.
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_MainOverlay : public UUserWidget
{
	GENERATED_BODY()

	/*
	 * Current fishing done screen widget.
	 */
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UUserWidget_FishingDoneScreen* UserCreated_FishingDoneScreen = nullptr;
};