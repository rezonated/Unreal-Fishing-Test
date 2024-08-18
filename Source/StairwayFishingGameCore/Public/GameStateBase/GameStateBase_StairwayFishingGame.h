// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enum/FishingGameLoopState.h"
#include "GameFramework/GameStateBase.h"
#include "Runtime/VAAnyUnreal.h"
#include "GameStateBase_StairwayFishingGame.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFishingGameLoopStateChanged, const EFishingGameLoopState& /*InFishingGameLoopState*/);

UCLASS()
class STAIRWAYFISHINGGAMECORE_API AGameStateBase_StairwayFishingGame : public AGameStateBase
{
	GENERATED_BODY()

public:
	FORCEINLINE EFishingGameLoopState GetCurrentFishingGameLoopState() const { return CurrentFishingGameLoopState; }

	FOnFishingGameLoopStateChanged OnFishingGameLoopStateChanged;

	void SetCurrentFishingGameLoopState(const EFishingGameLoopState& InFishingGameLoopState);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UPROPERTY()
	EFishingGameLoopState CurrentFishingGameLoopState = EFishingGameLoopState::Fishing;
};