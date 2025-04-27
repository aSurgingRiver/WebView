// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonValuePureHelpers.h"


FMatureJsonValue UMatureJsonValuePureHelpers::Parse(const FString& Text) {
	FMatureJsonValue JValue;
	JValue.ParseString(Text);
	return JValue;
}

FString UMatureJsonValuePureHelpers::SaveString(FMatureJsonValue& JValue) {
	return JValue.SaveString();
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromBoolean(bool Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromFloat(float Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromInteger(int32 Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromString(const FString& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromDateTime(const FDateTime& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromGuid(const FGuid& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromColor(const FColor& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromLinearColor(const FLinearColor& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromRotator(const FRotator& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromTransform(const FTransform& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromVector(const FVector& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromObject(const FMatureJsonObject& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromArray(const FMatureJsonArray& Value)
{
	return FMatureJsonValue().SetValue(Value);
}

FMatureJsonValue UMatureJsonValuePureHelpers::FromValue(const FMatureJsonValue& Value) {
	return FMatureJsonValue().SetValue(Value);
}

bool UMatureJsonValuePureHelpers::ToBoolean(const FMatureJsonValue& JValue)
{
	return JValue.ToBoolean();
}

float UMatureJsonValuePureHelpers::ToFloat(const FMatureJsonValue& JValue)
{
	return JValue.ToFloat();
}

int32 UMatureJsonValuePureHelpers::ToInteger(const FMatureJsonValue& JValue)
{
	return JValue.ToInteger();
}

FString UMatureJsonValuePureHelpers::ToString(const FMatureJsonValue& JValue)
{
	return JValue.ToString();
}

FDateTime UMatureJsonValuePureHelpers::ToDateTime(const FMatureJsonValue& JValue)
{
	return JValue.ToDateTime();
}

FGuid UMatureJsonValuePureHelpers::ToGuid(const FMatureJsonValue& JValue)
{
	return JValue.ToGuid();
}

FColor UMatureJsonValuePureHelpers::ToColor(const FMatureJsonValue& JValue)
{
	return JValue.ToColor();
}

FLinearColor UMatureJsonValuePureHelpers::ToLinearColor(const FMatureJsonValue& JValue)
{
	return JValue.ToLinearColor();
}
FRotator UMatureJsonValuePureHelpers::ToRotator(const FMatureJsonValue& JValue) {
	FRotator Ret;
	JValue.GetValue(Ret);
	return Ret;
}
FVector UMatureJsonValuePureHelpers::ToVector(const FMatureJsonValue& JValue) {
	FVector Ret;
	JValue.GetValue(Ret);
	return Ret;
}
FTransform UMatureJsonValuePureHelpers::ToTransform(const FMatureJsonValue& JValue) {
	FTransform Ret;
	JValue.GetValue(Ret);
	return Ret;
}
FMatureJsonObject UMatureJsonValuePureHelpers::ToObject(const FMatureJsonValue& JValue)
{
	return JValue.ToObject();
}

FMatureJsonArray UMatureJsonValuePureHelpers::ToArray(const FMatureJsonValue& JValue)
{
	return JValue.ToArray();
}

int UMatureJsonValuePureHelpers::Size(const FMatureJsonValue& JValue) {
	return JValue.Size();
}
bool UMatureJsonValuePureHelpers::IsEmpty(const FMatureJsonValue& JValue) {
	return JValue.IsEmpty();
}

EMatureJsonType UMatureJsonValuePureHelpers::Type(const FMatureJsonValue& JValue) {
	return JValue.GetType();
}

bool UMatureJsonValuePureHelpers::IsObject(const FMatureJsonValue& JValue) {
	return JValue.GetType()== EMatureJsonType::Object;
}

bool UMatureJsonValuePureHelpers::IsArray(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Array;
}

bool UMatureJsonValuePureHelpers::IsString(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::String;
}

bool UMatureJsonValuePureHelpers::IsNumber(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Number;
}

bool UMatureJsonValuePureHelpers::IsNull(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Null;
}

bool UMatureJsonValuePureHelpers::IsBool(const FMatureJsonValue& JValue) {
	return JValue.GetType() == EMatureJsonType::Bool;
}
