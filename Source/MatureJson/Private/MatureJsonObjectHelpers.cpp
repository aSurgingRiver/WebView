// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonObjectHelpers.h"
#include "Engine/UserDefinedStruct.h"
#include "UObject/TextProperty.h"
#include "MatureJsonLog.h"




namespace maturejson
{
	static FName _DATA_TIME_NAME = TEXT("DateTime");
	static FName _GUID_NAME = TEXT("Guid");
#if MATUREJSON_VERSION<=500
#define ImportText_Direct(Buffer, PropertyPtr, OwnerObject, PortFlags) ImportText(Buffer, PropertyPtr, PortFlags, OwnerObject)
#define	ExportTextItem_Direct(ValueStr,PropertyValue,DefaultValue,Parent,PortFlags)  ExportTextItem(ValueStr,PropertyValue,DefaultValue,Parent,PortFlags)
#endif

	//bool ToProperty(const FMatureJsonValue& Value, FProperty* Property, void* OutValue, UObject* Owner) {
	//	if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property)) {
	//		return EnumToProperty(Value, EnumProperty, Property, Owner);
	//	}
	//	else if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property)) {
	//		return NumericToProperty(Value, NumericProperty, Property);
	//	}
	//	else if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
	//	{
	//		// AsBool will log an error for completely inappropriate types (then give us a default)
	//		BoolProperty->SetPropertyValue(OutValue, Value.ToBoolean());
	//		return true;
	//	}
	//	else if (FStrProperty* StringProperty = CastField<FStrProperty>(Property)) {
	//		StringProperty->SetPropertyValue(OutValue, Value.ToString());
	//		return true;
	//	}
	//	else if (FTextProperty* TextProperty = CastField<FTextProperty>(Property)) {
	//		TextProperty->SetPropertyValue(OutValue, FText::FromString(Value.ToString()));
	//		return true;
	//	}
	//	return false;
	//}
	
	// Begin json object convert to struct 
	bool ConvertProperty(const FMatureJsonValue& JsonValue, FProperty* Property, void* OutValue, UObject* Owner, int64 CheckFlags = 0);
	bool ConvertToStruct(const FMatureJsonObject& JObject, const UStruct* StructDef, void* OutStruct, UObject* Container, int64 CheckFlags = 0);
	bool EnumToProperty(const FMatureJsonValue& Json, FEnumProperty* Property,  void* ValuePtr, UObject* Owner) {
		if (Json.GetType() != EMatureJsonType::String) {
			// Property->GetUnderlyingProperty()->SetIntPropertyValue(OutValue, (int64)Json.ToInt64());
			UE_LOG(MatureJsonLog, Error, TEXT("NumericToProperty - Unable to set numeric property type %s for property %s , input json value is not String"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
			return false;
		}
		FString EnumValue = Json.ToString();
		Property->ImportText_Direct(*EnumValue, ValuePtr, Owner, PPF_None);
		return true;
	}
	bool NumericToProperty(const FMatureJsonValue& Json, FNumericProperty* Property,  void* ValuePtr) {
		if (Json.GetType() != EMatureJsonType::Number) {
			UE_LOG(MatureJsonLog, Error, TEXT("NumericToProperty - Unable to set numeric property type %s for property %s , input json value is not Number"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
			return false;
		}

		if (Property->IsFloatingPoint()) {
			Property->SetFloatingPointPropertyValue(ValuePtr, Json.ToNumber());
			return true;
		}
		if (Property->IsInteger()) {
			Property->SetIntPropertyValue(ValuePtr, Json.ToInt64());
			return true;
		}
		UE_LOG(MatureJsonLog, Error, TEXT("NumericToProperty - Unable to set numeric property type %s for property %s"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
		return false;
	}
	bool ToNativeArray(const FMatureJsonArray& Array, FProperty* Property, void* ValuePtr, UObject* Owner, int64 CheckFlags = 0) {
		int ItemsToRead = FMath::Clamp(Array.Size(), 0, Property->ArrayDim);
#if MATUREJSON_VERSION<=504
		auto ElementSize = Property->ElementSize;
#else
		auto ElementSize = Property->GetElementSize();
#endif
		for (int Index = 0; Index != ItemsToRead; ++Index){
			if (!ConvertProperty(Array.GetValue(Index), Property, (char*)ValuePtr + Index * ElementSize, Owner, CheckFlags))
			{
				return false;
			}
		}
		return true;
	}
	bool ToArray(const FMatureJsonArray& Array, FArrayProperty* Property, void* ValuePtr,UObject* Owner, int64 CheckFlags = 0) {
		int32 ArrLen = Array.Size();
		// make the output array size match
		FScriptArrayHelper Helper(Property, ValuePtr);
		Helper.Resize(ArrLen);
		// set the property values
		for (int32 i = 0; i < ArrLen; ++i){
			auto ArrayValueItem = Array.GetValue(i);
			if (ArrayValueItem.GetType() == EMatureJsonType::Null)continue;
			if (!ConvertProperty(ArrayValueItem, Property->Inner, Helper.GetRawPtr(i), Owner, CheckFlags & (~CPF_ParmFlags)))
			{
				UE_LOG(MatureJsonLog, Error, TEXT("ToTArray - Unable to deserialize array element [%d] for property %s"), i, *Property->GetNameCPP());
				return false;
			}
		}
		return true;
	}
	bool ToSet(const FMatureJsonArray& Array, FSetProperty* Property, void* ValuePtr, UObject* Owner, int64 CheckFlags = 0) {
		auto ArrayValue = Array;
		int32 ArrLen = ArrayValue.Size();
		FScriptSetHelper Helper(Property, ValuePtr);
		// set the property values
		for (int32 i = 0; i < ArrLen; ++i){
			auto ArrayValueItem = ArrayValue.GetValue(i);
			if (ArrayValueItem.GetType() == EMatureJsonType::Null)continue;
			int32 NewIndex = Helper.AddDefaultValue_Invalid_NeedsRehash();
			if (!ConvertProperty(ArrayValueItem, Property->ElementProp, Helper.GetElementPtr(NewIndex), Owner, CheckFlags & (~CPF_ParmFlags)))
			{
				UE_LOG(MatureJsonLog, Error, TEXT("ToTSet - Unable to deserialize set element [%d] for property %s"), i, *Property->GetNameCPP());
				return false;
			}
		}
		Helper.Rehash();
		return true;
	}
	bool ToMap(const FMatureJsonObject& ObjectValue, FMapProperty* MapProperty, void* ValuePtr, UObject* Owner, int64 CheckFlags = 0) {
		FScriptMapHelper Helper(MapProperty, ValuePtr);
		int32 MapSize = ObjectValue.Size();
		Helper.EmptyValues(MapSize);
		FMatureJsonObjectIterator it(ObjectValue);
		for (; it.IsValid(); it++){
			int32 NewIndex = Helper.AddDefaultValue_Invalid_NeedsRehash();
			FMatureJsonValue TempKeyValue;
			TempKeyValue.SetValue(it.Key());
			const bool bKeySuccess = ConvertProperty(TempKeyValue, MapProperty->KeyProp, Helper.GetKeyPtr(NewIndex), Owner, CheckFlags & (~CPF_ParmFlags));
			const bool bValueSuccess = ConvertProperty(it.Value(), MapProperty->ValueProp, Helper.GetValuePtr(NewIndex), Owner, CheckFlags & (~CPF_ParmFlags));
			if (bKeySuccess && bValueSuccess)continue;
			UE_LOG(MatureJsonLog, Error, TEXT("ToMap - Unable to deserialize map element [key: %s] for property %s"), *it.Key(), *MapProperty->GetNameCPP());
			return false;
		}
		Helper.Rehash();
		return true;
	}
	bool ToObject(const FMatureJsonObject& ObjectValue, FObjectProperty* ObjectProperty, void* ValuePtr, UObject* Owner, int64 CheckFlags = 0) {
		UClass* PropertyClass = ObjectProperty->PropertyClass;
#if MATUREJSON_VERSION<=501
		if (!Owner)Owner = GetTransientPackage();
#else
		if (!Owner)Owner = GetTransientOuterForRename(PropertyClass);
#endif
		UObject* createdObj = StaticAllocateObject(PropertyClass, Owner, NAME_None, EObjectFlags::RF_NoFlags, EInternalObjectFlags::None, false);
#if MATUREJSON_VERSION<500
		(*PropertyClass->ClassConstructor)(FObjectInitializer(createdObj, PropertyClass->ClassDefaultObject, false, false));
#elif MATUREJSON_VERSION<=505
		EObjectInitializerOptions options = EObjectInitializerOptions::InitializeProperties;
		(*PropertyClass->ClassConstructor)(FObjectInitializer(createdObj, PropertyClass->ClassDefaultObject, options));
#else 
		EObjectInitializerOptions options = EObjectInitializerOptions::InitializeProperties;
		(*PropertyClass->ClassConstructor)(FObjectInitializer(createdObj, PropertyClass->GetDefaultObject(), options));
#endif
		ObjectProperty->SetObjectPropertyValue(ValuePtr, createdObj);
		return ConvertToStruct(ObjectValue, ObjectProperty->PropertyClass, createdObj, createdObj, CheckFlags);
	}
	bool ToStruct(const FMatureJsonValue& JsonValue, FStructProperty* StructProperty, void* ValuePtr, UObject* Owner, int64 CheckFlags=0) {
		auto SubStruct = StructProperty->Struct; //
		auto FNameStruct = SubStruct->GetFName();
		if (FNameStruct == _DATA_TIME_NAME){
			if (JsonValue.GetType() == EMatureJsonType::String) {
				FString DateString = JsonValue.ToString();
				FDateTime& DateTimeOut = *(FDateTime*)ValuePtr;
				if (false == FDateTime::ParseIso8601(*DateString, DateTimeOut)
					&& false == FDateTime::Parse(DateString, DateTimeOut)) {
					UE_LOG(MatureJsonLog, Error, TEXT("ToStruct - Unable to import FDateTime for property %s"), *StructProperty->GetNameCPP());
					return false;
				}
				return true;
			}
		}
		else if (FNameStruct == _GUID_NAME) {
			if (JsonValue.GetType() == EMatureJsonType::String) {
				FGuid& GUID = *(FGuid*)ValuePtr;
				if (!JsonValue.GetValue(GUID)) {
					UE_LOG(MatureJsonLog, Error, TEXT("ToStruct - Unable to import FDateTime for property %s"), *StructProperty->GetNameCPP());
					return false;
				}
				return true;
			}
		}
		if (JsonValue.GetType() != EMatureJsonType::Object) {
			UE_LOG(MatureJsonLog, Error, TEXT("ToStruct - Attempted to import UStruct from non-object JSON key for property %s"), *StructProperty->GetNameCPP());
			return false;
		}
		auto JObject = JsonValue.ToObject();
		return ConvertToStruct(JObject, SubStruct, ValuePtr, Owner, CheckFlags);
		//if (SubStruct->GetCppStructOps() && SubStruct->GetCppStructOps()->HasImportTextItem())
		//{
		//	UScriptStruct::ICppStructOps* TheCppStructOps = SubStruct->GetCppStructOps();
		//	FString ImportTextString = JsonValue.ToString();
		//	const TCHAR* ImportTextPtr = *ImportTextString;
		//	if (!TheCppStructOps->ImportTextItem(ImportTextPtr, ValuePtr, PPF_None, nullptr, (FOutputDevice*)GWarn)) {
		//		// Fall back to trying the tagged property approach if custom ImportTextItem couldn't get it done
		//		StructProperty->ImportText_Direct(ImportTextPtr, ValuePtr, nullptr, PPF_None);
		//	}
		//	return true;
		//}
		//StructProperty->ImportText_Direct(*JsonValue.ToString(), ValuePtr, nullptr, PPF_None);
		//return true;
	}
	bool ConvertProperty(const FMatureJsonValue& JsonValue, FProperty* Property, void* ValuePtr, UObject* Owner, int64 CheckFlags)
	{
		switch(JsonValue.GetType())
		{
		case EMatureJsonType::Null:
			return true;
		// for array
		case EMatureJsonType::Array: {
			if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property)) {
				return ToArray(JsonValue.ToArray(), ArrayProperty, ValuePtr, Owner, CheckFlags);
			}
			if (FSetProperty* SetProperty = CastField<FSetProperty>(Property)) {
				return ToSet(JsonValue.ToArray(), SetProperty, ValuePtr, Owner, CheckFlags);
			}
			return ToNativeArray(JsonValue.ToArray(), Property, ValuePtr, Owner, CheckFlags);
		}
		// for map
		case EMatureJsonType::Object: {
			if (FMapProperty* MapProperty = CastField<FMapProperty>(Property)) {
				return ToMap(JsonValue.ToObject(), MapProperty, ValuePtr, Owner, CheckFlags);
			}
			if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property)) {
				return ToObject(JsonValue.ToObject(), ObjectProperty, ValuePtr, Owner, CheckFlags);
			}
			if (FStructProperty* StructProperty = CastField<FStructProperty>(Property)) {
				return ConvertToStruct(JsonValue.ToObject(), StructProperty->Struct, ValuePtr, Owner, CheckFlags & (~CPF_ParmFlags));
			}
			return true;
			//UE_LOG(MatureJsonLog, Error, TEXT("ConvertProperty - Attempted to import unkown from object JSON key"));
		}
		// for number int float double string
		default: {
			if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property)) {
				return EnumToProperty(JsonValue, EnumProperty, ValuePtr, Owner);
			}
			else if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property)) {
				return NumericToProperty(JsonValue, NumericProperty, ValuePtr);
			}
			else if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property)){
				// AsBool will log an error for completely inappropriate types (then give us a default)
				BoolProperty->SetPropertyValue(ValuePtr, JsonValue.ToBoolean());
				return true;
			}
			else if (FStrProperty* StringProperty = CastField<FStrProperty>(Property)) {
				StringProperty->SetPropertyValue(ValuePtr, JsonValue.ToString());
				return true;
			}
#if MATUREJSON_VERSION>=426
			else if (FTextProperty* TextProperty = CastField<FTextProperty>(Property)) {
				TextProperty->SetPropertyValue(ValuePtr, FText::FromString(JsonValue.ToString()));
				return true;
			}
#endif
			else if (FStructProperty* StructProperty = CastField<FStructProperty>(Property)) {
				return ToStruct(JsonValue, StructProperty, ValuePtr, Owner, CheckFlags);
			}
			return false;
		}
		}
	}
	bool ConvertToStruct(const FMatureJsonObject& JObject, const UStruct* StructDef, void* ValuePtr, UObject* Container, int64 CheckFlags)
	{
		int32 ObjectSize = JObject.Size();
		if (ObjectSize <= 0){
			return true;
		}
		for (TFieldIterator<FProperty> It(StructDef); It; ++It){
			FProperty* Property = *It;
			FString FieldName = Property->GetName();
			// find a json value matching this property name
			if (!JObject.HasKey(FieldName))continue;
			auto JValue = JObject.GetKey(FieldName);
			if (JValue.GetType() == EMatureJsonType::Null)continue;
			void* Value = Property->ContainerPtrToValuePtr<uint8>(ValuePtr);
			if (!ConvertProperty(JValue, Property, Value, Container, CheckFlags)){
				UE_LOG(MatureJsonLog, Error, TEXT("ToStruct - Unable to parse %s.%s from JSON.key %s"), *StructDef->GetName(), *Property->GetName(),*FieldName);
				return false;
			}
			if (--ObjectSize <= 0)break;
		}

		return true;
	}
	// End json object convert to struct 

	// Begin struct convert to json object 
	bool ConvertFromScriptStruct(const UScriptStruct* StructDef, const void* OutStruct, FMatureJsonValue& JsonValue);
	bool ConvertFromStruct(const UStruct* StructDef, const void* OutStruct, FMatureJsonObject& JObject);
	bool ConvertFromProperty(FProperty* Property, const void* ValuePtr, FMatureJsonValue& JsonValue);

	bool FromArray(FArrayProperty* Property, const void* ValuePtr, FMatureJsonArray& JsonValue) {
		TArray< TSharedPtr<FJsonValue> > Out;
		FScriptArrayHelper Helper(Property, ValuePtr);
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			FMatureJsonValue JValue = JsonValue.AddValue();
			ConvertFromProperty(Property->Inner, Helper.GetRawPtr(i), JValue);
		}
		return true;
	}
	bool FromSet(FSetProperty* Property, const void* ValuePtr, FMatureJsonArray& JsonValue) {
		TArray< TSharedPtr<FJsonValue> > Out;
		FScriptSetHelper Helper(Property, ValuePtr);
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			FMatureJsonValue JValue = JsonValue.AddValue();
			ConvertFromProperty(Property->ElementProp, Helper.GetElementPtr(i), JValue);
		}
		return true;
	}
	bool FromMap(FMapProperty* Property, const void* ValuePtr, FMatureJsonObject& JsonValue) {
		FScriptMapHelper Helper(Property, ValuePtr);
		for (int32 i = 0; i < Helper.Num(); ++i) {
			if (Helper.IsValidIndex(i)){
				FMatureJsonValue KValue;
				ConvertFromProperty(Property->KeyProp, Helper.GetKeyPtr(i), KValue);
				FString KeyStr = KValue.ToString();
				if (KeyStr.IsEmpty())continue;
				FMatureJsonValue VValue = JsonValue.GetKey(KeyStr);
				ConvertFromProperty(Property->ValueProp, Helper.GetValuePtr(i), VValue);
			}
		}
		return true;
	}


	bool ConvertFromProperty(FProperty* Property, const void* ValuePtr, FMatureJsonValue& JsonValue) {
		if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property)){
			// export enums as strings
			UEnum* EnumDef = EnumProperty->GetEnum();
			FString StringValue = EnumDef->GetNameStringByValue(EnumProperty->GetUnderlyingProperty()->GetSignedIntPropertyValue(ValuePtr));
			JsonValue.SetValue(StringValue);
			return true;
		}
		if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property)){
			// We want to export numbers as numbers
			if (NumericProperty->IsFloatingPoint()){
				JsonValue.SetValue(NumericProperty->GetFloatingPointPropertyValue(ValuePtr));
				return true;
			}
			if (NumericProperty->IsInteger()){
				JsonValue.SetValue(NumericProperty->GetSignedIntPropertyValue(ValuePtr));
				return true;
			}
			return true;
		}
		if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property)){ // Export bools as bools
			JsonValue.SetValue(BoolProperty->GetPropertyValue(ValuePtr));
			return true;
		}
		if (FStrProperty* StringProperty = CastField<FStrProperty>(Property)){
			JsonValue.SetValue(StringProperty->GetPropertyValue(ValuePtr));
			return true;
		}
#if MATUREJSON_VERSION>=426
		if (FTextProperty* TextProperty = CastField<FTextProperty>(Property)){
			JsonValue.SetValue(TextProperty->GetPropertyValue(ValuePtr).ToString());
			return true;
		}
#endif
		if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property)){
			auto JArray = JsonValue.ToArray();
			return FromArray(ArrayProperty, ValuePtr, JArray);
		}
		if (FSetProperty* SetProperty = CastField<FSetProperty>(Property)){
			auto JArray = JsonValue.ToArray();
			return FromSet(SetProperty, ValuePtr, JArray);
		}
		if (FMapProperty* MapProperty = CastField<FMapProperty>(Property)){
			auto JObject = JsonValue.ToObject();
			return FromMap(MapProperty, ValuePtr, JObject);
		}
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property)){
			return ConvertFromScriptStruct(StructProperty->Struct, ValuePtr, JsonValue);
		}
		FString StringValue;
		Property->ExportTextItem_Direct(StringValue, ValuePtr, NULL, NULL, PPF_None);
		JsonValue.SetValue(StringValue);
		return true;
	}
	bool ConvertFromScriptStruct(const UScriptStruct* StructDef, const void* ValuePtr, FMatureJsonValue& JsonValue) {
		auto FNameStruct = StructDef->GetFName();
		if (FNameStruct == _DATA_TIME_NAME) {
			const FDateTime& inDT = *(FDateTime*)ValuePtr;
			JsonValue.SetValue(inDT);
			return true;
		}
		if (FNameStruct == _GUID_NAME) {
			const FGuid& inDT = *(FGuid*)ValuePtr;
			JsonValue.SetValue(inDT);
			return true;
		}
		auto JObject = JsonValue.ToObject();
		return ConvertFromStruct(StructDef, ValuePtr, JObject);
	}
	bool ConvertFromStruct(const UStruct* StructDef, const void* StructPtr, FMatureJsonObject& JObject) {
		if (!StructDef || !StructPtr)
			return true;
		for (TFieldIterator<FProperty> It(StructDef); It; ++It){
			FProperty* Property = *It;
			if (Property->HasAnyPropertyFlags(CPF_Deprecated | CPF_Transient))continue;
			FString VariableName = Property->GetName();
			if (!(Property->PropertyFlags & CPF_NativeAccessSpecifiers)) {// for blueprint struction
				TArray<FString> S;
				VariableName.ParseIntoArray(S, TEXT("_"),false);
				const int Num = S.Num();
				if (3 <= Num && FCString::IsNumeric(*S[Num - 2]) && S[Num - 1].Len() == 32) {
					VariableName = S[0];
					for (int loop = 1; loop < Num - 2; loop++) {
						VariableName.Append(TEXT("_"));
						VariableName.Append(S[loop]);
					}
				}
			}
			const void* Value = Property->ContainerPtrToValuePtr<uint8>(StructPtr);
			auto ValueOut = JObject.AddKey(VariableName);
			if (Property->ArrayDim == 1) {
				ConvertFromProperty(Property, Value, ValueOut);
				continue;
			}
			auto ValueArray = ValueOut.ToArray();
#if MATUREJSON_VERSION<=504
			auto ElementSize = Property->ElementSize;
#else
			auto ElementSize = Property->GetElementSize();
#endif
			for (int Index = 0; Index != Property->ArrayDim; ++Index){
				auto LoopValue = ValueArray.AddValue();
				ConvertFromProperty(Property, (char*)Value + Index * ElementSize, LoopValue);
			}
		}
		return true;
	}
	// End struct convert to json object 
}



FMatureStruct::FMatureStruct()
{
}

FMatureStruct::~FMatureStruct()
{
}

bool UMatureJsonObjectHelpers::ToStruct(const UScriptStruct* StructDesc, const FMatureJsonObject& JObject, FMatureStruct& StructAddr) {
	return false;
}

bool UMatureJsonObjectHelpers::Generic_ToStruct(const UScriptStruct* StructType, const FMatureJsonObject& JObject, void* OutStructPtr) {

	UObject* Outer =nullptr;
	if (StructType->IsChildOf(UObject::StaticClass())){
		Outer = (UObject*)OutStructPtr;
	}
	maturejson::ConvertToStruct(JObject, StructType, OutStructPtr, Outer);
	return true;
}

DEFINE_FUNCTION(UMatureJsonObjectHelpers::execToStruct) {
	P_GET_OBJECT(UScriptStruct, StructType);
	P_GET_STRUCT(FMatureJsonObject, Object);
	Stack.StepCompiledIn<FStructProperty>(NULL);
	void* OutStructPtr = Stack.MostRecentPropertyAddress;
	P_FINISH;
	bool bSuccess = false;
	P_NATIVE_BEGIN;
	bSuccess = Generic_ToStruct(StructType, Object, OutStructPtr);
	P_NATIVE_END;
	*(bool*)RESULT_PARAM = bSuccess;
}

FMatureJsonObject UMatureJsonObjectHelpers::ToJson(const UScriptStruct* StructDesc, const FMatureStruct& StructAddr) {
	return FMatureJsonObject();
}

bool UMatureJsonObjectHelpers::Generic_ToJson(const UScriptStruct* StructType, const void* OutStructPtr, FMatureJsonObject& JObject) {
	return maturejson::ConvertFromStruct(StructType, OutStructPtr, JObject);
}

DEFINE_FUNCTION(UMatureJsonObjectHelpers::execToJson) {

	P_GET_OBJECT(UScriptStruct, StructType);
	Stack.StepCompiledIn<FStructProperty>(NULL);
	void* StructPtr = Stack.MostRecentPropertyAddress;
	P_FINISH;
	bool bSuccess = false;
	FMatureJsonObject OutObject ;
	P_NATIVE_BEGIN;
	bSuccess = Generic_ToJson(StructType, StructPtr, OutObject);
	P_NATIVE_END;
	*(FMatureJsonObject*)RESULT_PARAM = bSuccess ? OutObject : FMatureJsonObject();
}

FMatureJsonValue UMatureJsonObjectHelpers::AddKey(FMatureJsonObject Object, const FString& key) {
	return Object.SetValue(key);
}
FMatureJsonValue UMatureJsonObjectHelpers::GetKey(FMatureJsonObject& Object, const FString& key)  {
	return Object.GetKey(key);
}
int32 UMatureJsonObjectHelpers::Size(FMatureJsonObject& Object)  {
	return Object.Size();
}
bool  UMatureJsonObjectHelpers::IsEmpty(FMatureJsonObject& Object) {
	return Object.IsEmpty();
}
void  UMatureJsonObjectHelpers::Clear(FMatureJsonObject Object) {
	Object.Clear();
}
bool  UMatureJsonObjectHelpers::HasKey(FMatureJsonObject& Object, const FString& Key)  {
	return Object.HasKey(Key);
}
void  UMatureJsonObjectHelpers::RemoveKey(FMatureJsonObject Object, const FString& Key) {
	Object.RemoveKey(Key);
}

TArray<FString> UMatureJsonObjectHelpers::GetKeys(FMatureJsonObject& Object)  {
	return Object.GetKeys();
}

FMatureJsonObject UMatureJsonObjectHelpers::Parse(const FString& Text) {
	FMatureJsonValue JValue;
	JValue.ParseString(Text);
	return JValue.ToObject();
}

FString UMatureJsonObjectHelpers::ToString(const FMatureJsonObject& Object) {
	return FMatureJsonValue().SetValue(Object).ToString();
}

FMatureJsonValue UMatureJsonObjectHelpers::ToValue(const FMatureJsonObject& Object) {
	return FMatureJsonValue().SetValue(Object);
}

// Add a map of booleans to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromBooleanMap(const TMap<FString, bool>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of floats to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromFloatMap(const TMap<FString, float>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of integers to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromIntegerMap(const TMap<FString, int32>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of numbers to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromDoubleMap(const TMap<FString, double>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of strings to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromStringMap(const TMap<FString, FString>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of date/times to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromDateTimeMap(const TMap<FString, FDateTime>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of GUIDs to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromGuidMap(const TMap<FString, FGuid>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of colors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromColorMap(const TMap<FString, FColor>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of linear colors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromLinearColorMap(const TMap<FString, FLinearColor>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of rotators to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromRotatorMap(const TMap<FString, FRotator>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of transforms to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromTransformMap(const TMap<FString, FTransform>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of vectors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromVectorMap(const TMap<FString, FVector>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of vectors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromValueMap(const TMap<FString, FMatureJsonValue>& Map) {
	return FMatureJsonObject().AddValue(Map);
}

// Add a JSON object to this object.
FMatureJsonObject& UMatureJsonObjectHelpers::MergeObject(FMatureJsonObject& JObject, const FMatureJsonObject& inValue) {
	return JObject.AddValue(inValue);
}
// 
FMatureJsonObject UMatureJsonObjectHelpers::AddMapValue(FMatureJsonObject JObject, const TMap<FString, FMatureJsonValue>& Map) {
	return JObject.AddValue(Map);
}
// Set a property as a boolean.
FMatureJsonObject& UMatureJsonObjectHelpers::SetBoolean(FMatureJsonObject& JObject, const FString& Key, bool Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a float.
FMatureJsonObject& UMatureJsonObjectHelpers::SetFloat(FMatureJsonObject& JObject, const FString& Key, float Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as an integer.
FMatureJsonObject& UMatureJsonObjectHelpers::SetInteger(FMatureJsonObject& JObject, const FString& Key, int32 Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a number.
FMatureJsonObject& UMatureJsonObjectHelpers::SetDouble(FMatureJsonObject& JObject, const FString& Key, double Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a string.
FMatureJsonObject& UMatureJsonObjectHelpers::SetString(FMatureJsonObject& JObject, const FString& Key, const FString& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a date/time.
FMatureJsonObject& UMatureJsonObjectHelpers::SetDateTime(FMatureJsonObject& JObject, const FString& Key, const FDateTime& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a GUID.
FMatureJsonObject& UMatureJsonObjectHelpers::SetGuid(FMatureJsonObject& JObject, const FString& Key, const FGuid& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a color.
FMatureJsonObject& UMatureJsonObjectHelpers::SetColor(FMatureJsonObject& JObject, const FString& Key, const FColor& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a linear color.
FMatureJsonObject& UMatureJsonObjectHelpers::SetLinearColor(FMatureJsonObject& JObject, const FString& Key, const FLinearColor& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a rotator.
FMatureJsonObject& UMatureJsonObjectHelpers::SetRotator(FMatureJsonObject& JObject, const FString& Key, const FRotator& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a transform.
FMatureJsonObject& UMatureJsonObjectHelpers::SetTransform(FMatureJsonObject& JObject, const FString& Key, const FTransform& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a vector.
FMatureJsonObject& UMatureJsonObjectHelpers::SetVector(FMatureJsonObject& JObject, const FString& Key, const FVector& Value) {
	return JObject.SetValue(Key, Value);
}

// Set a property as a JSON value.
FMatureJsonObject& UMatureJsonObjectHelpers::SetValue(FMatureJsonObject& JObject, const FString& Key, const FMatureJsonValue& Value) {
	return JObject.SetValue(Key, Value);
}

// Set a property as a JSON object.
FMatureJsonObject& UMatureJsonObjectHelpers::SetObject(FMatureJsonObject& JObject, const FString& Key, const FMatureJsonObject& Value) {
	return JObject.SetValue(Key, Value);
}
// Set a property as a JSON array.
FMatureJsonObject& UMatureJsonObjectHelpers::SetArray(FMatureJsonObject& JObject, const FString& Key, const FMatureJsonArray& Value) {
	return JObject.SetValue(Key, Value);
}

FMatureJsonObject& UMatureJsonObjectHelpers::SetNull(FMatureJsonObject& JObject, const FString& Key) {
	JObject.SetValue(Key);
	return JObject;
}

FLinearColor UMatureJsonObjectHelpers::ToLinearColor(FMatureJsonObject& JObject) {
	FLinearColor value;
	JObject.GetValue(value);
	return value;
}
FRotator UMatureJsonObjectHelpers::ToRotator(FMatureJsonObject& JObject) {
	FRotator value;
	JObject.GetValue(value);
	return value;
}
FTransform UMatureJsonObjectHelpers::ToTransform(FMatureJsonObject& JObject) {
	FTransform value;
	JObject.GetValue(value);
	return value;
}
FVector UMatureJsonObjectHelpers::ToVector(FMatureJsonObject& JObject) {
	FVector value;
	JObject.GetValue(value);
	return value;
}

bool UMatureJsonObjectHelpers::GetBoolean(FMatureJsonObject& JObject, const FString& Key) {
	bool value=false;
	JObject.GetValue(Key, value);
	return value;
}
float UMatureJsonObjectHelpers::GetFloat(FMatureJsonObject& JObject, const FString& Key) {
	float value=0.0f;
	JObject.GetValue(Key, value);
	return value;
}
uint32 UMatureJsonObjectHelpers::GetUint(FMatureJsonObject& JObject, const FString& Key) {
	uint32 value=0;
	JObject.GetValue(Key, value);
	return value;
}
int32 UMatureJsonObjectHelpers::GetInt(FMatureJsonObject& JObject, const FString& Key) {
	int32 value=0;
	JObject.GetValue(Key, value);
	return value;
}
uint64 UMatureJsonObjectHelpers::GetUint64(FMatureJsonObject& JObject, const FString& Key) {
	uint64 value=0;
	JObject.GetValue(Key, value);
	return value;
}
int64 UMatureJsonObjectHelpers::GetInt64(FMatureJsonObject& JObject, const FString& Key) {
	int64 value = 0;
	JObject.GetValue(Key, value);
	return value;
}
double UMatureJsonObjectHelpers::GetDouble(FMatureJsonObject& JObject, const FString& Key) {
	double value=0.0f;
	JObject.GetValue(Key, value);
	return value;
}
FString UMatureJsonObjectHelpers::GetString(FMatureJsonObject& JObject, const FString& Key) {
	FString value;
	JObject.GetValue(Key, value);
	return value;
}
FGuid UMatureJsonObjectHelpers::GetGuid(FMatureJsonObject& JObject, const FString& Key) {
	FGuid value;
	JObject.GetValue(Key, value);
	return value;
}
FColor UMatureJsonObjectHelpers::GetColor(FMatureJsonObject& JObject, const FString& Key) {
	FColor value;
	JObject.GetValue(Key, value);
	return value;
}
FDateTime UMatureJsonObjectHelpers::GetDateTime(FMatureJsonObject& JObject, const FString& Key) {
	FDateTime value;
	JObject.GetValue(Key, value);
	return value;
}
FLinearColor UMatureJsonObjectHelpers::GetLinearColor(FMatureJsonObject& JObject, const FString& Key) {
	FLinearColor value;
	JObject.GetValue(Key, value);
	return value;
}
FRotator UMatureJsonObjectHelpers::GetRotator(FMatureJsonObject& JObject, const FString& Key) {
	FRotator value;
	JObject.GetValue(Key, value);
	return value;
}
FTransform UMatureJsonObjectHelpers::GetTransform(FMatureJsonObject& JObject, const FString& Key) {
	FTransform value;
	JObject.GetValue(Key, value);
	return value;
}
FVector UMatureJsonObjectHelpers::GetVector(FMatureJsonObject& JObject, const FString& Key) {
	FVector value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonValue UMatureJsonObjectHelpers::GetValue(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonValue value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonObject UMatureJsonObjectHelpers::GetObject(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonObject value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonArray UMatureJsonObjectHelpers::GetArray(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonArray value;
	JObject.GetValue(Key, value);
	return value;
}

FMatureJsonValue UMatureJsonObjectHelpers::NewValue(FMatureJsonObject& JObject, const FString& Key) {
	return JObject.SetValue(Key);
}
FMatureJsonObject UMatureJsonObjectHelpers::NewObject(FMatureJsonObject& JObject, const FString& Key) {
	return JObject.SetObject(Key);
}
FMatureJsonArray UMatureJsonObjectHelpers::NewArray(FMatureJsonObject& JObject, const FString& Key) {
	return JObject.SetArray(Key);
}

FMatureJsonObjectIterator UMatureJsonObjectIteratorHelpers::Begin(FMatureJsonObject& JObject) {
	return FMatureJsonObjectIterator( JObject);
}

FMatureJsonObjectIterator UMatureJsonObjectIteratorHelpers::End(FMatureJsonObject& JObject) {
	return FMatureJsonObjectIterator(JObject).End();
}

void UMatureJsonObjectIteratorHelpers::Next(FMatureJsonObjectIterator& Iterator, int step) {
	Iterator.Next(step);
}

bool UMatureJsonObjectIteratorHelpers::IsValid(FMatureJsonObjectIterator& Iterator) {
	return Iterator.IsValid();
}

FString UMatureJsonObjectIteratorHelpers::Key(FMatureJsonObjectIterator& Iterator) {
	return Iterator.Key();
}

FMatureJsonValue UMatureJsonObjectIteratorHelpers::Value(FMatureJsonObjectIterator& Iterator) {
	return Iterator.Value();
}
