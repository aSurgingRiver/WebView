// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#include "MatureJsonObjectHelpers.h"

FMatureJsonValue UMatureJsonObjectHelpers::AddKey(FMatureJsonObject Object, const FString& key) {
	return Object.AddValue(key);
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
FMatureJsonObject UMatureJsonObjectHelpers::FromMapBool(const TMap<FString, bool>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of floats to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapFloat(const TMap<FString, float>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of integers to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapInt(const TMap<FString, int32>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of numbers to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapDouble(const TMap<FString, double>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of strings to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapString(const TMap<FString, FString>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of date/times to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapDateTime(const TMap<FString, FDateTime>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of GUIDs to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapGuid(const TMap<FString, FGuid>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of colors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapColor(const TMap<FString, FColor>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of linear colors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapLinearColor(const TMap<FString, FLinearColor>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of rotators to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapRotator(const TMap<FString, FRotator>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of transforms to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapTransform(const TMap<FString, FTransform>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of vectors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapVector(const TMap<FString, FVector>& Map) {
	return FMatureJsonObject().AddValue(Map);
}
// Add a map of vectors to this object.
FMatureJsonObject UMatureJsonObjectHelpers::FromMapValue(const TMap<FString, FMatureJsonValue>& Map) {
	return FMatureJsonObject().AddValue(Map);
}

// Add a JSON object to this object.
FMatureJsonObject UMatureJsonObjectHelpers::MergeObject(FMatureJsonObject JObject, const FMatureJsonObject& inValue) {
	return JObject.AddValue(inValue);
}
// 
FMatureJsonObject UMatureJsonObjectHelpers::AddMapValue(FMatureJsonObject JObject, const TMap<FString, FMatureJsonValue>& Map) {
	return JObject.AddValue(Map);
}
// Set a property as a boolean.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyBool(FMatureJsonObject JObject, const FString& Key, bool Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a float.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyFloat(FMatureJsonObject JObject, const FString& Key, float Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as an integer.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyInt(FMatureJsonObject JObject, const FString& Key, int32 Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a number.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyDouble(FMatureJsonObject JObject, const FString& Key, double Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a string.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyString(FMatureJsonObject JObject, const FString& Key, const FString& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a date/time.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyDateTime(FMatureJsonObject JObject, const FString& Key, const FDateTime& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a GUID.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyGuid(FMatureJsonObject JObject, const FString& Key, const FGuid& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a color.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyColor(FMatureJsonObject JObject, const FString& Key, const FColor& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a linear color.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyLinearColor(FMatureJsonObject JObject, const FString& Key, const FLinearColor& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a rotator.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyRotator(FMatureJsonObject JObject, const FString& Key, const FRotator& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a transform.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyTransform(FMatureJsonObject JObject, const FString& Key, const FTransform& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a vector.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyVector(FMatureJsonObject JObject, const FString& Key, const FVector& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a JSON value.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyValue(FMatureJsonObject JObject, const FString& Key, const FMatureJsonValue& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a JSON object.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyObject(FMatureJsonObject JObject, const FString& Key, const FMatureJsonObject& Value) {
	return JObject.AddValue(Key, Value);
}
// Set a property as a JSON array.
FMatureJsonObject UMatureJsonObjectHelpers::AddKeyList(FMatureJsonObject JObject, const FString& Key, const FMatureJsonList& Value) {
	return JObject.AddValue(Key, Value);
}

FLinearColor UMatureJsonObjectHelpers::GetLinearColor(FMatureJsonObject& JObject) {
	FLinearColor value;
	JObject.GetValue(value);
	return value;
}
FRotator UMatureJsonObjectHelpers::GetRotator(FMatureJsonObject& JObject) {
	FRotator value;
	JObject.GetValue(value);
	return value;
}
FTransform UMatureJsonObjectHelpers::GetTransform(FMatureJsonObject& JObject) {
	FTransform value;
	JObject.GetValue(value);
	return value;
}
FVector UMatureJsonObjectHelpers::GetVector(FMatureJsonObject& JObject) {
	FVector value;
	JObject.GetValue(value);
	return value;
}
bool UMatureJsonObjectHelpers::GetKeyBool(FMatureJsonObject& JObject, const FString& Key) {
	bool value;
	JObject.GetValue(Key, value);
	return value;
}
float UMatureJsonObjectHelpers::GetKeyFloat(FMatureJsonObject& JObject, const FString& Key) {
	bool value;
	JObject.GetValue(Key, value);
	return value;
}
uint32 UMatureJsonObjectHelpers::GetKeyUint(FMatureJsonObject& JObject, const FString& Key) {
	uint32 value;
	JObject.GetValue(Key, value);
	return value;
}
int32 UMatureJsonObjectHelpers::GetKeyInt(FMatureJsonObject& JObject, const FString& Key) {
	int32 value;
	JObject.GetValue(Key, value);
	return value;
}
uint64 UMatureJsonObjectHelpers::GetKeyUint64(FMatureJsonObject& JObject, const FString& Key) {
	uint64 value;
	JObject.GetValue(Key, value);
	return value;
}
int64 UMatureJsonObjectHelpers::GetKeyInt64(FMatureJsonObject& JObject, const FString& Key) {
	int64 value;
	JObject.GetValue(Key, value);
	return value;
}
double UMatureJsonObjectHelpers::GetKeyDouble(FMatureJsonObject& JObject, const FString& Key) {
	double value;
	JObject.GetValue(Key, value);
	return value;
}
FString UMatureJsonObjectHelpers::GetKeyString(FMatureJsonObject& JObject, const FString& Key) {
	FString value;
	JObject.GetValue(Key, value);
	return value;
}
FGuid UMatureJsonObjectHelpers::GetKeyGuid(FMatureJsonObject& JObject, const FString& Key) {
	FGuid value;
	JObject.GetValue(Key, value);
	return value;
}
FColor UMatureJsonObjectHelpers::GetKeyColor(FMatureJsonObject& JObject, const FString& Key) {
	FColor value;
	JObject.GetValue(Key, value);
	return value;
}
FDateTime UMatureJsonObjectHelpers::GetKeyDateTime(FMatureJsonObject& JObject, const FString& Key) {
	FDateTime value;
	JObject.GetValue(Key, value);
	return value;
}
FLinearColor UMatureJsonObjectHelpers::GetKeyLinearColor(FMatureJsonObject& JObject, const FString& Key) {
	FLinearColor value;
	JObject.GetValue(Key, value);
	return value;
}
FRotator UMatureJsonObjectHelpers::GetKeyRotator(FMatureJsonObject& JObject, const FString& Key) {
	FRotator value;
	JObject.GetValue(Key, value);
	return value;
}
FTransform UMatureJsonObjectHelpers::GetKeyTransform(FMatureJsonObject& JObject, const FString& Key) {
	FTransform value;
	JObject.GetValue(Key, value);
	return value;
}
FVector UMatureJsonObjectHelpers::GetKeyVector(FMatureJsonObject& JObject, const FString& Key) {
	FVector value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonValue UMatureJsonObjectHelpers::GetKeyValue(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonValue value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonObject UMatureJsonObjectHelpers::GetKeyObject(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonObject value;
	JObject.GetValue(Key, value);
	return value;
}
FMatureJsonList UMatureJsonObjectHelpers::GetKeyList(FMatureJsonObject& JObject, const FString& Key) {
	FMatureJsonList value;
	JObject.GetValue(Key, value);
	return value;
}

FMatureJsonObjectIterator UMatureJsonObjectIteratorHelpers::Begin(FMatureJsonObject& JObject) {
	return FMatureJsonObjectIterator( JObject);
}

FMatureJsonObjectIterator UMatureJsonObjectIteratorHelpers::End(FMatureJsonObject& JObject) {
	return FMatureJsonObjectIterator(JObject).End();
}

void UMatureJsonObjectIteratorHelpers::Next(FMatureJsonObjectIterator Iterator, int step) {
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
