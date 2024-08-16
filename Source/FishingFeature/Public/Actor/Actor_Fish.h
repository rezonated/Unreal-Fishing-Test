// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/CatchableInterface.h"
#include "Actor_Fish.generated.h"

class UDataAsset_ActorFishConfig;
class USphereComponent;

UCLASS()
class FISHINGFEATURE_API AActor_Fish : public AActor, public ICatchableInterface
{
	GENERATED_BODY()
public:
	AActor_Fish();
	
	virtual void ReeledIn(const FVector& RodLocation) override;
	virtual void Escape() override;
	void SetupFishMovementValues();
	virtual void Catch(USceneComponent* InCatchingRod) override;

	FORCEINLINE virtual void
	SetSpawnAreaCenterAndExtent(const FVector& InCenter, const FVector& InContainingSpawnAreaBoxExtent) override
	{
		ContainingSpawnAreaCenter = InCenter;
		ContainingSpawnAreaBoxExtent = InContainingSpawnAreaBoxExtent;
	}

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	USphereComponent* FishSphereCollision = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	UStaticMeshComponent* FishMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fish | Config")
	UDataAsset_ActorFishConfig* ActorFishConfigData = nullptr;
	
private:
	UPROPERTY(Transient)
	FVector InitialActorLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FVector ContainingSpawnAreaCenter = FVector::ZeroVector;

	UPROPERTY(Transient)
	FVector ContainingSpawnAreaBoxExtent = FVector::ZeroVector;

	UPROPERTY(Transient)
	float FishRotationSpeed = 0.f;

	UPROPERTY(Transient)
	float FishMoveSpeed = 0.f;

	UPROPERTY(Transient)
	float FishWanderTargetRadius = 0.f;

	UPROPERTY(Transient)
	FRotator EscapeRotation = FRotator::ZeroRotator;

	UPROPERTY(Transient)
	FVector ReelInLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FRotator LookAtReelInRotation = FRotator::ZeroRotator;

	UPROPERTY(Transient)
	bool bBeingTargeted = false;

	UPROPERTY(Transient)
	FVector WanderTargetLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FRotator WanderLookAtTargetRotation = FRotator::ZeroRotator;

	void SetupTimelines();
	void WanderWithinBoundingBox(float DeltaSeconds);
	void TickTimelines(float DeltaSeconds);

	UPROPERTY(Transient)
	FTimeline ReeledInTimeline;

	FOnTimelineFloat ReeledInFloatUpdate;
	UFUNCTION()
	void OnReelInUpdate(float InAlpha);

	FOnTimelineEvent ReeledInFinishedEvent;
	UFUNCTION()
	void OnReelInFinished();

	UPROPERTY(Transient)
	FTimeline EscapeTimeline;

	FOnTimelineFloat EscapeFloatUpdate;
	UFUNCTION()
	void OnEscapeUpdate(float InAlpha);

	FOnTimelineEvent EscapeFinishedEvent;
	UFUNCTION()
	void OnEscapeFinished();

	void SetupTimelineDataAndCallbacks(FTimeline* InTimeline, const FOnTimelineFloat& InOnTimelineFloat, const FOnTimelineEvent& InOnTimelineEvent, UCurveFloat* InCurveFloat) const;

	static void ClearTimeline(FOnTimelineFloat* InTimelineFloat, FOnTimelineEvent* InTimelineEvent);

	void InterpolateLocationAndRotation(const FVector& InTargetLocation, const FRotator& InTargetRotation, const float& InAlpha);
};