// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PlayerActionInterface.h"
#include "StairwayFishingGamePlayerController.generated.h"

struct FInputActionInstance;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API AStairwayFishingGamePlayerController : public APlayerController, public IPlayerActionInterface
{
	GENERATED_BODY()
public:
	virtual FPlayerActionDelegate GetOnCastStartedDelegate() const override
	{
		return OnCastStartedDelegate;
	}

	virtual FPlayerActionDelegate GetOnTriggeredDelegate() const override
	{
		return OnTriggeredDelegate;
	}
	
	virtual FPlayerActionDelegate GetOnCastFinishedDelegate() const override
	{
		return OnCastFinishedDelegate;
	}

protected:
	FPlayerActionDelegate OnCastStartedDelegate;
	FPlayerActionDelegate OnTriggeredDelegate;
	FPlayerActionDelegate OnCastFinishedDelegate;
	
	void MapInputActions();
	virtual void BeginPlay() override;
	
	void OnCastStarted(const FInputActionInstance& InInputActionInstance);
	void OnCastTriggered(const FInputActionInstance& InInputActionInstance);
	void OnCastFinished(const FInputActionInstance& InInputActionInstance);

	static void BroadcastCastEventsAndValues(const FPlayerActionDelegate& InDelegate, const FInputActionInstance& InInputActionInstance);

	void MapInputContext(const UInputMappingContext* InMappingContext, const int32& InPriority = 0, const bool& bInClearExistingMappings = true) const;

	bool GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputLocalPlayerSubsystem*& OutEnhancedInputLocalPlayerSubsystem) const;

	bool GetEnhancedInputComponent(UEnhancedInputComponent*& OutEnhancedInputComponent) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game")
	UInputMappingContext* DefaultInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game")
	UInputAction* CastingInputAction = nullptr;
};
