// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "K2Node.h"

#include "K2Node_GetValueAny.generated.h"


class FBlueprintActionDatabaseRegistrar;
class UEdGraph;

UCLASS()
class UK2Node_GetValueAny : public UK2Node
{
	GENERATED_BODY()

public:
	UK2Node_GetValueAny(const FObjectInitializer& ObjectInitializer);

	//~ Begin UEdGraphNode Interface.
	virtual void  AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	//virtual FText GetTooltipText() const override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void PostReconstructNode() override;
	//~ End UEdGraphNode Interface.

	//~ Begin UK2Node Interface
	virtual void  ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual void  GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual bool  IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;
	virtual void  EarlyValidation(class FCompilerResultsLog& MessageLog) const override;
	virtual void  NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	//~ End UK2Node Interface


private:
	UEdGraphPin* GetThenPin() const;
	UEdGraphPin* GetFailedPin() const;
	UEdGraphPin* GetInputValuePin() const;
	UEdGraphPin* GetResultPin(bool bChecked = true) const;


	void           RefreshOutputPinType();
	void           SetReturnTypeForStruct(UScriptStruct* NewRowStruct);
	UScriptStruct* GetResultStructType() const;
	UScriptStruct* GetResultStructTypeFromResultPin() const;

private:
	FNodeTextCache CachedNodeTitle;
};