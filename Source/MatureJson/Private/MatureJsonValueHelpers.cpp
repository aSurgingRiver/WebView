// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonValueHelpers.h"

bool UMatureJsonValueHelpers::ParseString(FMatureJsonValue& JValue,const FString& Text)
{
	return JValue.ParseString(Text);
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

FMatureJsonValue UMatureJsonValueHelpers::FromArray(const FMatureJsonArray& Value)
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

FMatureJsonArray UMatureJsonValueHelpers::ToArray(const FMatureJsonValue& JValue)
{
	return JValue.ToArray();
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

FMatureJsonValue& UMatureJsonValueHelpers::SetNull(FMatureJsonValue& JValue) {
	return JValue.SetValue();
}
FMatureJsonValue& UMatureJsonValueHelpers::SetBoolean(FMatureJsonValue& JValue, bool Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetFloat(FMatureJsonValue& JValue, float Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetInteger(FMatureJsonValue& JValue, int32 Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetString(FMatureJsonValue& JValue, const FString& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetDateTime(FMatureJsonValue& JValue, const FDateTime& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetGuid(FMatureJsonValue& JValue, const FGuid& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetColor(FMatureJsonValue& JValue, const FColor& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetLinearColor(FMatureJsonValue& JValue, const FLinearColor& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetRotator(FMatureJsonValue& JValue, const FRotator& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetTransform(FMatureJsonValue& JValue, const FTransform& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetVector(FMatureJsonValue& JValue, const FVector& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetObject(FMatureJsonValue& JValue, const FMatureJsonObject& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetArray(FMatureJsonValue& JValue, const FMatureJsonArray& Value) {
	return JValue.SetValue(Value);
}
FMatureJsonValue& UMatureJsonValueHelpers::SetValue(FMatureJsonValue& JValue, const FMatureJsonValue& Value) {
	return JValue.SetValue(Value);
}


