// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StreamableManager.h"
#include "ActorComponent_FishingComponent.generated.h"


class ICatcherInterface;
class ICatchableInterface;
class UDataAsset_FishingComponentConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FISHINGFEATURE_API UActorComponent_FishingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorComponent_FishingComponent();
	void RequestLoadFishingRodSoftClass();

protected:
	virtual void BeginPlay() override;

	void SetupInitialVectors();

	void InitializeDecalActor();
	
	void OnFishingRodAssetLoaded();
	void SpawnFishingRod(const FName& InFishingPoleSocketName, USkeletalMeshComponent* InSkeletalMeshComponent, UClass* InFishingRodActorClass, ESpawnActorCollisionHandlingMethod InCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	void BindToPlayerActionInputDelegates();
	
	void OnCastAction(const float& InElapsedTime);

	void ResetCastFlagAndTimer();
	
	void OnCastActionEnded(const float&);
	
	void DetermineCastLocation(const float& InElapsedTime);
	void AttemptToCast(const FVector& InCastStartPosition);

	void AttemptGetRandomCatchable();
	void ReelInCurrentCatchable();
	void StartCastingTimer();

	void BroadcastUIMessage(const float& InProgress) const;
	float GetMappedElapsedTimeToMaximumCastTime(const float& InValue, const float DefaultValue = 0.f) const;

	void ToggleDecalVisibility(const bool& bInShouldBeVisible) const;
	void SetDecalActorLocation(const FVector& InLocation) const;

	bool GetOwnerSkeletalMeshComponent(USkeletalMeshComponent*& OutSkeletalMeshComponent) const;
	
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
	bool bIsCurrentlyCasting = false;

	ICatchableInterface* CurrentCatchable = nullptr;
	
	ICatcherInterface* FishingRodActorAsCatcherInterface = nullptr;

	TSharedPtr<FStreamableHandle> FishingRodAssetHandle = nullptr;

	mutable FTimerHandle CastTimerHandle;
};