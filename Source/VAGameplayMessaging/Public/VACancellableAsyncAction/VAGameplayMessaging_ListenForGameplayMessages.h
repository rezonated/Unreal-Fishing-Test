// Created by: Vanan A. - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "VAGameplayMessaging/Public/BlueprintAsyncActionBase/VACancellableAsyncAction.h"
#include "VAAnyUnreal/Public/Runtime/VAAnyUnreal.h"
#include "VAGameplayMessaging_ListenForGameplayMessages.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAsyncGameplayMessageSignature, const FGameplayTag&, Channel, const FVAAnyUnreal&, MessagePayload);

UCLASS()
class VAGAMEPLAYMESSAGING_API UVAGameplayMessaging_ListenForGameplayMessages : public UVACancellableAsyncAction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"))
	static UVAGameplayMessaging_ListenForGameplayMessages* ListenForGameplayMessagesViaChannel(const UObject* WorldContext, const FGameplayTag Channel);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"))
	static UVAGameplayMessaging_ListenForGameplayMessages* ListenForGameplayMessagesViaMultipleChannels(const UObject* WorldContext, const FGameplayTagContainer Channels);

	UPROPERTY(BlueprintAssignable)
	FAsyncGameplayMessageSignature OnGameplayMessageReceived;

	virtual void Activate() override;

	virtual void SetReadyToDestroy() override;

private:
	UPROPERTY()
	TWeakObjectPtr<UWorld> CurrentWorldPtr;

	UPROPERTY(BlueprintReadOnly, Category = "VA_Gameplay Messaging", meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer ChannelsToRegister;
};