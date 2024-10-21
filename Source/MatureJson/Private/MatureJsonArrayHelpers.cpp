// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonArrayHelpers.h"


void UMatureJsonArrayHelpers::Remove(FMatureJsonArray& Value, const int index, const int num) {
	Value.Remove(index, num);
}

FMatureJsonValue UMatureJsonArrayHelpers::GetValue(const FMatureJsonArray& Value, const int index) {
	FMatureJsonValue val;
	Value.GetValue(index, val);
	return val;
}

int UMatureJsonArrayHelpers::Size(const FMatureJsonArray& Value) {
	return Value.Size();
}

bool UMatureJsonArrayHelpers::IsEmpty(const FMatureJsonArray& Value) {
	return Value.IsEmpty();
}

bool UMatureJsonArrayHelpers::HasIndex(const FMatureJsonArray& JArray, const int index) {
	return JArray.HasIndex(index);
}

void UMatureJsonArrayHelpers::Clear(FMatureJsonArray& Value) {
	Value.Clear();
}

FMatureJsonArray UMatureJsonArrayHelpers::FromBooleanArray(const TArray<bool>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromFloatArray(const TArray<float>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromIntegerArray(const TArray<int32>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromStringArray(const TArray<FString>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromDateTimeArray(const TArray<FDateTime>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromGuidArray(const TArray<FGuid>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromColorArray(const TArray<FColor>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromLinearColorArray(const TArray<FLinearColor>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromRotatorArray(const TArray<FRotator>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromTransformArray(const TArray<FTransform>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromVectorArray(const TArray<FVector>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromObjectArray(const TArray<FMatureJsonObject>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayHelpers::FromValueArray(const TArray<FMatureJsonValue>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}

int UMatureJsonArrayHelpers::AddBoolean(FMatureJsonArray& List, const bool Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddFloat(FMatureJsonArray& List, const float Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddInteger(FMatureJsonArray& List, const int32 Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddString(FMatureJsonArray& List, const FString& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddDateTime(FMatureJsonArray& List, const FDateTime& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddGuid(FMatureJsonArray& List, const FGuid& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddColor(FMatureJsonArray& List, const FColor& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddLinearColor(FMatureJsonArray& List, const FLinearColor& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddRotator(FMatureJsonArray& List, const FRotator& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddTransform(FMatureJsonArray& List, const FTransform& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddVector(FMatureJsonArray& List, const FVector& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddObject(FMatureJsonArray& List, const FMatureJsonObject& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddValue(FMatureJsonArray& List, const FMatureJsonValue& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonArrayHelpers::AddNull(FMatureJsonArray& List ) {
	int index = List.Size();
	List.AddValue();
	return index;
}

int UMatureJsonArrayHelpers::AddArray(FMatureJsonArray& List, const FMatureJsonArray& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}

FMatureJsonArray& UMatureJsonArrayHelpers::MergeArray(FMatureJsonArray& List, const FMatureJsonArray& Value) {
	List.MergeList(Value);
	return List;
}

// Convert a JSON value valueto a boolean.
bool UMatureJsonArrayHelpers::GetBoolean(FMatureJsonArray& Value, int index) {
	bool V;
	Value.GetValue(index, V);
	return V;
}
// Convert a JSON value valueto a float.
float UMatureJsonArrayHelpers::GetFloat(FMatureJsonArray& Value, int index) {
	float V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto an integer.
int32 UMatureJsonArrayHelpers::GetInteger(FMatureJsonArray& Value, int index) {
	int32 V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a string.
FString UMatureJsonArrayHelpers::GetString(FMatureJsonArray& Value, int index) {
	FString V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a date/time.
FDateTime UMatureJsonArrayHelpers::GetDateTime(FMatureJsonArray& Value, int index) {
	FDateTime V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a GUID.
FGuid UMatureJsonArrayHelpers::GetGuid(FMatureJsonArray& Value, int index) {
	FGuid V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a color.
FColor UMatureJsonArrayHelpers::GetColor(FMatureJsonArray& Value, int index) {
	FColor V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FLinearColor UMatureJsonArrayHelpers::GetLinearColor(FMatureJsonArray& Value, int index) {
	FLinearColor V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FRotator UMatureJsonArrayHelpers::GetRotator(FMatureJsonArray& Value, int index) {
	FRotator V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FVector UMatureJsonArrayHelpers::GetVector(FMatureJsonArray& Value, int index) {
	FVector V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FTransform UMatureJsonArrayHelpers::GetTransform(FMatureJsonArray& Value, int index) {
	FTransform V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a JSON object.
FMatureJsonObject UMatureJsonArrayHelpers::GetObject(FMatureJsonArray& Value, int index) {
	return Value.GetValue(index).ToObject(true);
}
// Convert a JSON value valueto a JSON array.
FMatureJsonArray UMatureJsonArrayHelpers::GetArray(FMatureJsonArray& Value, int index) {
	return Value.GetValue(index).ToArray(true);
}

FMatureJsonArray& UMatureJsonArrayHelpers::SetBoolean(FMatureJsonArray& List, const int index, const bool Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetFloat(FMatureJsonArray& List, const int index, const float Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetInteger(FMatureJsonArray& List, const int index, const int32 Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetString(FMatureJsonArray& List, const int index, const FString& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetDateTime(FMatureJsonArray& List, const int index, const FDateTime& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetGuid(FMatureJsonArray& List, const int index, const FGuid& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetColor(FMatureJsonArray& List, const int index, const FColor& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetLinearColor(FMatureJsonArray& List, const int index, const FLinearColor& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetRotator(FMatureJsonArray& List, const int index, const FRotator& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetTransform(FMatureJsonArray& List, const int index, const FTransform& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetVector(FMatureJsonArray& List, const int index, const FVector& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetObject(FMatureJsonArray& List, const int index, const FMatureJsonObject& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetValue(FMatureJsonArray& List, const int index, const FMatureJsonValue& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonArray& UMatureJsonArrayHelpers::SetNull(FMatureJsonArray& List, const int index) {
	List.SetValue(index);
	return List;
}

FMatureJsonValue UMatureJsonArrayHelpers::NewValue(FMatureJsonArray& JArray, const int index) {
	return JArray.SetValue(index);
}
FMatureJsonObject UMatureJsonArrayHelpers::NewObject(FMatureJsonArray& JArray, const int index) {
	return JArray.SetObject(index);
}
FMatureJsonArray UMatureJsonArrayHelpers::NewArray(FMatureJsonArray& JArray, const int index) {
	return JArray.SetArray(index);
}


FMatureJsonArrayIterator UMatureJsonArrayIteratorHelpers::Begin(FMatureJsonArray& JObject) {
	return FMatureJsonArrayIterator(JObject);
}

FMatureJsonArrayIterator UMatureJsonArrayIteratorHelpers::End(FMatureJsonArray& JObject) {
	return FMatureJsonArrayIterator(JObject).End();
}

void UMatureJsonArrayIteratorHelpers::Next(FMatureJsonArrayIterator& Iterator, int step) {
	Iterator.Next(step);
}

bool UMatureJsonArrayIteratorHelpers::IsValid(FMatureJsonArrayIterator& Iterator) {
	return Iterator.IsValid();
}

int UMatureJsonArrayIteratorHelpers::Index(FMatureJsonArrayIterator& Iterator) {
	return Iterator.Index();
}

FMatureJsonValue UMatureJsonArrayIteratorHelpers::Value(FMatureJsonArrayIterator& Iterator) {
	return Iterator.Value();
}
