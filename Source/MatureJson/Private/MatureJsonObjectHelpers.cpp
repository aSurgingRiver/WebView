// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonObjectHelpers.h"

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
	bool value;
	JObject.GetValue(Key, value);
	return value;
}
float UMatureJsonObjectHelpers::GetFloat(FMatureJsonObject& JObject, const FString& Key) {
	bool value;
	JObject.GetValue(Key, value);
	return value;
}
uint32 UMatureJsonObjectHelpers::GetUint(FMatureJsonObject& JObject, const FString& Key) {
	uint32 value;
	JObject.GetValue(Key, value);
	return value;
}
int32 UMatureJsonObjectHelpers::GetInt(FMatureJsonObject& JObject, const FString& Key) {
	int32 value;
	JObject.GetValue(Key, value);
	return value;
}
uint64 UMatureJsonObjectHelpers::GetUint64(FMatureJsonObject& JObject, const FString& Key) {
	uint64 value;
	JObject.GetValue(Key, value);
	return value;
}
int64 UMatureJsonObjectHelpers::GetInt64(FMatureJsonObject& JObject, const FString& Key) {
	int64 value;
	JObject.GetValue(Key, value);
	return value;
}
double UMatureJsonObjectHelpers::GetDouble(FMatureJsonObject& JObject, const FString& Key) {
	double value;
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
