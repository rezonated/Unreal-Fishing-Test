// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class UDataAsset_FishingComponentConfig;

class FISHINGFEATUREEDITOR_API FDetailCustomization_FishingComponent : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	void OnSkeletalMeshChanged(TSharedRef<IPropertyHandle> SkeletalMeshProperty, TSharedRef<IPropertyHandle> SocketNameProperty);

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	TArray<TSharedPtr<FName>> SocketAndBoneNames;
};