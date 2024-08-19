// Copyright - Vanan A. - 2024
#include "K2Node_SetValueAny.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "Runtime/VAAnyUnreal_FunctionLibrary.h"
#include "Runtime/VAAnyUnreal.h"

#define LOCTEXT_NAMESPACE "K2Node_SetValueAny"

namespace K2Node_SetValueAny
{
	const FName TargetPinName = "Target";
	const FName ValuePinName = "Value";
}


UK2Node_SetValueAny::UK2Node_SetValueAny(const FObjectInitializer& ObjectInitializer) {}

void UK2Node_SetValueAny::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Add execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	UEdGraphPin* ThenPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	// Add Input pin
	UEdGraphPin* TargetPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FVAAnyUnreal::StaticStruct(), K2Node_SetValueAny::TargetPinName);
	TargetPin->PinType.bIsReference = true;

	UEdGraphPin* ValuePin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, K2Node_SetValueAny::ValuePinName);

	Super::AllocateDefaultPins();
}

FText UK2Node_SetValueAny::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	auto* ValueStruct = GetInputStructTypeFromPin();
	if (ValueStruct != nullptr)
	{
		if (CachedNodeTitle.IsOutOfDate(this))
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("StructName"), ValueStruct->GetDisplayNameText());

			FText Format = LOCTEXT("NodeTitleFormat", "Set {StructName} in VA_AnyUnreal");
			CachedNodeTitle.SetCachedText(FText::Format(Format, Args), this);
		}
		return CachedNodeTitle;
	}
	return LOCTEXT("NodeTitle", "Set Struct in VA_AnyUnreal");
}


void UK2Node_SetValueAny::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const FName           FunctionName = GET_FUNCTION_NAME_CHECKED(UVAAnyUnreal_FunctionLibrary, SetValueAny);
	UK2Node_CallFunction* FunctionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	FunctionNode->FunctionReference.SetExternalMember(FunctionName, UVAAnyUnreal_FunctionLibrary::StaticClass());
	FunctionNode->AllocateDefaultPins();

	UEdGraphPin* FunctionTargetPin = FunctionNode->FindPinChecked(TEXT("Target"));
	UEdGraphPin* FunctionValuePin = FunctionNode->FindPinChecked(TEXT("Value"));

	UEdGraphPin* OriginalValuePin = GetValuePin();

	FunctionValuePin->PinType = OriginalValuePin->PinType;
	FunctionValuePin->PinType.PinSubCategoryObject = OriginalValuePin->PinType.PinSubCategoryObject;

	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *FunctionNode->GetExecPin());
	CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *FunctionNode->GetThenPin());
	CompilerContext.MovePinLinksToIntermediate(*GetTargetPin(), *FunctionTargetPin);
	CompilerContext.MovePinLinksToIntermediate(*GetValuePin(), *FunctionValuePin);

	BreakAllNodeLinks();
}

void UK2Node_SetValueAny::PostReconstructNode()
{
	Super::PostReconstructNode();

	RefreshInputPinType();
}

void UK2Node_SetValueAny::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);
}

void UK2Node_SetValueAny::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_SetValueAny::GetMenuCategory() const
{
	return LOCTEXT("MenuCategory", "VA_AnyUnreal");
}

bool UK2Node_SetValueAny::IsConnectionDisallowed(
	const UEdGraphPin* MyPin,
	const UEdGraphPin* OtherPin,
	FString&           OutReason) const
{
	if (MyPin == GetValuePin() && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)
	{
		bool bDisallowed = true;
		if (OtherPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			if (UScriptStruct* ConnectionType = Cast<UScriptStruct>(OtherPin->PinType.PinSubCategoryObject.Get()))
			{
				bDisallowed = !FVAAnyUnreal::IsValidValueStruct(ConnectionType);
			}
		}
		else if (OtherPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)
		{
			bDisallowed = false;
		}

		if (bDisallowed)
		{
			OutReason = TEXT("Must be a struct that can be used in a VA_AnyUnreal");
		}
		return bDisallowed;
	}
	return false;
}

void UK2Node_SetValueAny::EarlyValidation(FCompilerResultsLog& MessageLog) const
{
	Super::EarlyValidation(MessageLog);
}

void UK2Node_SetValueAny::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	if (Pin == GetValuePin())
	{
		RefreshInputPinType();
	}
}

UEdGraphPin* UK2Node_SetValueAny::GetThenPin() const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_Then);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

UEdGraphPin* UK2Node_SetValueAny::GetTargetPin() const
{
	UEdGraphPin* Pin = FindPinChecked(K2Node_SetValueAny::TargetPinName);
	check(Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_SetValueAny::GetValuePin(bool bChecked) const
{
	UEdGraphPin* Pin = FindPin(K2Node_SetValueAny::ValuePinName);

	if (bChecked) { check(Pin != nullptr); }
	check(Pin == nullptr || Pin->Direction == EGPD_Input);

	return Pin;
}

void UK2Node_SetValueAny::RefreshInputPinType()
{
	UScriptStruct* InputType = GetInputStructType();
	SetInputTypeForStruct(InputType);
}

void UK2Node_SetValueAny::SetInputTypeForStruct(UScriptStruct* NewRowStruct)
{
	UScriptStruct* OldRowStruct = GetInputStructTypeFromPin();
	if (NewRowStruct != OldRowStruct)
	{
		UEdGraphPin* ValuePin = GetValuePin();

		if (ValuePin->SubPins.Num() > 0)
		{
			GetSchema()->RecombinePin(ValuePin);
		}

		// NOTE: purposefully not disconnecting the ResultPin (even though it changed type)... we want the user to see the old
		//       connections, and incompatible connections will produce an error (plus, some super-struct connections may still be valid)
		ValuePin->PinType.PinSubCategoryObject = NewRowStruct;
		ValuePin->PinType.PinCategory = (NewRowStruct == nullptr) ? UEdGraphSchema_K2::PC_Wildcard : UEdGraphSchema_K2::PC_Struct;

		CachedNodeTitle.Clear();
	}
}

UScriptStruct* UK2Node_SetValueAny::GetInputStructType() const
{
	UEdGraphPin* ValuePin = GetValuePin();
	if (ValuePin && 0 < ValuePin->LinkedTo.Num())
	{
		const TArray<UEdGraphPin*>& LinkedTo = ValuePin->LinkedTo;
		UScriptStruct*              PinStructType = Cast<UScriptStruct>(LinkedTo[0]->PinType.PinSubCategoryObject.Get());
		for (int32 LinkIndex = 1; LinkIndex < ValuePin->LinkedTo.Num(); ++LinkIndex)
		{
			UEdGraphPin*   Link = LinkedTo[LinkIndex];
			UScriptStruct* LinkType = Cast<UScriptStruct>(Link->PinType.PinSubCategoryObject.Get());

			if (PinStructType->IsChildOf(LinkType))
			{
				PinStructType = LinkType;
			}
		}
		return PinStructType;
	}
	return nullptr;
}

UScriptStruct* UK2Node_SetValueAny::GetInputStructTypeFromPin() const
{
	UEdGraphPin* ValuePin = GetValuePin(false);
	if (ValuePin)
	{
		if (ValuePin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			return Cast<UScriptStruct>(ValuePin->PinType.PinSubCategoryObject.Get());
		}
	}
	return nullptr;
}


#undef LOCTEXT_NAMESPACE