// Copyright aXiuShen. All Rights Reserved.

#include "K2Node_MatureJsonToStruct.h"
#include "Engine/UserDefinedStruct.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_CallFunction.h"
#include "K2Node_IfThenElse.h"
#include "Kismet2/BlueprintEditorUtils.h"
#if MATUREJSON_VERSION>=505
#include "StructUtils/UserDefinedStruct.h"
#endif
#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "MatureJsonObject.h"
#include "MatureJsonObjectHelpers.h"

#define LOCTEXT_NAMESPACE "K2Node_MatureJsonToStruct"

namespace maturejson
{
	static FName ObjectName = *LOCTEXT("ObjectPinName", "Object").ToString();
};

UK2Node_MatureJsonToStruct::UK2Node_MatureJsonToStruct( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
}

void UK2Node_MatureJsonToStruct::AllocateDefaultPins()
{
	auto set_pint_tool_tip = [this](UEdGraphPin& Pin, const FText& Desc) {
		Pin.PinToolTip = UEdGraphSchema_K2::TypeToText(Pin.PinType).ToString();
		UEdGraphSchema_K2 const* const K2Schema = Cast<const UEdGraphSchema_K2>(GetSchema());
		if (K2Schema) {
			Pin.PinToolTip += TEXT(" ");
			Pin.PinToolTip += K2Schema->GetPinDisplayName(&Pin).ToString();
		}
		Pin.PinToolTip += FString(TEXT("\n")) + Desc.ToString();
		};
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	CreatePin( EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute );

	UScriptStruct* JsonObjectStruct = FMatureJsonObject::StaticStruct();
	UEdGraphPin* DataPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, JsonObjectStruct, maturejson::ObjectName);
	set_pint_tool_tip(*DataPin, LOCTEXT("DataPinDescription", "The JSON object to convert."));

	UEdGraphPin* SuccessPin = CreatePin( EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then );
	SuccessPin->PinFriendlyName = LOCTEXT( "MatureJsonToStruct Success pin", "Success" );

	UEdGraphPin* FailedPin = CreatePin( EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_CastFailed);
	FailedPin->PinFriendlyName = LOCTEXT( "MatureJsonToStruct Failed pin", "Failure" );

	UEdGraphPin* ResultPin = CreatePin( EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, UEdGraphSchema_K2::PN_ReturnValue );
	ResultPin->PinFriendlyName = LOCTEXT( "MatureJsonToStruct Out Struct", "Structure" );
	set_pint_tool_tip( *ResultPin, LOCTEXT( "ResultPinDescription", "The returned structure, if converted." ) );

	Super::AllocateDefaultPins();
}

UScriptStruct* UK2Node_MatureJsonToStruct::GetReturnTypeForStruct() const
{
	UScriptStruct* ReturnStructType = (UScriptStruct*)( GetResultPin()->PinType.PinSubCategoryObject.Get() );
	return ReturnStructType;
}

void UK2Node_MatureJsonToStruct::GetMenuActions( FBlueprintActionDatabaseRegistrar& ActionRegistrar ) const
{
	UClass* ActionKey = GetClass();
	if ( ActionRegistrar.IsOpenForRegistration( ActionKey ) )
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create( GetClass() );
		check( NodeSpawner != nullptr );

		ActionRegistrar.AddBlueprintAction( ActionKey, NodeSpawner );
	}
}

FText UK2Node_MatureJsonToStruct::GetMenuCategory() const
{
	return FText::FromString( TEXT( "Mature Json|Structure" ) );
}

bool UK2Node_MatureJsonToStruct::IsConnectionDisallowed( const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason ) const
{
	if ( MyPin == GetResultPin() && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard )
	{
		bool bDisallowed = true;
		if ( OtherPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct )
		{
			if ( UScriptStruct* ConnectionType = Cast<UScriptStruct>( OtherPin->PinType.PinSubCategoryObject.Get() ) )
				bDisallowed = false;
		}
		else if ( OtherPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard )
			bDisallowed = false;

		if ( bDisallowed )
			OutReason = TEXT( "Must be a structure." );

		return bDisallowed;
	}

	return false;
}

FText UK2Node_MatureJsonToStruct::GetTooltipText() const
{
	static FText Tip = LOCTEXT("NodeTooltip", "Trying to parse a JSON object into a structure.");
	return Tip;
}

FText UK2Node_MatureJsonToStruct::GetNodeTitle( ENodeTitleType::Type TitleType ) const
{
	static const FText _node_title = NSLOCTEXT("K2Node", "ToStruct_Title_None", "JSON to Structure");
	if ( TitleType == ENodeTitleType::MenuTitle )
		return _node_title;
	UEdGraphPin* ResultPin = GetResultPin();
	if ( ResultPin==nullptr )
		return _node_title;
	UScriptStruct* StructType = GetReturnTypeForStruct();
	if (!StructType || ResultPin->LinkedTo.Num() == 0)
		return _node_title;

	if (CachedNodeTitle.IsOutOfDate(this)){
		FFormatNamedArguments Args;
		Args.Add(TEXT("StructName"), FText::FromName(StructType->GetFName()));

		FText LocFormat = NSLOCTEXT("K2Node", "JsonToStruct", "JSON to {StructName}");
		CachedNodeTitle.SetCachedText(FText::Format(LocFormat, Args), this);
	}
	
	return CachedNodeTitle;
}

void UK2Node_MatureJsonToStruct::ExpandNode( FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph )
{
	Super::ExpandNode( CompilerContext, SourceGraph );
	
	const FName ToStructFunctionName = GET_FUNCTION_NAME_CHECKED(UMatureJsonObjectHelpers, ToStruct);
	UK2Node_CallFunction* CallToStructFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>( this, SourceGraph );

	CallToStructFunction->FunctionReference.SetExternalMember(ToStructFunctionName, UMatureJsonObjectHelpers::StaticClass() );
	CallToStructFunction->AllocateDefaultPins();

	CompilerContext.MovePinLinksToIntermediate( *GetExecPin(), *(CallToStructFunction->GetExecPin() ) );

	UScriptStruct* LocalStructType = GetReturnTypeForStruct();
	UUserDefinedStruct* LocalUserStructType = Cast<UUserDefinedStruct>(LocalStructType);

	UEdGraphPin* CallStructDescPin = CallToStructFunction->FindPinChecked( TEXT( "StructDesc" ) );
	if (LocalUserStructType && LocalUserStructType->PrimaryStruct.IsValid() )
		CallStructDescPin->DefaultObject = LocalUserStructType->PrimaryStruct.Get();
	else
		CallStructDescPin->DefaultObject = LocalStructType;

	UEdGraphPin* JObjectInPin = CallToStructFunction->FindPinChecked( TEXT( "JObject" ) );
	CompilerContext.MovePinLinksToIntermediate( *GetDataPin(), *JObjectInPin);

	UEdGraphPin* LocalReturnPin = FindPinChecked( UEdGraphSchema_K2::PN_ReturnValue );
	UEdGraphPin* CallStructAddrPin = CallToStructFunction->FindPinChecked(TEXT("StructAddr"));
	CallStructAddrPin->PinType = LocalReturnPin->PinType;
	CallStructAddrPin->PinType.PinSubCategoryObject = LocalReturnPin->PinType.PinSubCategoryObject;
	CompilerContext.MovePinLinksToIntermediate(*LocalReturnPin, *CallStructAddrPin);


	UEdGraphPin* CallReturnPin = CallToStructFunction->FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue);
	UEdGraphPin* CallThenPin      = CallToStructFunction->GetThenPin();
	UK2Node_IfThenElse* BranchNode = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>( this, SourceGraph );
	BranchNode->AllocateDefaultPins();

	CallThenPin->MakeLinkTo( BranchNode->GetExecPin() );
	CallReturnPin->MakeLinkTo( BranchNode->GetConditionPin() );
	
	CompilerContext.MovePinLinksToIntermediate( *GetThenPin(), *( BranchNode->GetThenPin() ) );
	CompilerContext.MovePinLinksToIntermediate( *GetFailedPin(), *( BranchNode->GetElsePin() ) );

	BreakAllNodeLinks();
}

FSlateIcon UK2Node_MatureJsonToStruct::GetIconAndTint( FLinearColor& OutColor ) const
{
	OutColor = GetNodeTitleColor();
	static FSlateIcon Icon( "EditorStyle", "Kismet.AllClasses.FunctionIcon" );
	return Icon;
}

void UK2Node_MatureJsonToStruct::PostReconstructNode()
{
	Super::PostReconstructNode();
	RefreshOutputPinType(GetResultPin());
}

void UK2Node_MatureJsonToStruct::EarlyValidation( FCompilerResultsLog& MessageLog ) const
{
	Super::EarlyValidation( MessageLog );
	if ( UEdGraphPin* ResultPin = GetResultPin() ){
		if (ResultPin->LinkedTo.Num() != 0) return;
		MessageLog.Error(*LOCTEXT("MissingPins", "Missing pins in @@").ToString(), this);
	}
}

void UK2Node_MatureJsonToStruct::NotifyPinConnectionListChanged( UEdGraphPin* Pin )
{
	Super::NotifyPinConnectionListChanged( Pin );
	if ( Pin == GetResultPin() )
		RefreshOutputPinType(Pin);
}

void UK2Node_MatureJsonToStruct::RefreshOutputPinType(UEdGraphPin* data_pin) {
	UScriptStruct* InputType = nullptr;
	if (data_pin && (data_pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)) {
		FEdGraphPinType PinType = data_pin->PinType;
		if (data_pin->LinkedTo.Num() > 0)
			PinType = data_pin->LinkedTo[0]->PinType;

		if (PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
			InputType = Cast<UScriptStruct>(PinType.PinSubCategoryObject.Get());
	}
	if (InputType == GetReturnTypeForStruct())// the same struct
		return;

	if (data_pin->SubPins.Num() > 0)
		GetSchema()->RecombinePin(data_pin);

	data_pin->PinType.PinSubCategoryObject = InputType;
	data_pin->PinType.PinCategory = InputType ?
		UEdGraphSchema_K2::PC_Struct :
		UEdGraphSchema_K2::PC_Wildcard;

	CachedNodeTitle.Clear();
}

UEdGraphPin* UK2Node_MatureJsonToStruct::GetThenPin()const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_Then);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

UEdGraphPin* UK2Node_MatureJsonToStruct::GetFailedPin() const
{
	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_CastFailed);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

UEdGraphPin* UK2Node_MatureJsonToStruct::GetResultPin() const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

UEdGraphPin* UK2Node_MatureJsonToStruct::GetDataPin() const
{
	UEdGraphPin* Pin = FindPinChecked(maturejson::ObjectName);
	check(Pin->Direction == EGPD_Input);
	return Pin;
}


//
//void UK2Node_MatureJsonToStruct::RefreshOutputPinType()
//{
//	UEdGraphPin* ResultPin = GetResultPin();
//	const bool bFillTypeFromConnected = ResultPin && (ResultPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard);
//
//	UScriptStruct* OutputType = nullptr;
//	if (bFillTypeFromConnected)
//	{
//		FEdGraphPinType PinType = ResultPin->PinType;
//		if (ResultPin->LinkedTo.Num() > 0)
//			PinType = ResultPin->LinkedTo[0]->PinType;
//
//		if (PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
//			OutputType = Cast<UScriptStruct>(PinType.PinSubCategoryObject.Get());
//	}
//
//	SetReturnTypeForStruct(OutputType);
//}
//
//void UK2Node_MatureJsonToStruct::SetReturnTypeForStruct(UScriptStruct* StructType)
//{
//	if (StructType == GetReturnTypeForStruct())
//		return;
//
//	UEdGraphPin* ResultPin = GetResultPin();
//	if (ResultPin->SubPins.Num() > 0)
//		GetSchema()->RecombinePin(ResultPin);
//
//	ResultPin->PinType.PinSubCategoryObject = StructType;
//	ResultPin->PinType.PinCategory = StructType ?
//		UEdGraphSchema_K2::PC_Struct :
//		UEdGraphSchema_K2::PC_Wildcard;
//
//	CachedNodeTitle.Clear();
//}
#undef LOCTEXT_NAMESPACE
