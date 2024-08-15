// Vanan Andreas - 2024


#include "Actor/Actor_Fish.h"

#include "Components/SphereComponent.h"

AFish::AFish()
{
	PrimaryActorTick.bCanEverTick = false;

	FishSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Fish Sphere Collision"));
	SetRootComponent(FishSphereCollision);

	FishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fish Mesh"));
	FishMesh->SetupAttachment(FishSphereCollision);
	FishMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFish::ReeledIn(const FVector& RodLocation)
{
	const FString FishName = GetNameSafe(this);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Reeled in %s"), *FishName));
}
