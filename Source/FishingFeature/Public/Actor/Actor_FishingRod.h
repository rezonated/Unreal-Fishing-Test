// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/CatcherInterface.h"
#include "Actor_FishingRod.generated.h"

UCLASS()
class FISHINGFEATURE_API AActor_FishingRod : public AActor, public ICatcherInterface
{
	GENERATED_BODY()

public:
	AActor_FishingRod();

	void PrepareBobberTimeline();

	virtual void SetStartLocation() override;
	
	virtual void Throw(const FVector& InCastLocation) override;
	
	virtual void ReelBack() override;

	FORCEINLINE virtual FSimpleDelegate& OnLandsOnWater() override { return CatchableLandsOnWaterDelegate; }

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* FishingRodMeshComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BobberMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Curve")
	UCurveFloat* BobberCurve = nullptr;

	UPROPERTY(Transient)
	FVector BobberTargetLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FVector BobberStartLocation = FVector::ZeroVector;
	
	UPROPERTY(Transient)
	FTimeline ThrowTimeline;

	FOnTimelineFloat ThrowFloatUpdate;
	UFUNCTION()
	void OnThrowUpdate(float InAlpha);

	FOnTimelineEvent ThrowFinishedEvent;
	UFUNCTION()
	void OnThrowFinished();

	FSimpleDelegate CatchableLandsOnWaterDelegate;
};
