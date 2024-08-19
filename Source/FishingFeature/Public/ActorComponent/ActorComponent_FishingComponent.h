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

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FISHINGFEATURE_API UActorComponent_FishingComponent : public UActorComponent, public IMockableFishingInterface
{
	GENERATED_BODY()

public:
	UActorComponent_FishingComponent();

	virtual void MockCast(const float& InElapsedTime) override;
	
	virtual void MockCastEnd() override;
	
	FORCEINLINE virtual FOnMockDone& OnMockDone() override { return MockDoneDelegate; }

protected:
	virtual void BeginPlay() override;
	
	virtual void BeginDestroy() override;
	
	void CleanupMessageListeners();
	void CleanupCatcherAndControllerDelegateBindings();

	void RequestLoadFishingRodSoftClass();
	
	void SetupInitialVectors();

	void InitializeDecalActor();

	void OnFishingRodAssetLoaded();

	void SpawnFishingRod(const FName& InFishingPoleSocketName, USkeletalMeshComponent* InSkeletalMeshComponent, UClass* InFishingRodActorClass, ESpawnActorCollisionHandlingMethod InCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	void BindToPlayerActionInputDelegates();

	void OnCastAction(const float& InElapsedTime);

	void ResetStateAndTimer();

	void OnCastActionEnded(const float&);

	void OnBobberLandsOnWater();

	void ListenForReelDoneNotify();
	void ListenForThrowNotify();

	void ListenForGameModeStateChangeFinish();

	void DetermineCastLocation(const float& InElapsedTime);
	void AttemptToCast(const FVector& InCastStartPosition);

	void AttemptGetNearestCatchable();
	void ReelInCurrentCatchable();
	void StartWaitingForFishTimer();
	void LetCatchableEscape();
	void ReelBack();


	void  BroadcastUIMessage(const float& InProgress) const;
	float GetMappedElapsedTimeToMaximumCastTime(const float& InValue, const float DefaultValue = 0.f) const;

	void ToggleDecalVisibility(const bool& bInShouldBeVisible) const;
	void SetDecalActorLocation(const FVector& InLocation) const;

	bool GetOwnerSkeletalMeshComponent(USkeletalMeshComponent*& OutSkeletalMeshComponent) const;

	UFUNCTION()
	void OnThrowNotifyMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UFUNCTION()
	void OnReelDoneNotifyMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UFUNCTION()
	void OnGameModeStateChangeFinishMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UPROPERTY(EditDefaultsOnly, Category = "Fishing Component | Config")
	UDataAsset_FishingComponentConfig* FishingComponentConfigData = nullptr;

private:
	UPROPERTY(Transient)
	FVector InitialActorLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FVector InitialActorForwardVector = FVector::ZeroVector;

	UPROPERTY(Transient)
	FVector CastLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	AActor* TargetActorDecalInstance = nullptr;

	UPROPERTY(Transient)
	FGameplayTag CurrentFishingState;

	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* NotifyMessageListenerAsync = nullptr;

	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* GameModeStateChangeMessageListenerAsync = nullptr;

	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* ReelDoneDoneNotifyMessageListenerAsync = nullptr;

	ICatchableInterface* CurrentCatchable = nullptr;

	ICatcherInterface* CurrentCatcher = nullptr;

	IPlayerActionInputInterface* OwnerControllerAsPlayerActionInput = nullptr;

	TSharedPtr<FStreamableHandle> FishingRodAssetHandle = nullptr;

	FTimerHandle CastTimerHandle;

	FOnMockDone MockDoneDelegate;
};