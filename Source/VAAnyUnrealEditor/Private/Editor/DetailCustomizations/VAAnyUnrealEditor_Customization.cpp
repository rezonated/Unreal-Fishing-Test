// Copyright - Vanan A. - 2024
#include "VAAnyUnrealEditor_Customization.h"

#include "Editor.h"
#include "Widgets/Input/STextComboBox.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailPropertyRow.h"
#include "IPropertyUtilities.h"
#include "StructViewerFilter.h"
#include "StructViewerModule.h"
#include "EdGraphSchema_K2.h"
#include "Editor/TransBuffer.h"
#include "ScopedTransaction.h"
#include "Misc/NotifyHook.h"
#include "Modules/ModuleManager.h"

//#include "PropertyEditor/Private/PropertyNode.h"


#define LOCTEXT_NAMESPACE "VAAnyUnrealEditorCustomization"


namespace VAAnyUnrealEditorCustomization
{
	static FName GetTypeName()
	{
		return FVAAnyUnreal::StaticStruct()->GetFName();
	}

	static const FText Transaction_SetValueType = LOCTEXT("Transaction_SetValueType", "Set ValueType");

	static const FName MD_AllowedStructs = "AllowedStructs";

	TArray<TSoftObjectPtr<UScriptStruct>> GetStructsByMetaDataString(const FString& MetadataString)
	{
		TArray<FString> StructNames;
		MetadataString.ParseIntoArrayWS(StructNames, TEXT(","), true);

		TArray<TSoftObjectPtr<UScriptStruct>> Structs;
		Structs.Reserve(StructNames.Num());

		for (const FString& StructName : StructNames)
		{
			const UScriptStruct* Struct = FindObject<UScriptStruct>(ANY_PACKAGE, *StructName);
			if (!Struct)
			{
				continue;
			}
			Structs.Add(Struct);
		}

		return Structs;
	}


	class FVAAnyUnrealEditorCustomizationStructFilter final : public IStructViewerFilter
	{
	public:
		// IStructViewerFilter interface.
		virtual bool IsStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const UScriptStruct* InStruct, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
		{
			const bool bBlueprintType = InStruct->GetBoolMetaData(FBlueprintMetadata::MD_AllowableBlueprintVariableType);
			if (!bBlueprintType)
			{
				return false;
			}

			if (AllowedStructs.Num() != 0)
			{
				bool bAllowed = AllowedStructs.ContainsByPredicate([&](TSoftObjectPtr<UScriptStruct> AllowedStructPath) {
					UScriptStruct* AllowedStruct = AllowedStructPath.LoadSynchronous();

					if (AllowedStruct && InStruct->IsChildOf(AllowedStruct))
					{
						return true;
					}
					return false;
				});
				if (!bAllowed)
				{
					return false;
				}
			}

			return FVAAnyUnreal::IsValidValueStruct(InStruct);
		}

		virtual bool IsUnloadedStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const FName InStructPath, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
		{
			return false;
		}

		// End of IStructViewerFilter interface.

		void SetAllowedStructsByMetaDataString(const FString& MetadataString)
		{
			AllowedStructs = GetStructsByMetaDataString(MetadataString);
		}


		TArray<TSoftObjectPtr<UScriptStruct>> AllowedStructs;
	};


	const UScriptStruct* GetDefaultStruct(IPropertyHandle& PropertyHandle)
	{
		if (PropertyHandle.HasMetaData(MD_AllowedStructs))
		{
			// FVAAnyUnrealEditorCustomizationStructFilter Filter;
			// Filter.SetAllowedStructsByMetaDataString(PropertyHandle.GetMetaData(MD_AllowedStructs));
			// for(UScriptStruct* Struct : TObjectRange<UScriptStruct>())
			// {
			// }
			TArray<TSoftObjectPtr<UScriptStruct>> Structs = GetStructsByMetaDataString(PropertyHandle.GetMetaData(MD_AllowedStructs));
			for (TSoftObjectPtr<UScriptStruct> Struct : Structs)
			{
				auto* LoadedStruct = Struct.LoadSynchronous();
				if (LoadedStruct)
				{
					return LoadedStruct;
				}
			}
		}
		return TBaseStructure<FVector>::Get();
	}

}

FVAAnyUnrealEditor_Customization::FValueChanged FVAAnyUnrealEditor_Customization::OnValueChanged;

void FVAAnyUnrealEditor_Customization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomPropertyTypeLayout(
		VAAnyUnrealEditorCustomization::GetTypeName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FVAAnyUnrealEditor_Customization::MakeInstance));
}

void FVAAnyUnrealEditor_Customization::Unregister()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout(VAAnyUnrealEditorCustomization::GetTypeName());
}


TSharedRef<IPropertyTypeCustomization> FVAAnyUnrealEditor_Customization::MakeInstance()
{
	return MakeShared<FVAAnyUnrealEditor_Customization>();
}

FVAAnyUnrealEditor_Customization::FVAAnyUnrealEditor_Customization()
{
	InitializeTypePickerOptions();
}

void FVAAnyUnrealEditor_Customization::CustomizeHeader(
	TSharedRef<IPropertyHandle>      PropertyHandle,
	FDetailWidgetRow&                HeaderRow,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	OnValueChanged.RemoveAll(this);
	OnValueChanged.AddSP(this, &FVAAnyUnrealEditor_Customization::HandleValueChanged);

	StructPropertyHandle = PropertyHandle;
	InitializeTypePickerOptions();

	UTransBuffer* Trans = GEditor ? Cast<UTransBuffer>(GEditor->Trans) : nullptr;
	if (Trans)
	{
		Trans->OnRedo().RemoveAll(this);
		Trans->OnUndo().RemoveAll(this);
		Trans->OnRedo().AddSP(this, &FVAAnyUnrealEditor_Customization::HandleRedoUndo);
		Trans->OnUndo().AddSP(this, &FVAAnyUnrealEditor_Customization::HandleRedoUndo);
	}

	const auto* StructProperty = CastFieldChecked<FStructProperty>(PropertyHandle->GetProperty());
	if (!StructProperty || StructProperty->Struct != FVAAnyUnreal::StaticStruct())
	{
		return;
	}

	TSharedPtr<FString>     TypeName;
	FPropertyAccess::Result Result = GetTypeName(TypeName);
	if (Result == FPropertyAccess::MultipleValues)
	{
		TypeName = MultipleValuesOption;
	}

	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(200)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(TypePickerComboButton, STextComboBox)
				.ContentPadding(FMargin(2, 2, 2, 1))
				.OptionsSource(&TypePickerOptions)
				.InitiallySelectedItem(TypeName)
				.OnSelectionChanged(this, &FVAAnyUnrealEditor_Customization::OnValueTypePicked)
				.IsEnabled(this, &FVAAnyUnrealEditor_Customization::IsPropertyEditable)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(StructPickerComboButton, SComboButton)
				.ContentPadding(FMargin(2, 2, 2, 1))
				.MenuPlacement(MenuPlacement_BelowAnchor)
				.ButtonContent()
				[
					SNew(STextBlock)
					.Text(this, &FVAAnyUnrealEditor_Customization::OnGetComboTextValue)
				]
				.OnGetMenuContent(this, &FVAAnyUnrealEditor_Customization::GenerateStructPicker)
				.IsEnabled(this, &FVAAnyUnrealEditor_Customization::IsPropertyEditable)
				.Visibility(this, &FVAAnyUnrealEditor_Customization::GetStructPickerVisibility)
			]
		];
}

void FVAAnyUnrealEditor_Customization::CustomizeChildren(
	TSharedRef<IPropertyHandle>      PropertyHandle,
	IDetailChildrenBuilder&          ChildBuilder,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	PropertyUtilities = CustomizationUtils.GetPropertyUtilities();
	const UScriptStruct*          ScriptStruct = nullptr;
	const FPropertyAccess::Result Result = GetValueStruct(ScriptStruct);
	if (Result != FPropertyAccess::Success)
	{
		StructValue = nullptr;
		return;
	}

	const TArray<FVAAnyUnreal*> Values = GetPropertyValues();
	if (Values.Num() != 1)
	{
		StructValue = nullptr;
		return;
	}

	FVAAnyUnreal* Value = Values[0];
	if (Value == nullptr || !Value->IsValid())
	{
		StructValue = nullptr;
		return;;
	}

	FText StructName;
	{
		TSharedPtr<FString>     TypeName;
		FPropertyAccess::Result TypeNameResult = GetTypeName(TypeName);
		if (TypeName)
		{
			if (TypeName == AnyStructTypeOption)
			{
				StructName = Value->GetStruct()->GetDisplayNameText();
			}
			else
			{
				StructName = FText::FromString(*TypeName);
			}
		}
	}

	StructValue = MakeShared<FStructOnScope>(Value->GetStruct(), static_cast<uint8*>(Value->GetData()));
	if (StructValue)
	{
		IDetailPropertyRow* PropertyRow = ChildBuilder.AddExternalStructure(StructValue.ToSharedRef());
		if (PropertyRow)
		{
			PropertyRow->DisplayName(StructName);
			PropertyRow->IsEnabled(TAttribute<bool>(this, &FVAAnyUnrealEditor_Customization::IsPropertyEditable));

			const auto OnValueChangedDelegate = FSimpleDelegate::CreateSP(this, &FVAAnyUnrealEditor_Customization::OnStructValueChanged);
			PropertyRow->GetPropertyHandle()->SetOnPropertyValueChanged(OnValueChangedDelegate);
			PropertyRow->GetPropertyHandle()->SetOnChildPropertyValueChanged(OnValueChangedDelegate);
		}
	}
}

void FVAAnyUnrealEditor_Customization::InitializeTypePickerOptions()
{
	TypePickerOptions.Reset();
	NoneTypeOption.Reset();
	AnyStructTypeOption.Reset();
	TypeNameToStructMap.Reset();

	MultipleValuesOption = MakeShared<FString>(TEXT("MultipleValues"));
	NoneTypeOption = MakeShared<FString>(TEXT("None"));
	AnyStructTypeOption = MakeShared<FString>(TEXT("Structure"));

	TypePickerOptions.Add(NoneTypeOption);
	TypePickerOptions.Add(AnyStructTypeOption);

	bool bHasAllowedStructs = false;
	if (StructPropertyHandle)
	{
		bHasAllowedStructs = StructPropertyHandle->HasMetaData(VAAnyUnrealEditorCustomization::MD_AllowedStructs);
	}

	if (!bHasAllowedStructs)
	{
		TArray<VAAnyUnreal::FVAAnyUnreal_SingleValueStructInfo> SingleValueStructs = VAAnyUnreal::FVAAnyUnreal_SingleValueStructRegistry::Get().GetStructs();
		for (const auto& StructInfo : SingleValueStructs)
		{
			TSharedPtr<FString> TypeName = MakeShared<FString>(StructInfo.TypeName);
			TypePickerOptions.Add(TypeName);
			TypeNameToStructMap.Add(TypeName, StructInfo.StructPath);
		}
	}
}


FText FVAAnyUnrealEditor_Customization::OnGetComboTextValue() const
{
	const UScriptStruct*          Struct = nullptr;
	const FPropertyAccess::Result Result = GetValueStruct(Struct);

	if (Result == FPropertyAccess::Success)
	{
		return Struct ? Struct->GetDisplayNameText() : LOCTEXT("None", "None");
	}

	if (Result == FPropertyAccess::MultipleValues)
	{
		return LOCTEXT("MultipleValues", "MultipleValues");
	}

	return FText::GetEmpty();
}

TSharedRef<SWidget> FVAAnyUnrealEditor_Customization::GenerateStructPicker()
{
	FStructViewerModule& StructViewerModule = FModuleManager::LoadModuleChecked<FStructViewerModule>("StructViewer");

	TSharedRef<VAAnyUnrealEditorCustomization::FVAAnyUnrealEditorCustomizationStructFilter> StructFilter = MakeShared<VAAnyUnrealEditorCustomization::FVAAnyUnrealEditorCustomizationStructFilter>();

	FString AllowedStructs = StructPropertyHandle->GetMetaData(VAAnyUnrealEditorCustomization::MD_AllowedStructs);
	StructFilter->SetAllowedStructsByMetaDataString(AllowedStructs);

	FStructViewerInitializationOptions Options;
	Options.Mode = EStructViewerMode::StructPicker;
	Options.StructFilter = StructFilter;

	const TSharedRef<SWidget> StructViewer = StructViewerModule.CreateStructViewer(
		Options,
		FOnStructPicked::CreateSP(this, &FVAAnyUnrealEditor_Customization::OnValueStructPicked));

	return
			SNew(SBox)
			.WidthOverride(330)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.MaxHeight(500)
				[
					SNew(SBorder)
					.Padding(4)
					.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
					[
						StructViewer
					]
				]
			];
}

bool FVAAnyUnrealEditor_Customization::IsPropertyEditable() const
{
	if (StructPropertyHandle)
	{
		return StructPropertyHandle->IsEditable();
	}

	return false;
}

EVisibility FVAAnyUnrealEditor_Customization::GetStructPickerVisibility() const
{
	TSharedPtr<FString>     TypeName;
	FPropertyAccess::Result Result = GetTypeName(TypeName);

	if (Result != FPropertyAccess::Success)
	{
		return EVisibility::Collapsed;
	}

	if (TypeName != AnyStructTypeOption)
	{
		return EVisibility::Collapsed;
	}

	return EVisibility::Visible;
}

void FVAAnyUnrealEditor_Customization::OnValueTypePicked(TSharedPtr<FString> ChosenType, ESelectInfo::Type SelectInfo)
{
	if (StructPropertyHandle == nullptr)
	{
		return;
	}
	FScopedTransaction Transaction(VAAnyUnrealEditorCustomization::Transaction_SetValueType);

	FEditPropertyChain PropertyChain;
	PropertyChain.AddHead(StructPropertyHandle->GetProperty());

	// Fire off the pre-notify
	StructPropertyHandle->NotifyPreChange();

	ModifyOuterObjects();

	TArray<FVAAnyUnreal*> Values = GetPropertyValues();

	if (ChosenType == NoneTypeOption)
	{
		for (FVAAnyUnreal* Value : Values)
		{
			if (Value)
			{
				Value->Reset();
			}
		}
	}
	else if (ChosenType == AnyStructTypeOption)
	{
		const UScriptStruct* DefaultStruct = VAAnyUnrealEditorCustomization::GetDefaultStruct(*StructPropertyHandle);
		for (FVAAnyUnreal* Value : Values)
		{
			if (Value)
			{
				TSharedPtr<FString> CurrentTypeName = GetTypeNameByValue(*Value);
				if (CurrentTypeName != ChosenType)
				{
					Value->Emplace(DefaultStruct);
				}
			}
		}
	}
	else
	{
		const FSoftObjectPath StructPath = TypeNameToStructMap.FindRef(ChosenType);
		UScriptStruct*        Struct = Cast<UScriptStruct>(StructPath.TryLoad());
		for (FVAAnyUnreal* Value : Values)
		{
			if (Value)
			{
				if (Struct)
				{
					Value->Emplace(Struct);
				}
				else
				{
					Value->Reset();
				}
			}
		}
	}

	StructPropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
	if (PropertyUtilities)
	{
		PropertyUtilities->ForceRefresh();
	}

	OnValueChanged.Broadcast(StructPropertyHandle, Values);
}

void FVAAnyUnrealEditor_Customization::OnValueStructPicked(const UScriptStruct* ChosenStruct)
{
	if (StructPropertyHandle == nullptr)
	{
		return;
	}
	FScopedTransaction Transaction(LOCTEXT("Transaction_OnValueStructPicked", "Set ValueStruct"));

	FEditPropertyChain PropertyChain;
	PropertyChain.AddHead(StructPropertyHandle->GetProperty());

	// Fire off the pre-notify
	StructPropertyHandle->NotifyPreChange();

	ModifyOuterObjects();

	TArray<FVAAnyUnreal*> Values = GetPropertyValues();

	if (ChosenStruct != nullptr)
	{
		for (FVAAnyUnreal* Value : Values)
		{
			if (Value != nullptr && Value->GetStruct() != ChosenStruct)
			{
				Value->Emplace(ChosenStruct);
			}
		}
	}
	else
	{
		for (FVAAnyUnreal* Value : Values)
		{
			if (Value != nullptr)
			{
				Value->Reset();
			}
		}
	}

	FPropertyChangedEvent BubbleChangeEvent(StructPropertyHandle->GetProperty(), EPropertyChangeType::ValueSet);

	// post notify
	StructPropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
	if (PropertyUtilities)
	{
		PropertyUtilities->ForceRefresh();
	}

	OnValueChanged.Broadcast(StructPropertyHandle, Values);

	StructPickerComboButton->SetIsOpen(false);
}

FPropertyAccess::Result FVAAnyUnrealEditor_Customization::GetValueStruct(const UScriptStruct*& OutScriptStruct) const
{
	OutScriptStruct = nullptr;

	if (StructPropertyHandle == nullptr)
	{
		return FPropertyAccess::Fail;
	}

	TArray<FVAAnyUnreal*> Values = GetPropertyValues();
	if (Values.Num() == 0 || Values[0] == nullptr)
	{
		return FPropertyAccess::Fail;
	}

	const UScriptStruct* FirstValurStruct = Values[0]->GetStruct();
	for (int32 i = 1; i < Values.Num(); ++i)
	{
		const auto* ValuePtr = Values[i];
		if (ValuePtr == nullptr)
		{
			return FPropertyAccess::Fail;
		}

		if (ValuePtr->GetStruct() != FirstValurStruct)
		{
			return FPropertyAccess::MultipleValues;
		}
	}

	OutScriptStruct = FirstValurStruct;
	return FPropertyAccess::Success;
}

FPropertyAccess::Result FVAAnyUnrealEditor_Customization::GetTypeName(TSharedPtr<FString>& OutTypeName) const
{
	OutTypeName = nullptr;

	if (StructPropertyHandle == nullptr)
	{
		return FPropertyAccess::Fail;
	}

	TArray<FVAAnyUnreal*> Values = GetPropertyValues();
	if (Values.Num() == 0 || Values[0] == nullptr)
	{
		return FPropertyAccess::Fail;
	}

	TSharedPtr<FString> FirstTypeName = GetTypeNameByValue(*Values[0]);
	for (int32 i = 1; i < Values.Num(); ++i)
	{
		if (Values[i] == nullptr)
		{
			return FPropertyAccess::Fail;
		}

		TSharedPtr<FString> TypeName = GetTypeNameByValue(*Values[i]);
		if (FirstTypeName != TypeName)
		{
			return FPropertyAccess::MultipleValues;
		}
	}

	OutTypeName = FirstTypeName;
	return FPropertyAccess::Success;
}

TArray<FVAAnyUnreal*> FVAAnyUnrealEditor_Customization::GetPropertyValues() const
{
	TArray<FVAAnyUnreal*> PropertyValues;
	TArray<void*>         RawData;
	StructPropertyHandle->AccessRawData(RawData);

	PropertyValues.Reserve(RawData.Num());

	for (void* Ptr : RawData)
	{
		PropertyValues.Add(static_cast<FVAAnyUnreal*>(Ptr));
	}

	return PropertyValues;
}

TSharedPtr<FString> FVAAnyUnrealEditor_Customization::GetTypeNameByValue(const FVAAnyUnreal& InValue) const
{
	if (!InValue.IsValid())
	{
		return NoneTypeOption;
	}

	FSoftObjectPath StructPath = InValue.GetStruct();
	for (const auto& Pair : TypeNameToStructMap)
	{
		if (Pair.Value == StructPath)
		{
			return Pair.Key;
		}
	}

	return AnyStructTypeOption;
}


void FVAAnyUnrealEditor_Customization::OnStructValueChanged()
{
	ModifyOuterObjects();

	TArray<FVAAnyUnreal*> Values = GetPropertyValues();
	if (Values.Num() <= 1 || Values[0] != nullptr)
	{
		return;
	}

	const FVAAnyUnreal* FirstValue = Values[0];
	for (int32 i = 1; i < Values.Num(); ++i)
	{
		if (Values[i] != nullptr)
		{
			*Values[i] = *FirstValue;
		}
	}

	StructPropertyHandle->NotifyFinishedChangingProperties();
}

void FVAAnyUnrealEditor_Customization::ModifyOuterObjects()
{
	TArray<UObject*> Outers;
	StructPropertyHandle->GetOuterObjects(Outers);
	for (UObject* Object : Outers)
	{
		Object->Modify();
	}
}

void FVAAnyUnrealEditor_Customization::HandleRedoUndo(const FTransactionContext& TransactionContext, bool Succeeded)
{
	if (TransactionContext.Title.IdenticalTo(VAAnyUnrealEditorCustomization::Transaction_SetValueType))
	{
		if (PropertyUtilities)
		{
			PropertyUtilities->ForceRefresh();
		}
	}
}


void FVAAnyUnrealEditor_Customization::HandleValueChanged(const TSharedPtr<IPropertyHandle>& PropertyHandle, const TArray<FVAAnyUnreal*>& PropertyValues)
{
	if (PropertyHandle != StructPropertyHandle)
	{
		TArray<FVAAnyUnreal*> Values = GetPropertyValues();

		bool bRefresh = false;
		for (FVAAnyUnreal* Value : Values)
		{
			if (PropertyValues.Contains(Value))
			{
				bRefresh = true;
				break;
			}
		}

		if (bRefresh)
		{
			if (PropertyUtilities)
			{
				PropertyUtilities->ForceRefresh();
			}
		}
	}
}


#undef LOCTEXT_NAMESPACE