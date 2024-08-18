// Created by: Vanan A. - 2024


#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"


UVAGameplayMessagingSubsystem& UVAGameplayMessagingSubsystem::Get(const UObject* WorldContextObject)
{
	UVAGameplayMessagingSubsystem* VAGameplayMessagingSubsystem = nullptr;

	GetInstance(WorldContextObject, VAGameplayMessagingSubsystem);

	ensureAlwaysMsgf(IsValid(VAGameplayMessagingSubsystem), TEXT("VAGameplayMessagingSubsystem is not valid!"));

	return *VAGameplayMessagingSubsystem;
}

bool UVAGameplayMessagingSubsystem::GetInstance(const UObject* WorldContextObject, UVAGameplayMessagingSubsystem*& OutSubsystem)
{
	bool bRetVal = false;
	OutSubsystem = nullptr;

	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	if (!IsValid(World))
	{
		return bRetVal;
	}

	const UGameInstance* CurrentWorldGameInstance = World->GetGameInstance();
	if (!IsValid(CurrentWorldGameInstance))
	{
		return bRetVal;
	}

	UVAGameplayMessagingSubsystem* CurrentVAGameplayMessagingSubsystem = CurrentWorldGameInstance->GetSubsystem<UVAGameplayMessagingSubsystem>();
	if (!IsValid(CurrentVAGameplayMessagingSubsystem))
	{
		return bRetVal;
	}

	OutSubsystem = CurrentVAGameplayMessagingSubsystem;
	bRetVal = true;
	return bRetVal;
}

bool UVAGameplayMessagingSubsystem::BroadcastMessage(const UObject* WorldContextObject, const FGameplayTag InChannel,
	const FVAAnyUnreal                                              InMessagePayload)
{
	bool bRetVal = false;
	if (!IsValid(WorldContextObject))
	{
		return bRetVal;
	}

	const UWorld* WorldContext = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

	UVAGameplayMessagingSubsystem* GameplayMessagingSubsystemInstance;
	const bool                     bGetSubsystemInstance = GetInstance(WorldContext, GameplayMessagingSubsystemInstance);
	if (!bGetSubsystemInstance)
	{
		return bRetVal;
	}

	bRetVal = GameplayMessagingSubsystemInstance->BroadcastMessage_Internal(InChannel, InMessagePayload);
	return bRetVal;
}

bool UVAGameplayMessagingSubsystem::BroadcastMessage_Internal(const FGameplayTag InChannel, const FVAAnyUnreal& InMessagePayload)
{
	bool bRetVal = false;

	if (!InChannel.IsValid())
	{
		return bRetVal;
	}

	FVAAnyUnreal MessagePayload = InMessagePayload;
	if (!InMessagePayload.IsValid())
	{
		MessagePayload = FVAAnyUnreal::GetEmpty();
	}

	const bool bHasChannelTag = ChannelToMembersMap.Contains(InChannel);
	if (!bHasChannelTag)
	{
		return bRetVal;
	}

	const FChannelMembersData CurrentChannelMembers = ChannelToMembersMap[InChannel];
	if (CurrentChannelMembers.IsEmpty())
	{
		return bRetVal;
	}

	TArray<UVAGameplayMessaging_ListenForGameplayMessages*> ChannelMembersArray = CurrentChannelMembers.GetChannelMembers();
	for (UVAGameplayMessaging_ListenForGameplayMessages* ChannelMember : ChannelMembersArray)
	{
		if (!IsValid(ChannelMember) || !ChannelMember->IsValidLowLevel())
		{
			// Remove the invalid member from the channel
			ChannelToMembersMap[InChannel].RemoveMembership(ChannelMember);
			continue;
		}

		const bool bIsAsyncTask = ChannelMember->IsA(UVAGameplayMessaging_ListenForGameplayMessages::StaticClass());
		if (!bIsAsyncTask)
		{
			continue;
		}

		if (ChannelMember->OnGameplayMessageReceived.IsBound())
		{
			ChannelMember->OnGameplayMessageReceived.Broadcast(InChannel, MessagePayload);
		}
	}

	bRetVal = true;
	return bRetVal;
}

bool UVAGameplayMessagingSubsystem::RegisterNewMember(const FGameplayTagContainer& InChannels, UVAGameplayMessaging_ListenForGameplayMessages* InChannelMember)
{
	bool bRetVal = false;

	if (!InChannels.IsValid())
	{
		return bRetVal;
	}

	if (!IsValid(InChannelMember))
	{
		return bRetVal;
	}

	TArray<FGameplayTag> ChannelsToSubscribeTo;
	InChannels.GetGameplayTagArray(ChannelsToSubscribeTo);

	if (ChannelsToSubscribeTo.Num() <= 0)
	{
		return bRetVal;
	}

	for (const FGameplayTag& Channel : ChannelsToSubscribeTo)
	{
		const bool bChannelExistAlready = ChannelToMembersMap.Contains(Channel);
		if (!bChannelExistAlready) // If the channel does not exist, create a new channel and add the member to it
		{
			FChannelMembersData NewChannelMembersData;
			NewChannelMembersData.AddMembership(InChannelMember);

			ChannelToMembersMap.Add(Channel, NewChannelMembersData);

			continue;
		}

		// Otherwise, add the member to the existing channel
		FChannelMembersData* CurrentChannelMembersData = ChannelToMembersMap.Find(Channel);
		if (!CurrentChannelMembersData)
		{
			continue;
		}

		CurrentChannelMembersData->AddMembership(InChannelMember);
	}

	bRetVal = true;
	return bRetVal;
}

void UVAGameplayMessagingSubsystem::UnregisterMember(UVAGameplayMessaging_ListenForGameplayMessages* InChannelMember)
{
	for (const TPair<FGameplayTag, FChannelMembersData>& ChannelMember : ChannelToMembersMap)
	{
		FChannelMembersData CurrentMemberData = ChannelMember.Value;

		if (!CurrentMemberData.Contains(InChannelMember))
		{
			continue;
		}

		CurrentMemberData.RemoveMembership(InChannelMember);
	}
}

void UVAGameplayMessagingSubsystem::Deinitialize()
{
	ChannelToMembersMap.Reset();

	Super::Deinitialize();
}