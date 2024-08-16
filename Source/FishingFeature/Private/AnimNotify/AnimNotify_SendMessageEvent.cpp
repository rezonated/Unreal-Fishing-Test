// Vanan Andreas - 2024


#include "AnimNotify/AnimNotify_SendMessageEvent.h"

#include "FishingTags.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"

void UAnimNotify_SendMessageEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

	UVAGameplayMessagingSubsystem::Get(Owner).BroadcastMessage(Owner, MessageTag, {});
}
