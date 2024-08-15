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
