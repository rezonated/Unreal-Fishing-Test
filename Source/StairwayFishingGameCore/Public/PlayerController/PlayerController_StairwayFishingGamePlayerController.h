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
 * Player controller for the game. Handles the input actions and the casting of the fishing action.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API APlayerController_StairwayFishingGamePlayerController : public APlayerController, public IPlayerActionInputInterface
{
	GENERATED_BODY()

public:
	/*
	 * Delegate for the start of the casting action. Fired when the started event of the input action is triggered.
	 */
	FORCEINLINE virtual FOnPlayerActionInput& OnCastActionStarted() override { return OnCastStartedDelegate; }

	/*
	 * Delegate for the trigger of the casting action. Fired when the triggered event of the input action is triggered.
	 */
	FORCEINLINE virtual FOnPlayerActionInput& OnCastActionTriggered() override{ return OnCastTriggeredDelegate; }

	/*
	 * Delegate for the completed of the casting action. Fired when the completed event of the input action is triggered.
	 */
	FORCEINLINE virtual FOnPlayerActionInput& OnCastActionCompleted() override { return OnCastCompletedDelegate; }

protected:
	/*
	 * Delegate for the start of the casting action.
	 */
	FOnPlayerActionInput OnCastStartedDelegate;

	/*
	 * Delegate for the trigger of the casting action.
	 */
	FOnPlayerActionInput OnCastTriggeredDelegate;

	/*
	 * Delegate for the completed of the casting action.
	 */
	FOnPlayerActionInput OnCastCompletedDelegate;

	/*
	 * Sets the focus of the player to the game viewport upon playing,
	 * Maps the input context and actions.
	 */
	virtual void BeginPlay() override;

	/*
	 * Handles for when the casting action start event is triggered.
	 */
	void OnCastStarted(const FInputActionInstance& InInputActionInstance);

	/*
	 * Handles for when the casting action trigger event is triggered.
	 */
	void OnCastTriggered(const FInputActionInstance& InInputActionInstance);

	/*
	 * Handles for when the casting action completed event is triggered.
	 */
	void OnCastFinished(const FInputActionInstance& InInputActionInstance);

	/*
	 * Broadcasts the delegate and the input action instance to the delegate.
	 */
	void BroadcastCastDelegateAndValue(const FOnPlayerActionInput& InDelegate, const FInputActionInstance& InInputActionInstance) const;

	/*
	 * Maps the assigned input context and actions.
	 */
	void MapInputContext(const UInputMappingContext* InMappingContext, const int32& InPriority = 0, const bool& bInClearExistingMappings = true) const;

	/*
	 * Maps the assigned input actions.
	 */
	void MapInputActions();

	/*
	 * Gets the enhanced input local player subsystem.
	 */
	bool GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputLocalPlayerSubsystem*& OutEnhancedInputLocalPlayerSubsystem) const;

	/*
	 * Gets the enhanced input component.
	 */
	bool GetEnhancedInputComponent(UEnhancedInputComponent*& OutEnhancedInputComponent) const;

	/*
	 * Default input mapping context.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game Player Controller")
	UInputMappingContext* DefaultInputMappingContext = nullptr;

	/*
	 * Input action for the casting action.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game Player Controller")
	UInputAction* CastingInputAction = nullptr;
};