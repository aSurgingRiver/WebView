// Copyright aXiuShen. All Rights Reserved.
#include "K2Node_MatureJsonFromStruct.h"
#include "Engine/UserDefinedStruct.h"
#if MATUREJSON_VERSION>=505
#include "StructUtils/UserDefinedStruct.h"
#endif
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_CallFunction.h"
#include "K2Node_IfThenElse.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "MatureJsonObject.h"
#include "MatureJsonObjectHelpers.h"

#define LOCTEXT_NAMESPACE "K2Node_MatureJsonFromStruct"

namespace maturejson 
{
	static FName StructName = *LOCTEXT("StructName", "Structure").ToString();
};

UK2Node_MatureJsonFromStruct::UK2Node_MatureJsonFromStruct( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
}

void UK2Node_MatureJsonFromStruct::AllocateDefaultPins()
{
	auto set_pin_tool_tip = [&,this](UEdGraphPin& Pin, const FString& Desc) {
		Pin.PinToolTip = UEdGraphSchema_K2::TypeToText(Pin.PinType).ToString();
		UEdGraphSchema_K2 const* const GrapSchema = Cast<const UEdGraphSchema_K2>(GetSchema());
		if (GrapSchema){
			Pin.PinToolTip += TEXT(" ");
			Pin.PinToolTip += GrapSchema->GetPinDisplayName(&Pin).ToString();
		}
		Pin.PinToolTip += FString(TEXT("\n")) + Desc;
		};
	const UEdGraphSchema_K2* GrapSchema = GetDefault<UEdGraphSchema_K2>();
	CreatePin( EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute );

	UEdGraphPin* Data = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, maturejson::StructName);
	Data->bDisplayAsMutableRef = true;
	Data->PinFriendlyName = LOCTEXT("In Struct", "Struct");
	set_pin_tool_tip(*Data, TEXT("The structure to convert."));

	UEdGraphPin* Success = CreatePin( EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_CastSucceeded);
	Success->PinFriendlyName = LOCTEXT( "Success Exec pin", "Success" );

	UScriptStruct* JsonObject = FMatureJsonObject::StaticStruct();// TBaseStructure<FMatureJsonObject>::Get();
	UEdGraphPin* Result = CreatePin( EGPD_Output, UEdGraphSchema_K2::PC_Struct, JsonObject, UEdGraphSchema_K2::PN_ReturnValue );
	Result->PinFriendlyName = LOCTEXT( "Out Json", "JObject" );
	set_pin_tool_tip( *Result, TEXT("The returned JSON object, if converted."));

	Super::AllocateDefaultPins();
}

UScriptStruct* UK2Node_MatureJsonFromStruct::GetPropertyTypeForStruct() const
{
	UScriptStruct* DataStructType = (UScriptStruct*)( GetDataPin()->PinType.PinSubCategoryObject.Get() );
	return DataStructType;
}

FText UK2Node_MatureJsonFromStruct::GetMenuCategory() const
{
	return FText::FromString(TEXT("Mature Json|Structure"));
}

void UK2Node_MatureJsonFromStruct::GetMenuActions( FBlueprintActionDatabaseRegistrar& ActionRegistrar ) const
{
	UClass* ActionKey = GetClass();
	if (!ActionRegistrar.IsOpenForRegistration(ActionKey))return;
	UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(ActionKey);
	check(NodeSpawner != nullptr);
	ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
}

bool UK2Node_MatureJsonFromStruct::IsConnectionDisallowed( const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason ) const
{
	if (MyPin != GetDataPin() || MyPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
		return false;

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

FText UK2Node_MatureJsonFromStruct::GetTooltipText() const
{
	return LOCTEXT("GetTooltipText", "Trying to convert the structure into a JsonObject.");
}


UEdGraphPin* UK2Node_MatureJsonFromStruct::GetDataPin() const
{
	UEdGraphPin* Pin = FindPinChecked(maturejson::StructName);
	check(Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_MatureJsonFromStruct::GetThenPin()const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = FindPinChecked( UEdGraphSchema_K2::PN_CastSucceeded);
	check( Pin->Direction == EGPD_Output );
	return Pin;
}

UEdGraphPin* UK2Node_MatureJsonFromStruct::GetResultPin() const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = FindPinChecked( UEdGraphSchema_K2::PN_ReturnValue );
	check( Pin->Direction == EGPD_Output );
	return Pin;
}

FText UK2Node_MatureJsonFromStruct::GetNodeTitle( ENodeTitleType::Type TitleType ) const
{
	FText default_title = LOCTEXT("GetNodeTitle_Default", "Structure to JSON");
	if (TitleType == ENodeTitleType::MenuTitle)
		return default_title;
	
	UEdGraphPin* DataPin = GetDataPin();
	if (nullptr == DataPin) {
		return default_title;
	}
	UScriptStruct* StructType = GetPropertyTypeForStruct();
	if (!StructType || DataPin->LinkedTo.Num() == 0)
		return default_title;

	if (CachedNodeTitle.IsOutOfDate(this))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("StructName"), FText::FromName(StructType->GetFName()));

		FText LocFormat = LOCTEXT("GetNodeTitle_OutOfDate", "{StructName} to JSON");
		CachedNodeTitle.SetCachedText(FText::Format(LocFormat, Args), this);
	}
	return CachedNodeTitle;
}

void UK2Node_MatureJsonFromStruct::ExpandNode( FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph )
{
	Super::ExpandNode( CompilerContext, SourceGraph );
	
	const FName StructToJsonFunctionName = GET_FUNCTION_NAME_CHECKED(UMatureJsonObjectHelpers, ToJson);
	UK2Node_CallFunction* CallStructToJsonFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>( this, SourceGraph );

	CallStructToJsonFunction->FunctionReference.SetExternalMember( StructToJsonFunctionName, UMatureJsonObjectHelpers::StaticClass() );
	CallStructToJsonFunction->AllocateDefaultPins();

	CompilerContext.MovePinLinksToIntermediate( *GetExecPin(), *( CallStructToJsonFunction->GetExecPin() ) );
	
	UScriptStruct* StructType = GetPropertyTypeForStruct();
	UUserDefinedStruct* UserStructType = Cast<UUserDefinedStruct>( StructType );
	
	UEdGraphPin* StructDescPin = CallStructToJsonFunction->FindPinChecked( TEXT( "StructDesc" ) );
	if (UserStructType && UserStructType->PrimaryStruct.IsValid() )
		StructDescPin->DefaultObject = UserStructType->PrimaryStruct.Get();
	else
		StructDescPin->DefaultObject = StructType;

	UEdGraphPin* DataPinFrom = GetDataPin();
	UEdGraphPin* StructAddrPin = CallStructToJsonFunction->FindPinChecked( TEXT( "StructAddr" ) );

	StructAddrPin->PinType                      = DataPinFrom->PinType;
	StructAddrPin->PinType.PinSubCategoryObject = DataPinFrom->PinType.PinSubCategoryObject;

	CompilerContext.MovePinLinksToIntermediate( *DataPinFrom, *StructAddrPin );

	UEdGraphPin* OriginalReturnPin = FindPinChecked( UEdGraphSchema_K2::PN_ReturnValue );
	UEdGraphPin* FunctionReturnPin = CallStructToJsonFunction->FindPinChecked( UEdGraphSchema_K2::PN_ReturnValue );
	UEdGraphPin* FunctionThenPin   = CallStructToJsonFunction->GetThenPin();

	CompilerContext.MovePinLinksToIntermediate( *GetThenPin(), *(FunctionThenPin) );
	CompilerContext.MovePinLinksToIntermediate( *OriginalReturnPin, *FunctionReturnPin);

	BreakAllNodeLinks();
}

FSlateIcon UK2Node_MatureJsonFromStruct::GetIconAndTint( FLinearColor& OutColor ) const
{
	OutColor = GetNodeTitleColor();
	static FSlateIcon Icon( "EditorStyle", "Kismet.AllClasses.FunctionIcon" );
	return Icon;
}

void UK2Node_MatureJsonFromStruct::EarlyValidation( FCompilerResultsLog& MessageLog ) const
{
	Super::EarlyValidation( MessageLog );
	if ( UEdGraphPin* DataPin = GetDataPin() ){
		if ( DataPin->LinkedTo.Num() == 0 ){
			MessageLog.Error( *LOCTEXT( "MissingPins", "Missing pins in @@" ).ToString(), this );
			return;
		}
	}
}

void UK2Node_MatureJsonFromStruct::PostReconstructNode()
{
	Super::PostReconstructNode();
	RefreshInputPin(GetDataPin());
}

void UK2Node_MatureJsonFromStruct::NotifyPinConnectionListChanged( UEdGraphPin* Pin )
{
	Super::NotifyPinConnectionListChanged( Pin );
	UEdGraphPin* DataPin = GetDataPin();
	if (Pin != DataPin)return;
	RefreshInputPin(DataPin);
}

void UK2Node_MatureJsonFromStruct::RefreshInputPin(UEdGraphPin* data_pin) {
	UScriptStruct* InputType = nullptr;
	if (data_pin && (data_pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)) {
		FEdGraphPinType PinType = data_pin->PinType;
		if (data_pin->LinkedTo.Num() > 0)
			PinType = data_pin->LinkedTo[0]->PinType;

		if (PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
			InputType = Cast<UScriptStruct>(PinType.PinSubCategoryObject.Get());
	}
	if (InputType == GetPropertyTypeForStruct())// the same struct
		return;

	if (data_pin->SubPins.Num() > 0)
		GetSchema()->RecombinePin(data_pin);

	data_pin->PinType.PinSubCategoryObject = InputType;
	data_pin->PinType.PinCategory = InputType ?
		UEdGraphSchema_K2::PC_Struct :
		UEdGraphSchema_K2::PC_Wildcard;

	CachedNodeTitle.Clear();
}

#undef LOCTEXT_NAMESPACE

