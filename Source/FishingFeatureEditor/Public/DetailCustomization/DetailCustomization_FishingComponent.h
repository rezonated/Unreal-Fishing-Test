// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class UDataAsset_FishingComponentConfig;

/*
 * Detail customization for the fishing component data asset.
 * Adds a custom detail panel for the assigned skeletal mesh bones and socket names.
 */
class FISHINGFEATUREEDITOR_API FDetailCustomization_FishingComponent : public IDetailCustomization
{
public:
	/*
	 * Returns the fishing component data asset detail customization instance.
	 */
	static TSharedRef<IDetailCustomization> MakeInstance();

	/*
	 * Called when the skeletal mesh property is changed, used to update the socket and bone names for the detail panel's dropdown.
	 */
	void OnSkeletalMeshChanged(TSharedRef<IPropertyHandle> SkeletalMeshProperty, TSharedRef<IPropertyHandle> SocketNameProperty);

	/*
	 * Actual implementation of the detail customization.
	 */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	/*
	 * Cached socket and bone names for the current skeletal mesh assigned.
	 */
	TArray<TSharedPtr<FName>> SocketAndBoneNames;
};