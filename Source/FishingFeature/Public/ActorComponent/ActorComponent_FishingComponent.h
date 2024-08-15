// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponent_FishingComponent.generated.h"


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
	void OnCastActionEnded(const float&);
	
	void DetermineCastLocation(const float& InElapsedTime);
	void AttemptToCast(const FVector& InCastStartPosition);

	void BroadcastUIMessage(const float& InProgress);
	float GetMappedElapsedTimeToMaximumCastTime(const float& InValue, const float DefaultValue = 0.f) const;

	void ToggleDecalVisibility(const bool& bInShouldBeVisible) const;
	void SetDecalActorLocation(const FVector& InLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Fishing Component | Config")
	UDataAsset_FishingComponentConfig* FishingComponentConfigData = nullptr;

private:
	UPROPERTY(Transient)
	FVector InitialActorLocation;
	
	UPROPERTY(Transient)
	FVector InitialActorForwardVector;

	UPROPERTY(Transient)
	FVector CastLocation;

	UPROPERTY(Transient)
	AActor* TargetActorDecalInstance = nullptr;
};