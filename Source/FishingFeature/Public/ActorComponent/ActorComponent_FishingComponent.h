// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponent_FishingComponent.generated.h"


class ICatchableInterface;
class UDataAsset_FishingComponentConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FISHINGFEATURE_API UActorComponent_FishingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorComponent_FishingComponent();

protected:
	virtual void BeginPlay() override;

	void SetupInitialVectors();

	void InitializeDecalActor();
	
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

	mutable FTimerHandle CastTimerHandle;
};