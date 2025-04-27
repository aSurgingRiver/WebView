// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonArrayPureHelpers.h"


FMatureJsonValue UMatureJsonArrayPureHelpers::GetValue(const FMatureJsonArray& Value, const int index) {
	FMatureJsonValue val;
	Value.GetValue(index, val);
	return val;
}

int UMatureJsonArrayPureHelpers::Size(const FMatureJsonArray& Value) {
	return Value.Size();
}

bool UMatureJsonArrayPureHelpers::IsEmpty(const FMatureJsonArray& Value) {
	return Value.IsEmpty();
}

bool UMatureJsonArrayPureHelpers::HasIndex(const FMatureJsonArray& JArray, const int index) {
	return JArray.HasIndex(index);
}

FMatureJsonArray UMatureJsonArrayPureHelpers::Parse(const FString& Text) {
	FMatureJsonValue JValue;
	JValue.ParseString(Text);
	return JValue.ToArray();
}

FString UMatureJsonArrayPureHelpers::ToString(const FMatureJsonArray& JArray) {
	return FMatureJsonValue().SetValue(JArray).ToString();
}

FMatureJsonValue UMatureJsonArrayPureHelpers::ToValue(const FMatureJsonArray& JArray) {
	return FMatureJsonValue().SetValue(JArray);
}

FMatureJsonArray UMatureJsonArrayPureHelpers::FromBooleanArray(const TArray<bool>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromFloatArray(const TArray<float>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromIntegerArray(const TArray<int32>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromStringArray(const TArray<FString>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromDateTimeArray(const TArray<FDateTime>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromGuidArray(const TArray<FGuid>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromColorArray(const TArray<FColor>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromLinearColorArray(const TArray<FLinearColor>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromRotatorArray(const TArray<FRotator>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromTransformArray(const TArray<FTransform>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromVectorArray(const TArray<FVector>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromObjectArray(const TArray<FMatureJsonObject>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}
FMatureJsonArray UMatureJsonArrayPureHelpers::FromValueArray(const TArray<FMatureJsonValue>& Value) {
	FMatureJsonArray List;
	for (auto& it : Value)
		List.AddValue(it);
	return  List;
}

// Convert a JSON value valueto a boolean.
bool UMatureJsonArrayPureHelpers::GetBoolean(FMatureJsonArray& Value, int index) {
	bool V=false;
	Value.GetValue(index, V);
	return V;
}
// Convert a JSON value valueto a float.
float UMatureJsonArrayPureHelpers::GetFloat(FMatureJsonArray& Value, int index) {
	float V=0.0f;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto an integer.
int32 UMatureJsonArrayPureHelpers::GetInteger(FMatureJsonArray& Value, int index) {
	int32 V=0;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a string.
FString UMatureJsonArrayPureHelpers::GetString(FMatureJsonArray& Value, int index) {
	FString V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a date/time.
FDateTime UMatureJsonArrayPureHelpers::GetDateTime(FMatureJsonArray& Value, int index) {
	FDateTime V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a GUID.
FGuid UMatureJsonArrayPureHelpers::GetGuid(FMatureJsonArray& Value, int index) {
	FGuid V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a color.
FColor UMatureJsonArrayPureHelpers::GetColor(FMatureJsonArray& Value, int index) {
	FColor V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FLinearColor UMatureJsonArrayPureHelpers::GetLinearColor(FMatureJsonArray& Value, int index) {
	FLinearColor V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FRotator UMatureJsonArrayPureHelpers::GetRotator(FMatureJsonArray& Value, int index) {
	FRotator V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FVector UMatureJsonArrayPureHelpers::GetVector(FMatureJsonArray& Value, int index) {
	FVector V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a linear color.
FTransform UMatureJsonArrayPureHelpers::GetTransform(FMatureJsonArray& Value, int index) {
	FTransform V;
	Value.GetValue(index).GetValue(V);
	return V;
}
// Convert a JSON value valueto a JSON object.
FMatureJsonObject UMatureJsonArrayPureHelpers::GetObject(FMatureJsonArray& Value, int index) {
	return Value.GetValue(index).ToObject(true);
}
// Convert a JSON value valueto a JSON array.
FMatureJsonArray UMatureJsonArrayPureHelpers::GetArray(FMatureJsonArray& Value, int index) {
	return Value.GetValue(index).ToArray(true);
}

FMatureJsonValue UMatureJsonArrayPureHelpers::NewValue(FMatureJsonArray& JArray, const int index) {
	return JArray.SetValue(index);
}
FMatureJsonObject UMatureJsonArrayPureHelpers::NewObject(FMatureJsonArray& JArray, const int index) {
	return JArray.SetObject(index);
}
FMatureJsonArray UMatureJsonArrayPureHelpers::NewArray(FMatureJsonArray& JArray, const int index) {
	return JArray.SetArray(index);
}
