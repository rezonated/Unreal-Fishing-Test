// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ThrowCast.generated.h"

/**
 * 
 */
UCLASS()
class FISHINGFEATURE_API UAnimNotify_ThrowCast : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
