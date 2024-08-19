// Copyright - Vanan A. - 2024
#pragma once


#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/STextComboBox.h"
#include "Layout/Visibility.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyEditorModule.h"
#include "VAAnyUnreal/Public/Runtime/VAAnyUnreal.h"


class IDetailPropertyRow;


class FVAAnyUnrealEditor_Customization final
	: public IPropertyTypeCustomization
{
	DECLARE_MULTICAST_DELEGATE_TwoParams(FValueChanged, const TSharedPtr<IPropertyHandle>&, const TArray<FVAAnyUnreal*>&);
	static FValueChanged OnValueChanged;

public:
	static void Register();
	static void Unregister();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();


	FVAAnyUnrealEditor_Customization();

	// IPropertyTypeCustomization interface
	virtual void CustomizeHeader(
		TSharedRef<IPropertyHandle>      PropertyHandle,
		FDetailWidgetRow&                HeaderRow,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(
		TSharedRef<IPropertyHandle>      PropertyHandle,
		IDetailChildrenBuilder&          ChildBuilder,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	// End IPropertyTypeCustomization interface


private:
	void InitializeTypePickerOptions();

	FText               OnGetComboTextValue() const;
	TSharedRef<SWidget> GenerateStructPicker();
	bool                IsPropertyEditable() const;
	EVisibility         GetStructPickerVisibility() const;

	void OnValueTypePicked(TSharedPtr<FString> ChosenType, ESelectInfo::Type SelectInfo);
	void OnValueStructPicked(const UScriptStruct* ChosenStruct);

	FPropertyAccess::Result GetValueStruct(const UScriptStruct*& OutScriptStruct) const;
	FPropertyAccess::Result GetTypeName(TSharedPtr<FString>& OutTypeName) const;
	TArray<FVAAnyUnreal*>   GetPropertyValues() const;
	TSharedPtr<FString>     GetTypeNameByValue(const FVAAnyUnreal& InValue) const;

	void OnStructValueChanged();
	void ModifyOuterObjects();

	void HandleRedoUndo(const struct FTransactionContext& TransactionContext, bool Succeeded);


	void HandleValueChanged(const TSharedPtr<IPropertyHandle>& PropertyHandle, const TArray<FVAAnyUnreal*>& PropertyValues);

	TSharedPtr<IPropertyUtilities> PropertyUtilities;
	TSharedPtr<IPropertyHandle>    StructPropertyHandle;

	TArray<TSharedPtr<FString>>                TypePickerOptions;
	TSharedPtr<FString>                        MultipleValuesOption;
	TSharedPtr<FString>                        NoneTypeOption;
	TSharedPtr<FString>                        AnyStructTypeOption;
	TMap<TSharedPtr<FString>, FSoftObjectPath> TypeNameToStructMap;
	TSharedPtr<STextComboBox>                  TypePickerComboButton;
	TSharedPtr<SComboButton>                   StructPickerComboButton;

	TSharedPtr<FStructOnScope> StructValue;
};