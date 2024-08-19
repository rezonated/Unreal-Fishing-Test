// Vanan Andreas - 2024


#include "AnimNotify/AnimNotify_SendMessageEvent.h"

#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"

void UAnimNotify_SendMessageEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp)
	{
		UE_LOG(LogTemp, Error, TEXT("MeshComp is null, this should never happen! Won't continue..."));
		return;
	}

	const AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null, this should never happen! Won't continue..."));
		return;
	}

	if (!ChannelTag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("MessageTag is invalid, are you sure you picked a valid tag? Won't continue..."));
		return;
	}

	UVAGameplayMessagingSubsystem::Get(Owner).BroadcastMessage(Owner, ChannelTag, {});
}