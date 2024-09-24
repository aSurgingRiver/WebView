// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#include "MatureJsonListHelpers.h"


void UMatureJsonListHelpers::Remove(FMatureJsonList& Value, const int index, const int num) {
	Value.Remove(index, num);
}

FMatureJsonValue UMatureJsonListHelpers::GetValue(const FMatureJsonList& Value, const int index) {
	FMatureJsonValue val;
	Value.GetValue(index, val);
	return val;
}

int UMatureJsonListHelpers::Size(const FMatureJsonList& Value) {
	return Value.Size();
}

bool UMatureJsonListHelpers::IsEmpty(const FMatureJsonList& Value) {
	return Value.IsEmpty();
}

void UMatureJsonListHelpers::Clear(FMatureJsonList& Value) {
	Value.Clear();
}

FMatureJsonList UMatureJsonListHelpers::FromBooleanArray(const TArray<bool>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromFloatArray(const TArray<float>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromIntegerArray(const TArray<int32>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromStringArray(const TArray<FString>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromDateTimeArray(const TArray<FDateTime>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromGuidArray(const TArray<FGuid>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromColorArray(const TArray<FColor>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromLinearColorArray(const TArray<FLinearColor>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromRotatorArray(const TArray<FRotator>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromTransformArray(const TArray<FTransform>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromVectorArray(const TArray<FVector>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromObjectArray(const TArray<FMatureJsonObject>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonList UMatureJsonListHelpers::FromValueArray(const TArray<FMatureJsonValue>& Value) {
	FMatureJsonList List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}

int UMatureJsonListHelpers::AddBoolean(FMatureJsonList List, const bool Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddFloat(FMatureJsonList List, const float Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddInteger(FMatureJsonList List, const int32 Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddString(FMatureJsonList List, const FString& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddDateTime(FMatureJsonList List, const FDateTime& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddGuid(FMatureJsonList List, const FGuid& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddColor(FMatureJsonList List, const FColor& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddLinearColor(FMatureJsonList List, const FLinearColor& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddRotator(FMatureJsonList List, const FRotator& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddTransform(FMatureJsonList List, const FTransform& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddVector(FMatureJsonList List, const FVector& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddObject(FMatureJsonList List, const FMatureJsonObject& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddValue(FMatureJsonList List, const FMatureJsonValue& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}
int UMatureJsonListHelpers::AddNull(FMatureJsonList List ) {
	int index = List.Size();
	List.AddValue();
	return index;
}

int UMatureJsonListHelpers::AddList(FMatureJsonList List, const FMatureJsonList& Value) {
	int index = List.Size();
	List.AddValue(Value);
	return index;
}

FMatureJsonList UMatureJsonListHelpers::MergeList(FMatureJsonList List, const FMatureJsonList& Value) {
	List.MergeList(Value);
	return List;
}

// Convert a JSON value valueto a boolean.
bool UMatureJsonListHelpers::GetBoolean(FMatureJsonList& Value, int index) {
	bool V;
	Value.GetValue(index, V);
	return V;
}
// Convert a JSON value valueto a float.
float UMatureJsonListHelpers::GetFloat(FMatureJsonList& Value, int index) {
	float V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto an integer.
int32 UMatureJsonListHelpers::GetInteger(FMatureJsonList& Value, int index) {
	int32 V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a string.
FString UMatureJsonListHelpers::GetString(FMatureJsonList& Value, int index) {
	FString V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a date/time.
FDateTime UMatureJsonListHelpers::GetDateTime(FMatureJsonList& Value, int index) {
	FDateTime V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a GUID.
FGuid UMatureJsonListHelpers::GetGuid(FMatureJsonList& Value, int index) {
	FGuid V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a color.
FColor UMatureJsonListHelpers::GetColor(FMatureJsonList& Value, int index) {
	FColor V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FLinearColor UMatureJsonListHelpers::GetLinearColor(FMatureJsonList& Value, int index) {
	FLinearColor V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FRotator UMatureJsonListHelpers::GetRotator(FMatureJsonList& Value, int index) {
	FRotator V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FVector UMatureJsonListHelpers::GetVector(FMatureJsonList& Value, int index) {
	FVector V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FTransform UMatureJsonListHelpers::GetTransform(FMatureJsonList& Value, int index) {
	FTransform V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a JSON object.
FMatureJsonObject UMatureJsonListHelpers::GetObject(FMatureJsonList& Value, int index) {
	return Value.GetValue(index).ToObject(true);
}
// Convert a JSON value valueto a JSON array.
FMatureJsonList UMatureJsonListHelpers::GetList(FMatureJsonList& Value, int index) {
	return Value.GetValue(index).ToList(true);
}

FMatureJsonList UMatureJsonListHelpers::UpdateBoolean(FMatureJsonList List, const int index, const bool Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateFloat(FMatureJsonList List, const int index, const float Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateInteger(FMatureJsonList List, const int index, const int32 Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateString(FMatureJsonList List, const int index, const FString& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateDateTime(FMatureJsonList List, const int index, const FDateTime& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateGuid(FMatureJsonList List, const int index, const FGuid& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateColor(FMatureJsonList List, const int index, const FColor& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateLinearColor(FMatureJsonList List, const int index, const FLinearColor& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateRotator(FMatureJsonList List, const int index, const FRotator& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateTransform(FMatureJsonList List, const int index, const FTransform& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateVector(FMatureJsonList List, const int index, const FVector& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateObject(FMatureJsonList List, const int index, const FMatureJsonObject& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateValue(FMatureJsonList List, const int index, const FMatureJsonValue& Value) {
	return List.SetValue(index, Value);
}
FMatureJsonList UMatureJsonListHelpers::UpdateNull(FMatureJsonList List, const int index) {
	return List.SetValue(index);
}

