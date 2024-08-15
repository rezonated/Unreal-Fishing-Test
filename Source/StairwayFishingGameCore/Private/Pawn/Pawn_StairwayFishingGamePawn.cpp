﻿// Vanan Andreas - 2024


#include "Pawn/Pawn_StairwayFishingGamePawn.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "FishingFeature/Public/ActorComponent/ActorComponent_FishingComponent.h"
#include "GameFramework/SpringArmComponent.h"


APawn_StairwayFishingGamePawn::APawn_StairwayFishingGamePawn()
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

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CastMeterBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CastMeterBarWidget"));
	CastMeterBarWidget->SetupAttachment(GetRootComponent());
	CastMeterBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	CastMeterBarWidget->SetDrawAtDesiredSize(true);

	FishingComponent = CreateDefaultSubobject<UActorComponent_FishingComponent>(TEXT("FishingComponent"));
}
