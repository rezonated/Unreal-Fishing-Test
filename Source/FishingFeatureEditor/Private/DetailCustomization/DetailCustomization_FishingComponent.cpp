#include "FishingFeatureEditor/Public/DetailCustomization/DetailCustomization_FishingComponent.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Engine/SkeletalMeshSocket.h"

TSharedRef<IDetailCustomization> FDetailCustomization_FishingComponent::MakeInstance()
{
	return MakeShareable(new FDetailCustomization_FishingComponent);
}

void FDetailCustomization_FishingComponent::OnSkeletalMeshChanged(TSharedRef<IPropertyHandle> SkeletalMeshProperty, TSharedRef<IPropertyHandle> SocketNameProperty)
{
	// Validate the SkeletalMesh property
	USkeletalMesh* SkeletalMesh = nullptr;
	if (SkeletalMeshProperty->GetValue((UObject*&)SkeletalMesh) != FPropertyAccess::Success || !SkeletalMesh)
	{
		// Early return if SkeletalMesh is invalid or null
		SocketAndBoneNames.Reset(); // Clear the dropdown options
		return;
	}

	// Clear any previous data in SocketAndBoneNames
	SocketAndBoneNames.Reset();

	// Populate bone names
	const int32 NumBones = SkeletalMesh->GetRefSkeleton().GetNum();
	SocketAndBoneNames.Reserve(NumBones); // Pre-allocate memory for bones
	for (int32 i = 0; i < NumBones; ++i)
	{
		SocketAndBoneNames.Add(MakeShared<FName>(SkeletalMesh->GetRefSkeleton().GetBoneName(i)));
	}

	// Populate socket names
	const TArray<USkeletalMeshSocket*>& Sockets = SkeletalMesh->GetActiveSocketList();
	SocketAndBoneNames.Reserve(SocketAndBoneNames.Num() + Sockets.Num()); // Reserve additional space for sockets
	for (const USkeletalMeshSocket* Socket : Sockets)
	{
		SocketAndBoneNames.Add(MakeShared<FName>(Socket->SocketName));
	}

	TArray<FName> Names;
	for (const TSharedPtr<FName>& Name : SocketAndBoneNames)
	{
		Names.Add(*Name.Get());
	}

	FName CurrentSocketNameValue;
	SocketNameProperty->GetValue(CurrentSocketNameValue);

	if (CurrentSocketNameValue == NAME_None || !Names.Contains(CurrentSocketNameValue))
	{
		SocketNameProperty->SetValue(*SocketAndBoneNames[0]);
	}
	else
	{
		SocketNameProperty->SetValue(CurrentSocketNameValue);
	}
}

void FDetailCustomization_FishingComponent::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Get the struct handle first
	TSharedRef<IPropertyHandle> MeshSocketStructHandle = DetailBuilder.GetProperty("FishingComponentConfig");

	// Access the SkeletalMesh and SocketOrBoneName properties from the struct
	TSharedRef<IPropertyHandle> OwnerSkeletalMeshProperty = MeshSocketStructHandle->GetChildHandle("OwnerSkeletalMesh").ToSharedRef();
	TSharedRef<IPropertyHandle> FishingPoleSocketNameProperty = MeshSocketStructHandle->GetChildHandle("FishingPoleSocketName").ToSharedRef();
	TSharedRef<IPropertyHandle> CarryFishSocketNameProperty = MeshSocketStructHandle->GetChildHandle("CarryFishSocketName").ToSharedRef();

	// Register a callback for when the SkeletalMesh property changes
	OwnerSkeletalMeshProperty->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda([this, OwnerSkeletalMeshProperty, FishingPoleSocketNameProperty, CarryFishSocketNameProperty]() {
		OnSkeletalMeshChanged(OwnerSkeletalMeshProperty, FishingPoleSocketNameProperty);
		OnSkeletalMeshChanged(OwnerSkeletalMeshProperty, CarryFishSocketNameProperty);
	}));

	// Initial population of the dropdown
	OnSkeletalMeshChanged(OwnerSkeletalMeshProperty, FishingPoleSocketNameProperty);
	OnSkeletalMeshChanged(OwnerSkeletalMeshProperty, CarryFishSocketNameProperty);

	DetailBuilder.HideProperty(FishingPoleSocketNameProperty);
	DetailBuilder.HideProperty(CarryFishSocketNameProperty);

	// Add a custom row with a combo box for the socket and bone names
	IDetailCategoryBuilder& SocketCategory = DetailBuilder.EditCategory("Fishing Component Config");

	SocketCategory.AddCustomRow(FishingPoleSocketNameProperty->GetPropertyDisplayName())
	              .NameContent()
		[
			FishingPoleSocketNameProperty->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(SComboBox<TSharedPtr<FName>>)
			.OptionsSource(&SocketAndBoneNames)
			.OnGenerateWidget_Lambda([](TSharedPtr<FName> Item) {
				return SNew(STextBlock).Text(FText::FromName(*Item));
			})
			.OnSelectionChanged_Lambda([FishingPoleSocketNameProperty](TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo) {
				if (NewSelection.IsValid())
				{
					FishingPoleSocketNameProperty->SetValue(*NewSelection);
				}
			})
			.Content()
			[
				SNew(STextBlock)
				.Text_Lambda([FishingPoleSocketNameProperty]() {
					FName CurrentValue;
					FishingPoleSocketNameProperty->GetValue(CurrentValue);
					return FText::FromName(CurrentValue);
				})
			]
		];

	SocketCategory.AddCustomRow(CarryFishSocketNameProperty->GetPropertyDisplayName())
	              .NameContent()
		[
			CarryFishSocketNameProperty->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(SComboBox<TSharedPtr<FName>>)
			.OptionsSource(&SocketAndBoneNames)
			.OnGenerateWidget_Lambda([](TSharedPtr<FName> Item) {
				return SNew(STextBlock).Text(FText::FromName(*Item));
			})
			.OnSelectionChanged_Lambda([CarryFishSocketNameProperty](TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo) {
				if (NewSelection.IsValid())
				{
					CarryFishSocketNameProperty->SetValue(*NewSelection);
				}
			})
			.Content()
			[
				SNew(STextBlock)
				.Text_Lambda([CarryFishSocketNameProperty]() {
					FName CurrentValue;
					CarryFishSocketNameProperty->GetValue(CurrentValue);
					return FText::FromName(CurrentValue);
				})
			]
		];
}