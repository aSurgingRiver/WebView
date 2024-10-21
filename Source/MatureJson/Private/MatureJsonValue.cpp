// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"
#include "MatureJsonLog.h"
#include "json_cast.h"
#include "Misc/FileHelper.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Policies/PrettyJsonPrintPolicy.h"


FMatureJsonValue::ValueWrap::ValueWrap()
	: Document(MakeShared<mature::Document>())
	, ValueRef(*Document.Get())
{
}

FMatureJsonValue::ValueWrap::ValueWrap(TSharedPtr<mature::Document> Doc)
	: Document(Doc)
	, ValueRef(*Document.Get())
{
}
FMatureJsonValue::ValueWrap::ValueWrap(TSharedPtr<mature::Document> Doc, mature::Value& Ref)
	: Document(Doc)
	, ValueRef(Ref)
{
}

bool FMatureJsonValue::ValueWrap::IsRoot() {
	void* Doc = Document.Get();
	void* ValPtr = &ValueRef;
	return Doc == ValPtr;
}

FMatureJsonValue::FMatureJsonValue(/*const TSharedPtr<mature::Document>& Doc*/)
	: ValueCache(MakeShared<ValueWrap>())
{
}

FMatureJsonValue::FMatureJsonValue(const TSharedPtr<mature::Document>& Doc, mature::Value& v)
	: ValueCache(MakeShared<ValueWrap>(Doc, v))
{
}

FMatureJsonValue::FMatureJsonValue(const FMatureJsonValue& rhs)
	: ValueCache(rhs.ValueCache)
{
}

FMatureJsonValue& FMatureJsonValue::SetValue() {
	ValueRef().SetNull();
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const bool Value )
{
	ValueRef().SetBool(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const float Value )
{
	ValueRef().SetFloat(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const double Value )
{
	ValueRef().SetDouble(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const int8 Value )
{
	ValueRef().SetInt(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const uint8 Value )
{
	ValueRef().SetUint(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const int16 Value )
{
	ValueRef().SetInt(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const uint16 Value )
{
	ValueRef().SetUint(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const int32 Value )
{
	ValueRef().SetInt(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const uint32 Value )
{
	ValueRef().SetUint(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const int64 Value )
{
	ValueRef().SetInt64(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const uint64 Value )
{
	ValueRef().SetUint64(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const TCHAR* Value)
{
	FString in = Value;
	ValueRef().SetString(*in, in.Len(), GetAllocator());
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue( const FString& Value )
{
	ValueRef().SetString(*Value, Value.Len(), GetAllocator());
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue( const FDateTime& Value)
{
	FString serial = Value.ToIso8601();
	ValueRef().SetString(*serial, serial.Len(), GetAllocator());
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue( const FGuid& Value )
{
	FString serial = Value.ToString(EGuidFormats::DigitsWithHyphens);
	ValueRef().SetString(*serial, serial.Len(), GetAllocator());
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue( const FColor& Value )
{
	//
	FString serial = "#" + Value.ToHex();
	ValueRef().SetString(*serial, serial.Len(), GetAllocator());
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const FTransform& Value)
{
	//
	ToObject().SetValue(Value);
	return *this;
}
FMatureJsonValue& FMatureJsonValue::SetValue(const FVector& Value)
{
	//
	ToObject().SetValue(Value);
	return *this;
}
FMatureJsonValue& FMatureJsonValue::SetValue(const FRotator& Value)
{
	//
	ToObject().SetValue(Value);
	return *this;
}
FMatureJsonValue& FMatureJsonValue::SetValue(const FLinearColor& Value)
{
	ToObject().SetValue(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const FMatureJsonValue& Value) {
	ValueRef().CopyFrom(Value.ValueRef(), GetAllocator());
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const FMatureJsonObject& Value) {
	ToObject().SetValue(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(const FMatureJsonArray& Value) {
	if (ValueRef().GetType()!=mature::Type::kArrayType)ValueRef().SetArray();
	FMatureJsonArray(Document(), ValueRef().GetArray()).AddValue(Value);
	return *this;
}

FMatureJsonValue& FMatureJsonValue::SetValue(mature::Value& Value) {
	ValueRef().CopyFrom(Value,GetAllocator());
	return *this;
}


EMatureJsonTypeNumber FMatureJsonValue::NumberType()const {
	if (mature::Type::kNumberType != ValueRef().GetType())return EMatureJsonTypeNumber::Unkown;
	if (ValueRef().IsDouble())return EMatureJsonTypeNumber::Double;
	else if (ValueRef().IsInt64())return EMatureJsonTypeNumber::Int64;
	else if (ValueRef().IsUint64())return EMatureJsonTypeNumber::Uint64;
	else if (ValueRef().IsInt())return EMatureJsonTypeNumber::Int32;
	else if (ValueRef().IsUint())return EMatureJsonTypeNumber::Uint32;
	return EMatureJsonTypeNumber::Unkown;
}

EMatureJsonType FMatureJsonValue::GetType() const
{
	switch (ValueRef().GetType())
	{
		case mature::Type::kNullType:    return EMatureJsonType::Null;
		case mature::Type::kFalseType :  return EMatureJsonType::Bool;
		case mature::Type::kTrueType:    return EMatureJsonType::Bool;
		case mature::Type::kNumberType:  return EMatureJsonType::Number;
		case mature::Type::kStringType:  return EMatureJsonType::String;
		case mature::Type::kObjectType:  return EMatureJsonType::Object;
		case mature::Type::kArrayType:   return EMatureJsonType::Array;
	}

	return EMatureJsonType::Null;
}
int  FMatureJsonValue::Size() const {
	return ValueRef().Size();
}
bool FMatureJsonValue::IsEmpty() const {
	return ValueRef().Empty();
}
void FMatureJsonValue::Clear() {
	ValueRef().Clear();
}

bool FMatureJsonValue::ToBoolean() const
{
	switch (ValueRef().GetType())
	{
	case mature::Type::kFalseType: return ValueRef().GetBool();
	case mature::Type::kTrueType:  return ValueRef().GetBool();
	case mature::Type::kNumberType: return mature::GetNumber<bool>(ValueRef());
	case mature::Type::kStringType:  return FString(ValueRef().GetString()).ToBool();
	}
	return false;
}

float FMatureJsonValue::ToFloat() const
{
	return mature::GetNumber<float>(ValueRef());
}

double FMatureJsonValue::ToNumber() const
{
	return mature::GetNumber<double>(ValueRef());
}

int32 FMatureJsonValue::ToInteger() const
{
	return mature::GetNumber<int32>(ValueRef());
}

FString FMatureJsonValue::ToString() const
{
	switch (ValueRef().GetType())
	{
	case mature::Type::kFalseType: return TEXT("false");
	case mature::Type::kTrueType:  return TEXT("true");
	case mature::Type::kNumberType: return FString::SanitizeFloat(mature::GetNumber<float>(ValueRef()), 0);
	case mature::Type::kStringType: return FString(ValueRef().GetString());
	}
	return FString();
}

FDateTime FMatureJsonValue::ToDateTime() const
{
	FDateTime DateTime;
	GetValue(DateTime);
	return DateTime;
}

FGuid FMatureJsonValue::ToGuid() const
{
	FGuid Guid;
	GetValue(Guid);
	return Guid;
}

FLinearColor FMatureJsonValue::ToLinearColor() const {
	FLinearColor value;
	GetValue(value);
	return value;
}

FColor FMatureJsonValue::ToColor() const
{
	FColor value;
	GetValue(value);
	return value;
}

FMatureJsonObject FMatureJsonValue::ToObject(bool check) const
{
	if (ValueRef().GetType() != mature::Type::kObjectType)
	{
		if (ValueRef().GetType() != mature::Type::kNullType && check == true ) {
			return FMatureJsonObject();
		}
		ValueRef().SetObject();
	}
	return FMatureJsonObject(Document(), ValueRef().GetObject());
}

FMatureJsonArray FMatureJsonValue::ToArray(bool check) const
{
	if (ValueRef().GetType() != mature::Type::kArrayType)
	{
		if (ValueRef().GetType() != mature::Type::kNullType && check == true) {
			return FMatureJsonArray();
		}
		ValueRef().SetArray();
	}
	return FMatureJsonArray(Document(), ValueRef().GetArray());
}

int32 FMatureJsonValue::ToInt32() const
{
	return mature::GetNumber<int32>(ValueRef());
}

uint32 FMatureJsonValue::ToUInt32() const
{
	return mature::GetNumber<uint32>(ValueRef());
}

int64 FMatureJsonValue::ToInt64() const
{
	return mature::GetNumber<int64>(ValueRef());
}

uint64 FMatureJsonValue::ToUInt64() const
{
	return mature::GetNumber<uint64>(ValueRef());
}


bool FMatureJsonValue::GetValue(bool& value)const {
	if (mature::Type::kNumberType != ValueRef().GetType())return false;
	if (ValueRef().IsDouble())value = 0.05f <= ValueRef().GetDouble() || (ValueRef().GetDouble()) <= -0.05f;
	else if (ValueRef().IsInt64())value = bool (ValueRef().GetInt64());
	else if (ValueRef().IsUint64())value = bool(ValueRef().GetUint64());
	else if (ValueRef().IsInt())value = bool(ValueRef().GetInt());
	else if (ValueRef().IsUint())value = bool(ValueRef().GetUint());
	else return false;
	return false;
	//return GetNumberBool<bool>(ValueRef(), value);
}
bool FMatureJsonValue::GetValue(float& value)const {
	if (mature::Type::kNumberType != ValueRef().GetType())return false;
	if (ValueRef().IsDouble())value = (ValueRef().GetDouble());
	else if (ValueRef().IsInt64())value = (ValueRef().GetInt64());
	else if (ValueRef().IsUint64())value = (ValueRef().GetUint64());
	else if (ValueRef().IsInt())value = (ValueRef().GetInt());
	else if (ValueRef().IsUint())value = (ValueRef().GetUint());
	else return false;
	return false;
}
bool FMatureJsonValue::GetValue(int32& value)const {
	if (mature::Type::kNumberType != ValueRef().GetType())return false;
	if (ValueRef().IsDouble())value = (ValueRef().GetDouble());
	else if (ValueRef().IsInt64())value = (ValueRef().GetInt64());
	else if (ValueRef().IsUint64())value = (ValueRef().GetUint64());
	else if (ValueRef().IsInt())value = (ValueRef().GetInt());
	else if (ValueRef().IsUint())value = (ValueRef().GetUint());
	else return false;
	return false;
}
bool FMatureJsonValue::GetValue(int64& value)const {
	if (mature::Type::kNumberType != ValueRef().GetType())return false;
	if (ValueRef().IsDouble())value = (ValueRef().GetDouble());
	else if (ValueRef().IsInt64())value = (ValueRef().GetInt64());
	else if (ValueRef().IsUint64())value = (ValueRef().GetUint64());
	else if (ValueRef().IsInt())value = (ValueRef().GetInt());
	else if (ValueRef().IsUint())value = (ValueRef().GetUint());
	else return false;
	return false;
}
bool FMatureJsonValue::GetValue(uint32& value)const {
	if (mature::Type::kNumberType != ValueRef().GetType())return false;
	if (ValueRef().IsDouble())value = (ValueRef().GetDouble());
	else if (ValueRef().IsInt64())value = (ValueRef().GetInt64());
	else if (ValueRef().IsUint64())value = (ValueRef().GetUint64());
	else if (ValueRef().IsInt())value = (ValueRef().GetInt());
	else if (ValueRef().IsUint())value = (ValueRef().GetUint());
	else return false;
	return false;
}
bool FMatureJsonValue::GetValue(uint64& value)const {
	if (mature::Type::kNumberType != ValueRef().GetType())return false;
	if (ValueRef().IsDouble())value = (ValueRef().GetDouble());
	else if (ValueRef().IsInt64())value = (ValueRef().GetInt64());
	else if (ValueRef().IsUint64())value = (ValueRef().GetUint64());
	else if (ValueRef().IsInt())value = (ValueRef().GetInt());
	else if (ValueRef().IsUint())value = (ValueRef().GetUint());
	else return false;
	return false;
}
bool FMatureJsonValue::GetValue(double& value)const {
	if (mature::Type::kNumberType != ValueRef().GetType())return false;
	if (ValueRef().IsDouble())value = (ValueRef().GetDouble());
	else if (ValueRef().IsInt64())value = (ValueRef().GetInt64());
	else if (ValueRef().IsUint64())value = (ValueRef().GetUint64());
	else if (ValueRef().IsInt())value = (ValueRef().GetInt());
	else if (ValueRef().IsUint())value = (ValueRef().GetUint());
	else return false;
	return false;
}
bool FMatureJsonValue::GetValue(FString& value)const {
	return GetStringBool(ValueRef(), value);
}
bool FMatureJsonValue::GetValue(FDateTime& value)const {
	if (mature::Type::kStringType != ValueRef().GetType())
		return false;

	return FDateTime::ParseIso8601(ValueRef().GetString(), value);
}
bool FMatureJsonValue::GetValue(FGuid& value)const {
	if (mature::Type::kStringType != ValueRef().GetType())
		return false;
	if (FGuid::Parse(ValueRef().GetString(), value))
		return value.IsValid();
	return false;
}

bool FMatureJsonValue::GetValue(FColor& value)const {
	if (mature::Type::kStringType != ValueRef().GetType())
		return false;

	if (!IsColor(ValueRef().GetString())) 
		return false;
	value = FColor::FromHex(ValueRef().GetString());
	return true;
}

bool FMatureJsonValue::GetValue(FLinearColor& value)const {
	if (ValueRef().GetType() != mature::Type::kObjectType)return false;;
	ToObject().GetValue(value);
	return true;
}

bool FMatureJsonValue::GetValue(FRotator& value)const {
	if (mature::Type::kObjectType != ValueRef().GetType())
		return false;
	ToObject().GetValue(value);
	return true;
}

bool FMatureJsonValue::GetValue(FVector& value)const {
	if (mature::Type::kObjectType != ValueRef().GetType())
		return false;
	ToObject().GetValue(value);
	return true;
}
bool FMatureJsonValue::GetValue(FTransform& value)const {
	if (mature::Type::kObjectType != ValueRef().GetType())
		return false;
	ToObject().GetValue(value);
	return true;
}

bool FMatureJsonValue::IsDateTime() const
{
	if (mature::Type::kStringType != ValueRef().GetType())
		return false;

	FDateTime DateTime;
	return FDateTime::ParseIso8601(ValueRef().GetString(), DateTime );
}

bool FMatureJsonValue::IsGuid() const
{
	if (mature::Type::kStringType != ValueRef().GetType())
		return false;

	FGuid Guid;
	if ( FGuid::Parse(ValueRef().GetString(), Guid ) )
		return Guid.IsValid();

	return false;
}

bool FMatureJsonValue::IsColor(FString hex_string) const
{
	if (hex_string.IsEmpty() )
		return false;
	if (hex_string.StartsWith(TEXT("#"))) {
		hex_string.RemoveAt(0, 1);
	}

	int32 StartIndex = 0;
	if (hex_string.Len() == 8 )
	{
		for (int32 i = 0; i < 8; i++)
			if (!FChar::IsHexDigit(hex_string[StartIndex++]))
				return false;

		return true;
	}
	if (hex_string.Len() == 6 )
	{
		for (int32 i = 0; i < 6; i++)
			if (!FChar::IsHexDigit(hex_string[StartIndex++]))
				return false;

		return true;
	}
	if (hex_string.Len() == 3 )
	{
		for ( int32 i = 0; i < 3; i++ )
			if ( !FChar::IsHexDigit(hex_string[ StartIndex++ ] ) )
				return false;

		return true;
	}
	return false;
}

FMatureJsonValue& FMatureJsonValue::operator=(const FMatureJsonValue& rhs) {
	ValueCache = rhs.ValueCache;
	return *this;
}

bool FMatureJsonValue::ParseString(const FString& Text) {
	ValueCache = MakeShared<ValueWrap>();
	Document()->Parse(*Text);
	if (!Document()->HasParseError())return true;
	int offset = Document()->GetErrorOffset();
	rapidjson::ParseErrorCode errorCode = Document()->GetParseError();
	FString ErrorPos;
	if (offset < Text.Len() && errorCode != rapidjson::ParseErrorCode::kParseErrorDocumentEmpty) {
		ErrorPos = FString((*Text) + offset, 20);
	}

	FString Desc = UTF8_TO_TCHAR( rapidjson::GetParseError_En(errorCode));
	UE_LOG(MatureJsonLog,Log,TEXT("Parse Error: ErrorCode[%d] Desc[%s] pos[%d] Content[%s]")
		, errorCode , *Desc, offset, *ErrorPos
	);
	return false;
}

bool FMatureJsonValue::ParseFile(const FString& FileName) {
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *FileName)) {
		return false;
	}
	return ParseString(FileContents);
}

FString FMatureJsonValue::SaveString() const{
	mature::StringBuffer buffer;
	mature::Writer writer(buffer);
	TSharedPtr<ValueWrap> DocRoot;
	if (ValueCache->IsRoot()) {
		DocRoot = ValueCache;
	}
	else {
		DocRoot = MakeShared<ValueWrap>();
		DocRoot->ValueRef.CopyFrom(ValueCache->ValueRef, DocRoot->Document->GetAllocator());
	}
	if (!DocRoot->Document->Accept(writer))
		return FString();
	return  buffer.GetString();
}

bool FMatureJsonValue::SaveFile(FString FileName) const {
	return FFileHelper::SaveStringToFile(SaveString(), *FileName);
}

TSharedPtr<mature::Document> FMatureJsonValue::Document() {
	return ValueCache->Document;
}

TSharedPtr<mature::Document> FMatureJsonValue::Document() const {
	return ValueCache->Document;
}
inline mature::Value& FMatureJsonValue::ValueRef() {
	return ValueCache->ValueRef;
}
inline mature::Value& FMatureJsonValue::ValueRef() const {
	return ValueCache->ValueRef;
}
inline mature::Allocator& FMatureJsonValue::GetAllocator() {
	return ValueCache->Document->GetAllocator();
}
inline mature::Allocator& FMatureJsonValue::GetAllocator()const {
	return ValueCache->Document->GetAllocator();
}


