// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_StairwayFishingGame.generated.h"

/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API AHUD_StairwayFishingGame : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	void SetupMainOverlayWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game HUD")
	TSubclassOf<UUserWidget> MainOverlayWidgetClass = nullptr;
	
	TWeakObjectPtr<UUserWidget> MainOverlayWidget;
};
