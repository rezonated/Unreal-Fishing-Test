// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/PlayerActionInputInterface.h"
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
class STAIRWAYFISHINGGAMECORE_API APlayerController_StairwayFishingGamePlayerController : public APlayerController, public IPlayerActionInputInterface
{
	GENERATED_BODY()

public:
	virtual FOnPlayerActionInput& OnCastActionStarted() override
	{
		return OnCastStartedDelegate;
	}

	virtual FOnPlayerActionInput& OnCastActionTriggered() override
	{
		return OnCastTriggeredDelegate;
	}

	virtual FOnPlayerActionInput& OnCastActionCompleted() override
	{
		return OnCastCompletedDelegate;
	}

protected:
	FOnPlayerActionInput OnCastStartedDelegate;
	FOnPlayerActionInput OnCastTriggeredDelegate;
	FOnPlayerActionInput OnCastCompletedDelegate;

	virtual void BeginPlay() override;

	void OnCastStarted(const FInputActionInstance& InInputActionInstance);
	void OnCastTriggered(const FInputActionInstance& InInputActionInstance);
	void OnCastFinished(const FInputActionInstance& InInputActionInstance);

	void BroadcastCastDelegateAndValue(const FOnPlayerActionInput& InDelegate, const FInputActionInstance& InInputActionInstance) const;

	void MapInputContext(const UInputMappingContext* InMappingContext, const int32& InPriority = 0, const bool& bInClearExistingMappings = true) const;
	void MapInputActions();

	bool GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputLocalPlayerSubsystem*& OutEnhancedInputLocalPlayerSubsystem) const;
	bool GetEnhancedInputComponent(UEnhancedInputComponent*& OutEnhancedInputComponent) const;

	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game Player Controller")
	UInputMappingContext* DefaultInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game Player Controller")
	UInputAction* CastingInputAction = nullptr;
};