// Vanan Andreas - 2024


#include "Actor/Actor_FishingRod.h"


AActor_FishingRod::AActor_FishingRod()
{
	PrimaryActorTick.bCanEverTick = false;

	FishingRodMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FishingRodMeshComponent"));
	SetRootComponent(FishingRodMeshComponent);

	BobberMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BobberMeshComponent"));
	BobberMeshComponent->SetupAttachment(FishingRodMeshComponent);
}