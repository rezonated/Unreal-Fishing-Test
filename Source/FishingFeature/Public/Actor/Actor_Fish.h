// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CatchableInterface.h"
#include "Actor_Fish.generated.h"

class USphereComponent;

UCLASS()
class FISHINGFEATURE_API AFish : public AActor, public ICatchableInterface
{
	GENERATED_BODY()

public:
	AFish();

	virtual void Catch() override {}
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	USphereComponent* FishSphereCollision = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	UStaticMeshComponent* FishMesh = nullptr;
};
