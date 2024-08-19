// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "VACancellableAsyncAction.generated.h"

/**
 * This class is a backport of the UCancellableAsyncAction class from UE 5+ to UE 4.27
 * It is used to create cancellable asynchronous action.
 * Since the submission explicitly prohibits Blueprint usage, I won't be backporting the blueprint node (UK2Node_AsyncAction) to UE 4.27, and instead will be using it purely from C++.
 */
UCLASS(Abstract, BlueprintType, meta = (ExposedAsyncProxy = AsyncAction))
class VAGAMEPLAYMESSAGING_API UVACancellableAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/** Handle when this action is being destroyed to ensure that the action is canceled and child classes can clean up. */
	virtual void BeginDestroy() override;

	/** Cancel an asynchronous action, this attempts to cancel any lower level processes and also prevents delegates from being fired */
	UFUNCTION(BlueprintCallable, Category = "Async Action")
	virtual void Cancel();

	/** Returns true if this action is still active and has not completed or been cancelled */
	UFUNCTION(BlueprintCallable, Category = "Async Action")
	virtual bool IsActive() const;

	/** This should be called prior to broadcasting delegates back into the event graph, this ensures the action is still valid */
	virtual bool ShouldBroadcastDelegates() const;

	/** Returns true if this action is registered with a valid game instance */
	bool IsRegistered() const;

	/** Wrapper function to get a timer manager for scheduling callbacks */
	FTimerManager* GetTimerManager() const;
};