// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#include "MatureJsonValueHelpers.h"

bool UMatureJsonValueHelpers::Parse(FMatureJsonValue& JValue,const FString& Text)
{
	return JValue.Parse(Text);
}

bool UMatureJsonValueHelpers::ParseFile(FMatureJsonValue& JValue, const FString& filepath) {
	return JValue.ParseFile(filepath);
}

FString UMatureJsonValueHelpers::SaveString(FMatureJsonValue& JValue) {
	return JValue.SaveString();
}

bool UMatureJsonValueHelpers::SaveFile(FMatureJsonValue& JValue, const FString& filepath) {
	return JValue.SaveFile(filepath);
}

FMatureJsonValue UMatureJsonValueHelpers::FromBoolean(bool Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromFloat(float Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromInteger(int32 Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromString(const FString& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromDateTime(const FDateTime& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromGuid(const FGuid& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromColor(const FColor& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromLinearColor(const FLinearColor& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromRotator(const FRotator& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromTransform(const FTransform& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromVector(const FVector& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromObject(const FMatureJsonObject& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromList(const FMatureJsonList& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValueHelpers::FromValue(const FMatureJsonValue& Value) {
	return FMatureJsonValue().SetValue(Value);
}

bool UMatureJsonValueHelpers::ToBoolean(const FMatureJsonValue& JValue)
{
	
	return JValue.ToBoolean();
}

float UMatureJsonValueHelpers::ToFloat(const FMatureJsonValue& JValue)
{
	return JValue.ToFloat();
}

int32 UMatureJsonValueHelpers::ToInteger(const FMatureJsonValue& JValue)
{
	return JValue.ToInteger();
}

FString UMatureJsonValueHelpers::ToString(const FMatureJsonValue& JValue)
{
	return JValue.ToString();
}

FDateTime UMatureJsonValueHelpers::ToDateTime(const FMatureJsonValue& JValue)
{
	return JValue.ToDateTime();
}

FGuid UMatureJsonValueHelpers::ToGuid(const FMatureJsonValue& JValue)
{
	return JValue.ToGuid();
}

FColor UMatureJsonValueHelpers::ToColor(const FMatureJsonValue& JValue)
{
	return JValue.ToColor();
}

FLinearColor UMatureJsonValueHelpers::ToLinearColor(const FMatureJsonValue& JValue)
{
	return JValue.ToLinearColor();
}
FRotator UMatureJsonValueHelpers::ToRotator(const FMatureJsonValue& JValue) {
	FRotator Ret;
	JValue.GetValue(Ret);
	return Ret;
}
FVector UMatureJsonValueHelpers::ToVector(const FMatureJsonValue& JValue) {
	FVector Ret;
	JValue.GetValue(Ret);
	return Ret;
}
FTransform UMatureJsonValueHelpers::ToTransform(const FMatureJsonValue& JValue) {
	FTransform Ret;
	JValue.GetValue(Ret);
	return Ret;
}
FMatureJsonObject UMatureJsonValueHelpers::ToObject(const FMatureJsonValue& JValue)
{
	return JValue.ToObject();
}

FMatureJsonList UMatureJsonValueHelpers::ToList(const FMatureJsonValue& JValue)
{
	return JValue.ToList();
}

int UMatureJsonValueHelpers::Size(const FMatureJsonValue& JValue) {
	return JValue.Size();
}
bool UMatureJsonValueHelpers::IsEmpty(const FMatureJsonValue& JValue) {
	return JValue.IsEmpty();
}
FMatureJsonValue& UMatureJsonValueHelpers::Clear(FMatureJsonValue& JValue) {
	JValue.Clear();
	return JValue;
}

EMatureJsonType UMatureJsonValueHelpers::Type(const FMatureJsonValue& JValue) {
	return JValue.GetType();
}

bool UMatureJsonValueHelpers::IsObject(const FMatureJsonValue& JValue) {
	return JValue.GetType()== EMatureJsonType::Object;
}

bool UMatureJsonValueHelpers::IsArray(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Array;
}

bool UMatureJsonValueHelpers::IsString(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::String;
}

bool UMatureJsonValueHelpers::IsNumber(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Number;
}

bool UMatureJsonValueHelpers::IsNull(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Null;
}

bool UMatureJsonValueHelpers::IsBool(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Bool;
}
