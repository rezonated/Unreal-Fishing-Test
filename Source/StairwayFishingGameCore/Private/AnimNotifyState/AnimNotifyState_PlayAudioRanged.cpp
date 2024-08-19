// Vanan Andreas - 2024


#include "AnimNotifyState/AnimNotifyState_PlayAudioRanged.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UAnimNotifyState_PlayAudioRanged::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float                                                                  TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (!SoundToPlay)
	{
		UE_LOG(LogTemp, Error, TEXT("UAnimNotifyState_PlayAudioRanged::NotifyBegin - SoundToPlay is null! Has it been set in the notifystate?"));
		return;
	}

	if (!MeshComp)
	{
		UE_LOG(LogTemp, Error, TEXT("MeshComp is null, this should never happen! Won't continue..."));
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null, this should never happen! Won't continue..."));
		return;
	}

	const FVector  OwnerLocation = Owner->GetActorLocation();
	const FRotator OwnerRotation = Owner->GetActorRotation();

	CurrentAudioComponent = UGameplayStatics::SpawnSound2D(Owner, SoundToPlay);
	if (!CurrentAudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentAudioComponent is null, this should never happen! Won't continue..."));
		CurrentAudioComponent = nullptr;
		return;
	}

	CurrentAudioComponent->Play();
}

void UAnimNotifyState_PlayAudioRanged::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (CurrentAudioComponent)
	{
		CurrentAudioComponent->Stop();
		CurrentAudioComponent->DestroyComponent();
	}

	Super::NotifyEnd(MeshComp, Animation);
}