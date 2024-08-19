// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Engine/StreamableManager.h"
#include "Interface/MockableFishingInterface.h"
#include "Runtime/VAAnyUnreal.h"
#include "ActorComponent_FishingComponent.generated.h"


class IPlayerActionInputInterface;
class UVAGameplayMessaging_ListenForGameplayMessages;
class ICatcherInterface;
class ICatchableInterface;
class UDataAsset_FishingComponentConfig;

/*
 * Fishing component actor component, handles fishing logic and fishing state.
 *
 * It has a data asset for the fishing component config data. Tweak the data asset to your liking.
 *
 * It implements the IMockableFishingInterface interface, which allows for mocking the fishing logic for functional testing purposes.
 *
 * The whole fishing logic is handled by this actor component - states, timers, fishing rod spawning, fishing casting, reeling in, emitting messages, etc.
 *
 * It listens for player action input events and handles it for casting preview via decal actor and fishing rod spawning.
 *
 * It also listens for game mode state change events whether we should keep fishing or not.
 *
 * Anim notify messages are used to notify this component for precise timing of fishing states (cast, reel in/out, etc.)
 *
 * This component also acts as a mediator between the fishing rod (ICatcherInterface) and the fish (ICatchableInterface) and driving the logic between them.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FISHINGFEATURE_API UActorComponent_FishingComponent : public UActorComponent, public IMockableFishingInterface
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, disables the ticking and set the fishing state to idle by default.
	 */
	UActorComponent_FishingComponent();

#pragma region IMockableFishingInterface
	/*
	 * Mock cast, this is called by the fishing game loop state to mock the casting of the fishing rod.
	 */
	virtual void MockCast(const float& InElapsedTime) override;

	/*
	 * Mock cast end, this is called by the fishing game loop state to mock the end of the casting of the fishing rod.
	 */
	virtual void MockCastEnd() override;

	/*
	 * Returns the mock able to catch fish done delegate.
	 */
	FORCEINLINE virtual FOnMockFishing& OnMockAbleToCatchFishDone() override { return MockAbleToCatchFishDoneDelegate; }

	/*
	 * Returns the mock bobber lands on water delegate.
	 */
	FORCEINLINE virtual FOnMockFishing& OnMockBobberLandsOnWater() override { return MockBobberLandsOnWaterDelegate; }

	/*
	 * Returns the mock reel in done delegate.
	 */
	FORCEINLINE virtual FOnMockFishing& OnMockReelInDone() override { return MockReelInDoneDelegate; }

#pragma endregion

protected:
	/*
	 * Initializes and caches the necessary data for the fishing component.
	 * Listens for the throw/reel notify message and the game mode state change finish message.
	 * Binds the player action input delegate to the owner controller.
	 * And finally requests the fishing rod soft class.
	 */
	virtual void BeginPlay() override;

	/*
	 * Cleans up the fishing component.
	 * Cleans up the message listeners.
	 * Cleans up the catcher and controller delegate bindings.
	 */
	virtual void BeginDestroy() override;

	/*
	 * Cleans up the message asynchronous listeners.
	 */
	void CleanupMessageListeners();

	/*
	 * Cleans up the catcher and controller delegate bindings.
	 */
	void CleanupCatcherAndControllerDelegateBindings();

	/*
	 * Requests the fishing rod soft class.
	 */
	void RequestLoadFishingRodSoftClass();

	/*
	 * Caches the initial actor location and forward vector.
	 */
	void SetupInitialVectors();

	/*
	 * Initializes the decal actor.
	 */
	void InitializeDecalActor();

	/*
	 * Loads the fishing rod asset.
	 */
	void OnFishingRodAssetLoaded();

	/*
	 * Spawns the fishing rod.
	 */
	void SpawnFishingRod(const FName& InFishingPoleSocketName, USkeletalMeshComponent* InSkeletalMeshComponent, UClass* InFishingRodActorClass, ESpawnActorCollisionHandlingMethod InCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	/*
	 * Binds the player action input delegates to cast and cast end.
	 */
	void BindToPlayerActionInputDelegates();

	/*
	 * Handles the cast action.
	 */
	void OnCastAction(const float& InElapsedTime);

	/*
	 * Resets the state and timer, used when the period to wait for the fish to be caught has passed.
	 */
	void ResetStateAndTimer();

	/*
	 * Handles the cast action end.
	 */
	void OnCastActionEnded(const float&);

	/*
	 * Called when the bobber lands on water via fishing rod's interface delegate.
	 */
	void OnBobberLandsOnWater();

	/*
	 * Listens for the reel done notify message, used to change the state of the game state to show fish if the fish is caught.
	 */
	void ListenForReelDoneNotify();

	/*
	 * Listens for the throw notify message, actually casts the fishing rod.
	 */
	void ListenForThrowNotify();

	/*
	 * Listens for the game mode state change finish message, used to handle state change by the game mode.
	 */
	void ListenForGameModeStateChangeFinish();

	/*
	 * Determines the cast location based on the fishing component config forwards of the player.
	 */
	void DetermineCastLocation(const float& InElapsedTime);

	/*
	 * Performs line trace downwards to the water body based on the cast location.
	 */
	void AttemptToCast(const FVector& InCastStartPosition);

	/*
	 * Attempts to get the nearest catchable using sphere trace.
	 */
	void AttemptGetNearestCatchable();

	/*
	 * Reels in the current catchable fish.
	 */
	void ReelInCurrentCatchable();

	/*
	 * Starts the waiting for fish timer, used to wait for the fish to be caught.
	 */
	void StartWaitingForFishTimer();

	/*
	 * Lets the catchable fish escape, called when player pulls the fishing rod too early.
	 */
	void LetCatchableEscape();

	/*
	 * Reels back the fishing rod.
	 */
	void ReelBack();

	/*
	 * Broadcasts the UI message for casting progress.
	 */
	void BroadcastUIMessage(const float& InProgress) const;

	/*
	 * Returns the mapped elapsed time relative to the maximum cast time.
	 */
	float GetMappedElapsedTimeToMaximumCastTime(const float& InValue, const float DefaultValue = 0.f) const;

	/*
	 * Toggles the visibility of the decal actor, used as a visual indicator of the casting location.
	 */
	void ToggleDecalVisibility(const bool& bInShouldBeVisible) const;

	/*
	 * Sets the decal actor location based on the cast location.
	 */
	void SetDecalActorLocation(const FVector& InLocation) const;

	/*
	 * Returns the owner skeletal mesh component.
	 */
	bool GetOwnerSkeletalMeshComponent(USkeletalMeshComponent*& OutSkeletalMeshComponent) const;

	/*
	 * Handles the throw notify message.
	 */
	UFUNCTION()
	void OnThrowNotifyMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	/*
	 * Handles the reel done notify message.
	 */
	UFUNCTION()
	void OnReelDoneNotifyMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	/*
	 * Handles the game mode state change finish message.
	 */
	UFUNCTION()
	void OnGameModeStateChangeFinishMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	/*
	 * The data asset for the fishing component config, tweak the data asset to your liking.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Fishing Component | Config")
	UDataAsset_FishingComponentConfig* FishingComponentConfigData = nullptr;

private:
	/*
	 * Cached initial actor location.
	 */
	UPROPERTY(Transient)
	FVector InitialActorLocation = FVector::ZeroVector;

	/*
	 * Cached initial actor forward vector.
	 */
	UPROPERTY(Transient)
	FVector InitialActorForwardVector = FVector::ZeroVector;

	/*
	 * Cached cast location based on how long the player held LMB.
	 */
	UPROPERTY(Transient)
	FVector CastLocation = FVector::ZeroVector;

	/*
	 * Cached decal actor instance.
	 */
	UPROPERTY(Transient)
	AActor* TargetActorDecalInstance = nullptr;

	/*
	 * Current fishing state.
	 */
	UPROPERTY(Transient)
	FGameplayTag CurrentFishingState;

	/*
	 * Async message listener for the throw notify message.
	 */
	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* NotifyMessageListenerAsync = nullptr;

	/*
	 * Async message listener for the game mode state change finish message.
	 */
	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* GameModeStateChangeMessageListenerAsync = nullptr;

	/*
	 * Async message listener for the reel done notify message.
	 */
	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* ReelDoneDoneNotifyMessageListenerAsync = nullptr;

	/*
	 * Cached current catchable fish.
	 */
	ICatchableInterface* CurrentCatchable = nullptr;

	/*
	 * Cached current fishing rod.
	 */
	ICatcherInterface* CurrentCatcher = nullptr;

	/*
	 * Cached owner controller as player action input.
	 */
	IPlayerActionInputInterface* OwnerControllerAsPlayerActionInput = nullptr;

	/*
	 * Cached fishing rod asset handle.
	 */
	TSharedPtr<FStreamableHandle> FishingRodAssetHandle = nullptr;

	/*
	 * Timer handle for the cast timer.
	 */
	FTimerHandle CastTimerHandle;

	/*
	 * Mock able to catch fish done delegate.
	 */
	FOnMockFishing MockAbleToCatchFishDoneDelegate;

	/*
	 * Mock bobber lands on water delegate.
	 */
	FOnMockFishing MockBobberLandsOnWaterDelegate;

	/*
	 * Mock reel in done delegate.
	 */
	FOnMockFishing MockReelInDoneDelegate;
};