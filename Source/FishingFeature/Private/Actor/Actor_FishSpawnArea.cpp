// Vanan Andreas - 2024


#include "Actor/Actor_FishSpawnArea.h"

#include "FishingFeature.h"
#include "Components/BoxComponent.h"
#include "DataAsset/DataAsset_FishSpawnAreaConfig.h"
#include "Engine/AssetManager.h"
#include "Interface/CatchableInterface.h"
#include "Kismet/KismetMathLibrary.h"


AActor_FishSpawnArea::AActor_FishSpawnArea()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnAreaRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Area Root"));
	SetRootComponent(SpawnAreaRoot);

	SpawnAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area Box"));
	SpawnAreaBox->SetupAttachment(SpawnAreaRoot);
}

void AActor_FishSpawnArea::RequestLoadFishAssetSoftClass()
{
	if (!FishSpawnAreaConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fish Spawn Area Config Data is not set, are you sure you have a valid data asset set? Won't continue spawning fish..."));
		return;
	}

	const FFishSpawnAreaConfig FishSpawnAreaConfig = FishSpawnAreaConfigData->GetFishSpawnAreaConfig();

	const TSoftClassPtr<AActor> FishActorClass = FishSpawnAreaConfig.FishActorClass;

	FishSpawnAssetHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(FishActorClass.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ThisClass::OnFishSpawnAssetLoaded));
}

void AActor_FishSpawnArea::BeginPlay()
{
	Super::BeginPlay();

	RequestLoadFishAssetSoftClass();
}

void AActor_FishSpawnArea::BeginDestroy()
{
	if (FishSpawnAssetHandle && FishSpawnAssetHandle->IsActive())
	{
		FishSpawnAssetHandle->CancelHandle();
	}

	Super::BeginDestroy();
}

void AActor_FishSpawnArea::OnFishSpawnAssetLoaded()
{
	UObject* LoadedAsset = FishSpawnAssetHandle.Get()->GetLoadedAsset();

	UClass* LoadedAssetAsClass = Cast<UClass>(LoadedAsset);

	if (!SpawnAreaBox)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Spawn Area Box is not valid, this should not happen. Won't continue spawning fish..."));
		return;
	}

	if (!FishSpawnAreaConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fish Spawn Area Config Data is not set, are you sure you have a valid data asset set? Won't continue spawning fish..."));
		return;
	}

	const FFishSpawnAreaConfig FishSpawnAreaConfig = FishSpawnAreaConfigData->GetFishSpawnAreaConfig();

	const int32 FishSpawnAmount = FishSpawnAreaConfig.FishSpawnAmount;

	const FVector CenterLocation = GetRootComponent()->GetComponentLocation();
	const FVector BoxExtent = SpawnAreaBox->GetScaledBoxExtent();

	SpawnFishes(FishSpawnAmount, CenterLocation, BoxExtent, LoadedAssetAsClass);
}

void AActor_FishSpawnArea::SpawnFishes(const int32& InFishSpawnAmount, const FVector& InCenterLocation, const FVector& InBoxExtent, UClass* InFishActorClass)
{
	if (!InFishActorClass)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to cast loaded asset to UClass, this should not happen. Won't continue spawning fish..."));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("World is not valid, this should not happen. Won't continue spawning fish..."));
		return;
	}

	for (int i = 0; i < InFishSpawnAmount; i++)
	{
		const FVector RandomLocationInsideSpawnArea = UKismetMathLibrary::RandomPointInBoundingBox(InCenterLocation, InBoxExtent);

		const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, RandomLocationInsideSpawnArea);

		AActor* SpawnedActor = World->SpawnActorDeferred<AActor>(InFishActorClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (!SpawnedActor)
		{
			continue;
		}

		const bool bIsSpawnedActorImplementsCatchableInterface = SpawnedActor->Implements<UCatchableInterface>();
		if (!bIsSpawnedActorImplementsCatchableInterface)
		{
			continue;
		}

		ICatchableInterface* SpawnedActorAsCatchableInterface = Cast<ICatchableInterface>(SpawnedActor);
		if (!SpawnedActorAsCatchableInterface)
		{
			continue;
		}

		SpawnedActorAsCatchableInterface->SetSpawnAreaCenterAndExtent(InCenterLocation, InBoxExtent);

		SpawnedActor->FinishSpawning(SpawnTransform);
	}
}