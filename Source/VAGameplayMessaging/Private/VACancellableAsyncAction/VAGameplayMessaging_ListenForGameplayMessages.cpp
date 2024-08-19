// Created by: Vanan A. - 2024


#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"

UVAGameplayMessaging_ListenForGameplayMessages* UVAGameplayMessaging_ListenForGameplayMessages::
ListenForGameplayMessagesViaChannel(const UObject* WorldContext, const FGameplayTag Channel)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert);
	if (!IsValid(World))
	{
		return nullptr;
	}

	if (!Channel.IsValid())
	{
		return nullptr;
	}

	UVAGameplayMessaging_ListenForGameplayMessages* ProxyObject = NewObject<UVAGameplayMessaging_ListenForGameplayMessages>();
	if (!IsValid(ProxyObject))
	{
		return nullptr;
	}

	ProxyObject->CurrentWorldPtr = World;
	ProxyObject->ChannelsToRegister.AddTag(Channel);
	ProxyObject->RegisterWithGameInstance(World);

	return ProxyObject;
}

UVAGameplayMessaging_ListenForGameplayMessages* UVAGameplayMessaging_ListenForGameplayMessages::
ListenForGameplayMessagesViaMultipleChannels(const UObject* WorldContext, const FGameplayTagContainer Channels)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert);
	if (!IsValid(World))
	{
		return nullptr;
	}

	if (!Channels.IsValid())
	{
		return nullptr;
	}

	UVAGameplayMessaging_ListenForGameplayMessages* ProxyObject = NewObject<UVAGameplayMessaging_ListenForGameplayMessages>();
	if (!IsValid(ProxyObject))
	{
		return nullptr;
	}

	ProxyObject->CurrentWorldPtr = World;
	ProxyObject->ChannelsToRegister = Channels;
	ProxyObject->RegisterWithGameInstance(World);

	return ProxyObject;
}

void UVAGameplayMessaging_ListenForGameplayMessages::Activate()
{
	const UWorld* World = CurrentWorldPtr.Get();
	if (!IsValid(World))
	{
		SetReadyToDestroy();
		return;
	}

	UVAGameplayMessagingSubsystem* Subsystem = &UVAGameplayMessagingSubsystem::Get(World);
	if (!IsValid(Subsystem))
	{
		SetReadyToDestroy();
		return;
	}

	if (!ChannelsToRegister.IsValid())
	{
		SetReadyToDestroy();
		return;
	}

	const bool bRegisterToSubsystem = Subsystem->RegisterNewMember(ChannelsToRegister, this);
	if (!bRegisterToSubsystem)
	{
		SetReadyToDestroy();
	}
}

void UVAGameplayMessaging_ListenForGameplayMessages::SetReadyToDestroy()
{
	const UWorld* World = CurrentWorldPtr.Get();
	if (!IsValid(World))
	{
		Super::SetReadyToDestroy();
		return;
	}

	UVAGameplayMessagingSubsystem* Subsystem = &UVAGameplayMessagingSubsystem::Get(World);
	if (!IsValid(Subsystem))
	{
		Super::SetReadyToDestroy();
		return;
	}

	Subsystem->UnregisterMember(this);

	Super::SetReadyToDestroy();
}