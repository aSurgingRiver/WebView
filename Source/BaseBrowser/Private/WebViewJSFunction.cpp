// Copyright aXiuShen. All Rights Reserved.

#include "WebViewJSFunction.h"
#include "WebViewJSScripting.h"



FWebViewJSParam::~FWebViewJSParam()
{
	// Since the FString, StructWrapper, TArray, and TMap members are in a union, they may or may not be valid, so we have to call the destructors manually.
	switch (Tag)
	{
		case PTYPE_STRING:
			delete StringValue;
			break;
		case PTYPE_STRUCT:
			delete StructValue;
			break;
		case PTYPE_ARRAY:
			delete ArrayValue;
			break;
		case PTYPE_MAP:
			delete MapValue;
			break;
		default:
			break;
	}
}


FWebViewJSParam::IStructWrapper::~IStructWrapper() {}

FWebViewJSParam::FWebViewJSParam(const FWebViewJSParam& Other)
	: Tag(Other.Tag)
{
	switch (Other.Tag)
	{
		case PTYPE_BOOL:
			BoolValue = Other.BoolValue;
			break;
		case PTYPE_DOUBLE:
			DoubleValue = Other.DoubleValue;
			break;
		case PTYPE_INT:
			IntValue = Other.IntValue;
			break;
		case PTYPE_STRING:
			StringValue = new FString(*Other.StringValue);
			break;
		case PTYPE_NULL:
			break;
		case PTYPE_OBJECT:
			ObjectValue = Other.ObjectValue;
			break;
		case PTYPE_STRUCT:
			StructValue = Other.StructValue->Clone();
			break;
		case PTYPE_ARRAY:
			ArrayValue = new TArray<FWebViewJSParam>(*Other.ArrayValue);
			break;
		case PTYPE_MAP:
			MapValue = new TMap<FString, FWebViewJSParam>(*Other.MapValue);
			break;
	}
}

FWebViewJSParam::FWebViewJSParam(FWebViewJSParam&& Other)
	: Tag(Other.Tag)
{
	switch (Other.Tag)
	{
	case PTYPE_BOOL:
		BoolValue = Other.BoolValue;
		break;
	case PTYPE_DOUBLE:
		DoubleValue = Other.DoubleValue;
		break;
	case PTYPE_INT:
		IntValue = Other.IntValue;
		break;
	case PTYPE_STRING:
		StringValue = Other.StringValue;
		Other.StringValue = nullptr;
		break;
	case PTYPE_NULL:
		break;
	case PTYPE_OBJECT:
		ObjectValue = Other.ObjectValue;
		Other.ObjectValue = nullptr;
		break;
	case PTYPE_STRUCT:
		StructValue = Other.StructValue;
		Other.StructValue = nullptr;
		break;
	case PTYPE_ARRAY:
		ArrayValue = Other.ArrayValue;
		Other.ArrayValue = nullptr;
		break;
	case PTYPE_MAP:
		MapValue = Other.MapValue;
		Other.MapValue = nullptr;
		break;
	}

	Other.Tag = PTYPE_NULL;
}


FWebViewJSParam::FWebViewJSParam() : Tag(PTYPE_NULL) {}
FWebViewJSParam::FWebViewJSParam(bool Value) : Tag(PTYPE_BOOL), BoolValue(Value) {}
FWebViewJSParam::FWebViewJSParam(int8 Value) : Tag(PTYPE_INT), IntValue(Value) {}
FWebViewJSParam::FWebViewJSParam(int16 Value) : Tag(PTYPE_INT), IntValue(Value) {}
FWebViewJSParam::FWebViewJSParam(int32 Value) : Tag(PTYPE_INT), IntValue(Value) {}
FWebViewJSParam::FWebViewJSParam(uint8 Value) : Tag(PTYPE_INT), IntValue(Value) {}
FWebViewJSParam::FWebViewJSParam(uint16 Value) : Tag(PTYPE_INT), IntValue(Value) {}
FWebViewJSParam::FWebViewJSParam(uint32 Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value) {}
FWebViewJSParam::FWebViewJSParam(int64 Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value) {}
FWebViewJSParam::FWebViewJSParam(uint64 Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value) {}
FWebViewJSParam::FWebViewJSParam(double Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value) {}
FWebViewJSParam::FWebViewJSParam(float Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value) {}
FWebViewJSParam::FWebViewJSParam(const FString& Value) : Tag(PTYPE_STRING), StringValue(new FString(Value)) {}
FWebViewJSParam::FWebViewJSParam(const FText& Value) : Tag(PTYPE_STRING), StringValue(new FString(Value.ToString())) {}
FWebViewJSParam::FWebViewJSParam(const FName& Value) : Tag(PTYPE_STRING), StringValue(new FString(Value.ToString())) {}
FWebViewJSParam::FWebViewJSParam(const TCHAR* Value) : Tag(PTYPE_STRING), StringValue(new FString(Value)) {}
FWebViewJSParam::FWebViewJSParam(UObject* Value) : Tag(PTYPE_OBJECT), ObjectValue(Value) {}


FWebViewJSCallbackBase::FWebViewJSCallbackBase()
{}

bool FWebViewJSCallbackBase::IsValid() const
{
	return ScriptingPtr.IsValid();
}

FWebViewJSCallbackBase::FWebViewJSCallbackBase(TSharedPtr<FWebViewJSScripting> InScripting, const FGuid& InCallbackId)
	: ScriptingPtr(InScripting)
	, CallbackId(InCallbackId)
{}

void FWebViewJSCallbackBase::Invoke(int32 ArgCount, FWebViewJSParam Arguments[], bool bIsError) const
{
//#ifdef WEBVIEW_CEF
	TSharedPtr<FWebViewJSScripting> Scripting = ScriptingPtr.Pin();
	if (Scripting.IsValid())
	{
		Scripting->InvokeJSFunction(CallbackId, ArgCount, Arguments, bIsError);
	}
//#endif
}


FWebViewJSFunction::FWebViewJSFunction()
	: FWebViewJSCallbackBase()
{}

FWebViewJSFunction::FWebViewJSFunction(TSharedPtr<FWebViewJSScripting> InScripting, const FGuid& InFunctionId)
	: FWebViewJSCallbackBase(InScripting, InFunctionId)
{}


FWebViewJSResponse::FWebViewJSResponse()
	: FWebViewJSCallbackBase()
{}

FWebViewJSResponse::FWebViewJSResponse(TSharedPtr<FWebViewJSScripting> InScripting, const FGuid& InCallbackId)
	: FWebViewJSCallbackBase(InScripting, InCallbackId)
{}

/**
 * Indicate successful completion without a return value.
 * The remote Promise's then() handler will be executed without arguments.
 */
void FWebViewJSResponse::Success() const
{
	Invoke(0, nullptr, false);
}


