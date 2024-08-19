// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameStateBase.h"
#include "Runtime/VAAnyUnreal.h"
#include "GameStateBase_StairwayFishingGame.generated.h"

/**
 * 
 */

class UVAGameplayMessaging_ListenForGameplayMessages;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFishingGameLoopStateChanged, const FGameplayTag& /*InFishingGameLoopState*/);

UCLASS()
class STAIRWAYFISHINGGAMECORE_API AGameStateBase_StairwayFishingGame : public AGameStateBase
{
	GENERATED_BODY()

public:
	FORCEINLINE FGameplayTag GetCurrentFishingGameLoopState() const { return CurrentFishingGameLoopState; }

	FOnFishingGameLoopStateChanged OnFishingGameLoopStateChanged;

	void SetCurrentFishingGameLoopState(const FGameplayTag& InFishingGameLoopState);

protected:
	virtual void BeginPlay() override;
	void CleanupGameStateChangeMessageListener();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnGameStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UPROPERTY(Transient)
	FGameplayTag CurrentFishingGameLoopState = FGameplayTag();

	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* GameStateChangeMessageListenerAsync = nullptr;
};