// Created by: Vanan A. - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Runtime/VAAnyUnreal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VAGameplayMessagingSubsystem.generated.h"

class UVAGameplayMessaging_ListenForGameplayMessages;

USTRUCT(BlueprintType)
struct FChannelMembersData
{
	GENERATED_BODY()

	FORCEINLINE void AddMembership(UVAGameplayMessaging_ListenForGameplayMessages* ChannelMember)
	{
		ChannelMembers.Add(ChannelMember);
	}

	FORCEINLINE void AddMembershipUnique(UVAGameplayMessaging_ListenForGameplayMessages* ChannelMember)
	{
		ChannelMembers.AddUnique(ChannelMember);
	}

	FORCEINLINE void RemoveMembership(UVAGameplayMessaging_ListenForGameplayMessages* ChannelMember)
	{
		ChannelMembers.Remove(ChannelMember);
	}

	FORCEINLINE bool IsEmpty() const
	{
		return ChannelMembers.Num() <= 0;
	}

	FORCEINLINE bool Contains(UVAGameplayMessaging_ListenForGameplayMessages* ChannelMember) const
	{
		return ChannelMembers.Contains(ChannelMember);
	}

	FORCEINLINE TArray<UVAGameplayMessaging_ListenForGameplayMessages*> GetChannelMembers() const
	{
		return ChannelMembers;
	}

private:
	TArray<UVAGameplayMessaging_ListenForGameplayMessages*> ChannelMembers;
};

UCLASS()
class VAGAMEPLAYMESSAGING_API UVAGameplayMessagingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UVAGameplayMessagingSubsystem& Get(const UObject* WorldContextObject);

	static bool GetInstance(const UObject* WorldContextObject, UVAGameplayMessagingSubsystem*& OutSubsystem);

	UFUNCTION(BlueprintCallable, Category = "VA_Gameplay Messaging", meta = (WorldContext = "WorldContextObject"))
	static bool BroadcastMessage(const UObject* WorldContextObject, const FGameplayTag InChannel, const FVAAnyUnreal InMessagePayload);

	bool BroadcastMessage_Internal(const FGameplayTag InChannel, const FVAAnyUnreal& InMessagePayload);

	bool RegisterNewMember(const FGameplayTagContainer& InChannels, UVAGameplayMessaging_ListenForGameplayMessages* InChannelMember);

	void UnregisterMember(UVAGameplayMessaging_ListenForGameplayMessages* InChannelMember);

	virtual void Deinitialize() override;

private:
	UPROPERTY()
	TMap<FGameplayTag, FChannelMembersData> ChannelToMembersMap;
};