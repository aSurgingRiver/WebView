// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "UObject/ObjectMacros.h"
#include "Textures/SlateIcon.h"
#include "K2Node.h"
#include "K2Node_MatureJsonFromStruct.generated.h"

class FBlueprintActionDatabaseRegistrar;
class UEdGraph;

UCLASS()
class MATUREJSONK2NODE_API UK2Node_MatureJsonFromStruct : public UK2Node
{
	GENERATED_UCLASS_BODY()

	//~ Begin UEdGraphNode Interface._
	virtual void AllocateDefaultPins() override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle( ENodeTitleType::Type TitleType ) const override;
	// 扩展新节点，然后删除自身节点
	virtual void ExpandNode( class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph ) override;
	virtual FSlateIcon GetIconAndTint( FLinearColor& OutColor ) const override;
	virtual void PostReconstructNode() override;
	//~ End UEdGraphNode Interface._

	//~ Begin UK2Node Interface_
	virtual bool IsNodeSafeToIgnore() const override { return true; }
	virtual FText GetMenuCategory() const override;
	// create menu for blueprint
	virtual void GetMenuActions( FBlueprintActionDatabaseRegistrar& ActionRegistrar ) const override;
	virtual bool IsConnectionDisallowed( const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason ) const override;
	// 检查引脚是否连接
	virtual void EarlyValidation( class FCompilerResultsLog& MessageLog ) const override;
	virtual void NotifyPinConnectionListChanged( UEdGraphPin* Pin ) override;
	//~ End UK2Node Interface_


private:
	void RefreshInputPin(UEdGraphPin* data_pin);
	UScriptStruct* GetPropertyTypeForStruct() const;

	UEdGraphPin* GetThenPin() const;
	UEdGraphPin* GetDataPin() const;
	UEdGraphPin* GetResultPin() const;

	FNodeTextCache CachedNodeTitle;
};