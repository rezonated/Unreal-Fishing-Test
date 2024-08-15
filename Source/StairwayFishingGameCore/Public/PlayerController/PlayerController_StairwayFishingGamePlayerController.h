// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_StairwayFishingGamePlayerController.generated.h"

struct FGameplayTag;
struct FInputActionInstance;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API APlayerController_StairwayFishingGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	void OnCastStarted(const FInputActionInstance& InInputActionInstance);
	void OnCastTriggered(const FInputActionInstance& InInputActionInstance);
	void OnCastFinished(const FInputActionInstance& InInputActionInstance);

	void BroadcastCastMessage(const FGameplayTag& InChannelTag, const FInputActionInstance& InInputActionInstance) const;
	
	void MapInputContext(const UInputMappingContext* InMappingContext, const int32& InPriority = 0, const bool& bInClearExistingMappings = true) const;
	void MapInputActions();

	bool GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputLocalPlayerSubsystem*& OutEnhancedInputLocalPlayerSubsystem) const;
	bool GetEnhancedInputComponent(UEnhancedInputComponent*& OutEnhancedInputComponent) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game")
	UInputMappingContext* DefaultInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game")
	UInputAction* CastingInputAction = nullptr;
};
