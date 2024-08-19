// Vanan Andreas - 2024


#include "Pawn/Pawn_StairwayFishingGame.h"

#include "FishingTags.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "FishingFeature/Public/ActorComponent/ActorComponent_FishingComponent.h"
#include "GameFramework/SpringArmComponent.h"


APawn_StairwayFishingGame::APawn_StairwayFishingGame()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Capsule->SetCapsuleHalfHeight(90.f);
	Capsule->SetCapsuleRadius(35.f);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeTransform(FTransform(FRotator(0.f, -90.f, 0.f), FVector(0.f, 0.f, -90.f)));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Capsule);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Capsule);
	SpringArm->SetRelativeRotation(FRotator(-45.f, -180.f, 0.f));
	SpringArm->TargetArmLength = 750.f;
	SpringArm->TargetOffset = FVector(-350.f, 0.f, 0.f);
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetAutoActivate(true);

	CastMeterBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CastMeterBarWidget"));
	CastMeterBarWidget->SetupAttachment(GetRootComponent());
	CastMeterBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	CastMeterBarWidget->SetDrawAtDesiredSize(true);

	FishingComponent = CreateDefaultSubobject<UActorComponent_FishingComponent>(TEXT("FishingComponent"));

	ShowFishCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ShowFishCamera"));
	ShowFishCamera->SetupAttachment(GetRootComponent());
	ShowFishCamera->SetAutoActivate(false);
}

void APawn_StairwayFishingGame::SetFishingView(const FGameplayTag& InFishingGameLoopStateTag)
{
	if (!InFishingGameLoopStateTag.IsValid()) 
	{
		UE_LOG(LogTemp, Error, TEXT("InFishingGameLoopStateTag is not valid, have you set it up correctly in the component?"));
		return;
	}
	
	const bool bShouldFish = InFishingGameLoopStateTag.MatchesTag(FFishingTags::Get().FishingGameLoopState_Fishing);

	if (Camera)
	{
		Camera->SetActive(bShouldFish);
	}

	if (ShowFishCamera)
	{
		ShowFishCamera->SetActive(!bShouldFish);
	}
}