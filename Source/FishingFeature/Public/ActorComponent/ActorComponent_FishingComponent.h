// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Struct/FishingComponentConfig.h"
#include "ActorComponent_FishingComponent.generated.h"


class UDataAsset_FishingComponentConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FISHINGFEATURE_API UActorComponent_FishingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorComponent_FishingComponent();

protected:
	virtual void BeginPlay() override;

	void BindToPlayerActionInputDelegates();
	
	void OnCastAction(const float& InElapsedTime);
	void OnCastActionEnded(const float&);

	float GetMappedProgress(const float& InValue, const float DefaultValue = 0.f) const;

	UPROPERTY(EditDefaultsOnly, Category = "Fishing Component | Config")
	UDataAsset_FishingComponentConfig* FishingComponentConfigData = nullptr;
};