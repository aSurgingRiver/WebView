// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonObjectPureHelpers.h"
#include "Engine/UserDefinedStruct.h"
#include "UObject/TextProperty.h"
#include "MatureJsonLog.h"



int32 UMatureJsonObjectPureHelpers::Size(FMatureJsonObject& Object)  {
	return Object.Size();
}
bool  UMatureJsonObjectPureHelpers::IsEmpty(FMatureJsonObject& Object) {
	return Object.IsEmpty();
}

bool  UMatureJsonObjectPureHelpers::HasKey(FMatureJsonObject& Object, const FString& Key)  {
	return Object.HasKey(Key);
}

TArray<FString> UMatureJsonObjectPureHelpers::GetKeys(FMatureJsonObject& Object)  {
	return Object.GetKeys();
}

FMatureJsonObject UMatureJsonObjectPureHelpers::Parse(const FString& Text) {
	FMatureJsonValue JValue;
	JValue.ParseString(Text);
	return JValue.ToObject();
}

FString UMatureJsonObjectPureHelpers::ToString(const FMatureJsonObject& Object) {
	return FMatureJsonValue().SetValue(Object).ToString();
}

FMatureJsonValue UMatureJsonObjectPureHelpers::ToValue(const FMatureJsonObject& Object) {
	return FMatureJsonValue().SetValue(Object);
}

// Add a map of booleans to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromBooleanMap(const TMap<FString, bool>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of floats to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromFloatMap(const TMap<FString, float>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of integers to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromIntegerMap(const TMap<FString, int32>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of numbers to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromDoubleMap(const TMap<FString, double>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of strings to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromStringMap(const TMap<FString, FString>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of date/times to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromDateTimeMap(const TMap<FString, FDateTime>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of GUIDs to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromGuidMap(const TMap<FString, FGuid>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of colors to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromColorMap(const TMap<FString, FColor>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of linear colors to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromLinearColorMap(const TMap<FString, FLinearColor>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of rotators to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromRotatorMap(const TMap<FString, FRotator>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of transforms to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromTransformMap(const TMap<FString, FTransform>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of vectors to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromVectorMap(const TMap<FString, FVector>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of vectors to this object.
FMatureJsonObject UMatureJsonObjectPureHelpers::FromValueMap(const TMap<FString, FMatureJsonValue>& Map) {
	return FMatureJsonObject().AddValue(Map);
}

FLinearColor UMatureJsonObjectPureHelpers::ToLinearColor(FMatureJsonObject& JObject) {
	FLinearColor value;
	JObject.GetValue(value);
	return value;
}
FRotator UMatureJsonObjectPureHelpers::ToRotator(FMatureJsonObject& JObject) {
	FRotator value;
	JObject.GetValue(value);
	return value;
}
FTransform UMatureJsonObjectPureHelpers::ToTransform(FMatureJsonObject& JObject) {
	FTransform value;
	JObject.GetValue(value);
	return value;
}
FVector UMatureJsonObjectPureHelpers::ToVector(FMatureJsonObject& JObject) {
	FVector value;
	JObject.GetValue(value);
	return value;
}

bool UMatureJsonObjectPureHelpers::GetBoolean(FMatureJsonObject& JObject, const FString& Key) {
	bool value=false;
	JObject.GetValue(Key, value);
	return value;
}
float UMatureJsonObjectPureHelpers::GetFloat(FMatureJsonObject& JObject, const FString& Key) {
	float value=0.0f;
	JObject.GetValue(Key, value);
	return value;
}
uint32 UMatureJsonObjectPureHelpers::GetUint(FMatureJsonObject& JObject, const FString& Key) {
	uint32 value=0;
	JObject.GetValue(Key, value);
	return value;
}
int32 UMatureJsonObjectPureHelpers::GetInt(FMatureJsonObject& JObject, const FString& Key) {
	int32 value=0;
	JObject.GetValue(Key, value);
	return value;
}
uint64 UMatureJsonObjectPureHelpers::GetUint64(FMatureJsonObject& JObject, const FString& Key) {
	uint64 value=0;
	JObject.GetValue(Key, value);
	return value;
}
int64 UMatureJsonObjectPureHelpers::GetInt64(FMatureJsonObject& JObject, const FString& Key) {
	int64 value = 0;
	JObject.GetValue(Key, value);
	return value;
}
double UMatureJsonObjectPureHelpers::GetDouble(FMatureJsonObject& JObject, const FString& Key) {
	double value=0.0f;
	JObject.GetValue(Key, value);
	return value;
}
FString UMatureJsonObjectPureHelpers::GetString(FMatureJsonObject& JObject, const FString& Key) {
	FString value;
	JObject.GetValue(Key, value);
	return value;
}
FGuid UMatureJsonObjectPureHelpers::GetGuid(FMatureJsonObject& JObject, const FString& Key) {
	FGuid value;
	JObject.GetValue(Key, value);
	return value;
}
FColor UMatureJsonObjectPureHelpers::GetColor(FMatureJsonObject& JObject, const FString& Key) {
	FColor value;
	JObject.GetValue(Key, value);
	return value;
}
FDateTime UMatureJsonObjectPureHelpers::GetDateTime(FMatureJsonObject& JObject, const FString& Key) {
	FDateTime value;
	JObject.GetValue(Key, value);
	return value;
}
FLinearColor UMatureJsonObjectPureHelpers::GetLinearColor(FMatureJsonObject& JObject, const FString& Key) {
	FLinearColor value;
	JObject.GetValue(Key, value);
	return value;
}
FRotator UMatureJsonObjectPureHelpers::GetRotator(FMatureJsonObject& JObject, const FString& Key) {
	FRotator value;
	JObject.GetValue(Key, value);
	return value;
}
FTransform UMatureJsonObjectPureHelpers::GetTransform(FMatureJsonObject& JObject, const FString& Key) {
	FTransform value;
	JObject.GetValue(Key, value);
	return value;
}
FVector UMatureJsonObjectPureHelpers::GetVector(FMatureJsonObject& JObject, const FString& Key) {
	FVector value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonValue UMatureJsonObjectPureHelpers::GetValue(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonValue value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonObject UMatureJsonObjectPureHelpers::GetObject(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonObject value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonArray UMatureJsonObjectPureHelpers::GetArray(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonArray value;
	JObject.GetValue(Key, value);
	return value;
}

FMatureJsonValue UMatureJsonObjectPureHelpers::NewValue(FMatureJsonObject& JObject, const FString& Key) {
	return JObject.SetValue(Key);
}
FMatureJsonObject UMatureJsonObjectPureHelpers::NewObject(FMatureJsonObject& JObject, const FString& Key) {
	return JObject.SetObject(Key);
}
FMatureJsonArray UMatureJsonObjectPureHelpers::NewArray(FMatureJsonObject& JObject, const FString& Key) {
	return JObject.SetArray(Key);
}
