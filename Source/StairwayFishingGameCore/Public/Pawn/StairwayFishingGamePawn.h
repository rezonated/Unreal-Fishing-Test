// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StairwayFishingGamePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;
class UCapsuleComponent;

UCLASS()
class STAIRWAYFISHINGGAMECORE_API AStairwayFishingGamePawn : public APawn
{
	GENERATED_BODY()

public:
	AStairwayFishingGamePawn();

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
};
