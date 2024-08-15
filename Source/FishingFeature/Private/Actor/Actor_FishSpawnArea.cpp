// Vanan Andreas - 2024


#include "Actor/Actor_FishSpawnArea.h"

#include "FishingFeature.h"
#include "Components/BoxComponent.h"
#include "DataAsset/DataAsset_FishSpawnAreaConfig.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetMathLibrary.h"


AActor_FishSpawnArea::AActor_FishSpawnArea()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnAreaRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Area Root"));
	SetRootComponent(SpawnAreaRoot);

	SpawnAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area Box"));
	SpawnAreaBox->SetupAttachment(SpawnAreaRoot);
}

void AActor_FishSpawnArea::BeginPlay()
{
	Super::BeginPlay();

	if (!FishSpawnAreaConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fish Spawn Area Config Data is not set, are you sure you have a valid data asset set? Won't continue spawning fish..."));
		return;
	}
	
	const FFishSpawnAreaConfig FishSpawnAreaConfig = FishSpawnAreaConfigData->GetFishSpawnAreaConfig();

	const TSoftClassPtr<AActor> FishActorClass = FishSpawnAreaConfig.FishActorClass;
	
	FishSpawnAssetHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(FishActorClass.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AActor_FishSpawnArea::OnFishSpawnAssetLoaded));
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
	if (!LoadedAssetAsClass)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to cast loaded asset to UClass, this should not happen. Won't continue spawning fish..."));
		return;
	}

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

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("World is not valid, this should not happen. Won't continue spawning fish..."));
		return;
	}
	
	const FVector CenterLocation = GetRootComponent()->GetComponentLocation();
	const FVector BoxExtent = SpawnAreaBox->GetScaledBoxExtent();

	const FFishSpawnAreaConfig FishSpawnAreaConfig = FishSpawnAreaConfigData->GetFishSpawnAreaConfig();

	const int32 FishSpawnAmount = FishSpawnAreaConfig.FishSpawnAmount;

	for (int i = 0; i < FishSpawnAmount; i++)
	{
		const FVector RandomLocationInsideSpawnArea = UKismetMathLibrary::RandomPointInBoundingBox(CenterLocation, BoxExtent);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, RandomLocationInsideSpawnArea);

		World->SpawnActor<AActor>(LoadedAssetAsClass, SpawnTransform, SpawnParameters);
	}
}
