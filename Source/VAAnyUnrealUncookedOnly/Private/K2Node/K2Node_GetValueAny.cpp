// Copyright - Vanan A. - 2024
#include "K2Node_GetValueAny.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_CallFunction.h"
#include "K2Node_IfThenElse.h"
#include "KismetCompiler.h"
#include "Runtime/VAAnyUnreal_FunctionLibrary.h"
#include "Runtime/VAAnyUnreal.h"


#define LOCTEXT_NAMESPACE "K2Node_GetValueAny"

namespace K2Node_GetValueAny
{
	const FName FailedPinName = "Failed";

	const FName InputValuePinName = "InputValue";
	const FName ResultPinName = "OutResult";
}

UK2Node_GetValueAny::UK2Node_GetValueAny(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

void UK2Node_GetValueAny::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Add execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	UEdGraphPin* ValidPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, K2Node_GetValueAny::FailedPinName);

	// Add Input pin
	UEdGraphPin* InputValuePin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FVAAnyUnreal::StaticStruct(), K2Node_GetValueAny::InputValuePinName);

	UEdGraphPin* ResultPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, K2Node_GetValueAny::ResultPinName);
	ResultPin->PinFriendlyName = LOCTEXT("ResultValue", "Result Value");

	Super::AllocateDefaultPins();
}

FText UK2Node_GetValueAny::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	auto* ValueStruct = GetResultStructTypeFromResultPin();
	if (ValueStruct != nullptr)
	{
		if (CachedNodeTitle.IsOutOfDate(this))
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("StructName"), ValueStruct->GetDisplayNameText());

			FText Format = LOCTEXT("NodeTitleFormat", "Get {StructName} from VA_AnyUnreal");
			CachedNodeTitle.SetCachedText(FText::Format(Format, Args), this);
		}
		return CachedNodeTitle;
	}
	return LOCTEXT("NodeTitle", "Get Struct from VA_AnyUnreal");
}

void UK2Node_GetValueAny::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	UEdGraphPin* InputValuePin = GetInputValuePin();

	const FName           FunctionName = GET_FUNCTION_NAME_CHECKED(UVAAnyUnreal_FunctionLibrary, GetValueAny);
	UK2Node_CallFunction* FunctionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	FunctionNode->FunctionReference.SetExternalMember(FunctionName, UVAAnyUnreal_FunctionLibrary::StaticClass());
	FunctionNode->AllocateDefaultPins();

	UEdGraphPin* FunctionInputPin = FunctionNode->FindPinChecked(TEXT("InputValue"));
	UEdGraphPin* FunctionOutValuePin = FunctionNode->FindPinChecked(TEXT("OutResult"));
	UEdGraphPin* FunctionReturnPin = FunctionNode->FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue);
	UEdGraphPin* FunctionThenPin = FunctionNode->GetThenPin();

	UEdGraphPin* OriginalOutValuePin = GetResultPin();

	FunctionOutValuePin->PinType = OriginalOutValuePin->PinType;
	FunctionOutValuePin->PinType.PinSubCategoryObject = OriginalOutValuePin->PinType.PinSubCategoryObject;

	//BRANCH NODE
	UK2Node_IfThenElse* BranchNode = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
	BranchNode->AllocateDefaultPins();
	// Hook up inputs to branch
	FunctionThenPin->MakeLinkTo(BranchNode->GetExecPin());
	FunctionReturnPin->MakeLinkTo(BranchNode->GetConditionPin());

	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *FunctionNode->GetExecPin());
	CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *BranchNode->GetThenPin());
	CompilerContext.MovePinLinksToIntermediate(*GetFailedPin(), *BranchNode->GetElsePin());
	CompilerContext.MovePinLinksToIntermediate(*GetInputValuePin(), *FunctionInputPin);
	CompilerContext.MovePinLinksToIntermediate(*OriginalOutValuePin, *FunctionOutValuePin);

	BreakAllNodeLinks();
}

void UK2Node_GetValueAny::PostReconstructNode()
{
	Super::PostReconstructNode();

	RefreshOutputPinType();
}

void UK2Node_GetValueAny::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);
}

void UK2Node_GetValueAny::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_GetValueAny::GetMenuCategory() const
{
	return LOCTEXT("MenuCategory", "VA_AnyUnreal");
}

bool UK2Node_GetValueAny::IsConnectionDisallowed(
	const UEdGraphPin* MyPin,
	const UEdGraphPin* OtherPin,
	FString&           OutReason) const
{
	if (MyPin == GetResultPin() && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)
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

void UK2Node_GetValueAny::EarlyValidation(FCompilerResultsLog& MessageLog) const
{
	Super::EarlyValidation(MessageLog);
}

void UK2Node_GetValueAny::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	if (Pin == GetResultPin())
	{
		RefreshOutputPinType();
	}
}

UEdGraphPin* UK2Node_GetValueAny::GetThenPin() const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_Then);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

UEdGraphPin* UK2Node_GetValueAny::GetFailedPin() const
{
	UEdGraphPin* Pin = FindPinChecked(K2Node_GetValueAny::FailedPinName);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

UEdGraphPin* UK2Node_GetValueAny::GetInputValuePin() const
{
	UEdGraphPin* Pin = FindPinChecked(K2Node_GetValueAny::InputValuePinName);
	check(Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_GetValueAny::GetResultPin(bool bChecked) const
{
	UEdGraphPin* Pin = FindPin(K2Node_GetValueAny::ResultPinName);

	if (bChecked) { check(Pin != nullptr); }
	check(Pin == nullptr || Pin->Direction == EGPD_Output);

	return Pin;
}

void UK2Node_GetValueAny::RefreshOutputPinType()
{
	UScriptStruct* OutputType = GetResultStructType();
	SetReturnTypeForStruct(OutputType);
}

void UK2Node_GetValueAny::SetReturnTypeForStruct(UScriptStruct* NewRowStruct)
{
	UScriptStruct* OldRowStruct = GetResultStructTypeFromResultPin();
	if (NewRowStruct != OldRowStruct)
	{
		UEdGraphPin* ResultPin = GetResultPin();

		if (ResultPin->SubPins.Num() > 0)
		{
			GetSchema()->RecombinePin(ResultPin);
		}

		// NOTE: purposefully not disconnecting the ResultPin (even though it changed type)... we want the user to see the old
		//       connections, and incompatible connections will produce an error (plus, some super-struct connections may still be valid)
		ResultPin->PinType.PinSubCategoryObject = NewRowStruct;
		ResultPin->PinType.PinCategory = (NewRowStruct == nullptr) ? UEdGraphSchema_K2::PC_Wildcard : UEdGraphSchema_K2::PC_Struct;

		CachedNodeTitle.Clear();
	}
}

UScriptStruct* UK2Node_GetValueAny::GetResultStructType() const
{
	UEdGraphPin* ResultPin = GetResultPin();
	if (ResultPin && 0 < ResultPin->LinkedTo.Num())
	{
		UScriptStruct* PinStructType = Cast<UScriptStruct>(ResultPin->LinkedTo[0]->PinType.PinSubCategoryObject.Get());
		for (int32 LinkIndex = 1; LinkIndex < ResultPin->LinkedTo.Num(); ++LinkIndex)
		{
			UEdGraphPin*   Link = ResultPin->LinkedTo[LinkIndex];
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

UScriptStruct* UK2Node_GetValueAny::GetResultStructTypeFromResultPin() const
{
	UEdGraphPin* ResultPin = GetResultPin(false);
	if (ResultPin)
	{
		if (ResultPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			return Cast<UScriptStruct>(ResultPin->PinType.PinSubCategoryObject.Get());
		}
	}
	return nullptr;
}

#undef LOCTEXT_NAMESPACE