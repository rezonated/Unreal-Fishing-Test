// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CatcherInterface.h"
#include "Actor_FishingRod.generated.h"

UCLASS()
class FISHINGFEATURE_API AActor_FishingRod : public AActor, public ICatcherInterface
{
	GENERATED_BODY()

public:
	AActor_FishingRod();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* FishingRodMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BobberMeshComponent = nullptr;
};
