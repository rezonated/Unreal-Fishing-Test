// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn_StairwayFishingGame.generated.h"

class UActorComponent_FishingComponent;
class UWidgetComponent;
class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;
class UCapsuleComponent;

UCLASS()
class STAIRWAYFISHINGGAMECORE_API APawn_StairwayFishingGame : public APawn
{
	GENERATED_BODY()

public:
	APawn_StairwayFishingGame();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UCapsuleComponent* Capsule = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UArrowComponent* Arrow = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UWidgetComponent* CastMeterBarWidget = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UActorComponent_FishingComponent* FishingComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UCameraComponent* ShowFishCamera = nullptr;
};
