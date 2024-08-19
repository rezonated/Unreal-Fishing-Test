// Vanan Andreas - 2024


#include "BlueprintAsyncActionBase/VACancellableAsyncAction.h"

void UVACancellableAsyncAction::BeginDestroy()
{
	Cancel();

	Super::BeginDestroy();
}

void UVACancellableAsyncAction::Cancel()
{
	// Child classes should override this
	SetReadyToDestroy();
}

bool UVACancellableAsyncAction::IsActive() const
{
	return ShouldBroadcastDelegates();
}

bool UVACancellableAsyncAction::ShouldBroadcastDelegates() const
{
	return IsRegistered();
}

bool UVACancellableAsyncAction::IsRegistered() const
{
	return RegisteredWithGameInstance.IsValid();
}

FTimerManager* UVACancellableAsyncAction::GetTimerManager() const
{
	if (RegisteredWithGameInstance.IsValid())
	{
		return &RegisteredWithGameInstance->GetTimerManager();
	}

	return nullptr;
}