// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameStateBase.h"
#include "Runtime/VAAnyUnreal.h"
#include "GameStateBase_StairwayFishingGame.generated.h"

class UVAGameplayMessaging_ListenForGameplayMessages;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFishingGameLoopStateChanged, const FGameplayTag& /*InFishingGameLoopState*/);

/*
 * Game state that handles and keep track of game loop state.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API AGameStateBase_StairwayFishingGame : public AGameStateBase
{
	GENERATED_BODY()

public:
	/*
	 * Returns the current fishing game loop state.
	 */
	FORCEINLINE FGameplayTag GetCurrentFishingGameLoopState() const { return CurrentFishingGameLoopState; }

	/*
	 * Delegate for when the fishing game loop state changes.
	 */
	FOnFishingGameLoopStateChanged OnFishingGameLoopStateChanged;

	/*
	 * Sets the current fishing game loop state.
	 */
	void SetCurrentFishingGameLoopState(const FGameplayTag& InFishingGameLoopState);

protected:
	/*
	 * Listens for the game state change message.
	 */
	virtual void BeginPlay() override;

	/*
	 * Cleans up the game state change message listener async.
	 */
	void CleanupGameStateChangeMessageListener();

	/*
	 * Trigger cleanup for the game state change message listener async.
	 */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/*
	 * Handles the game state change message.
	 */
	UFUNCTION()
	void OnGameStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	/*
	 * Current fishing game loop state.
	 */
	UPROPERTY(Transient)
	FGameplayTag CurrentFishingGameLoopState = FGameplayTag();

	/*
	 * Cached game state change message listener async.
	 */
	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* GameStateChangeMessageListenerAsync = nullptr;
};