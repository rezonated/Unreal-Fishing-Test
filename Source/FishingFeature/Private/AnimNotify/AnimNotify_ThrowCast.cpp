// Vanan Andreas - 2024


#include "AnimNotify/AnimNotify_ThrowCast.h"

#include "FishingTags.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"

void UAnimNotify_ThrowCast::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp)
	{
		return;
	}

	const AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	UVAGameplayMessagingSubsystem::Get(Owner).BroadcastMessage(Owner, FFishingTags::Get().Messaging_Fishing_Notify_Throw, {});
}
