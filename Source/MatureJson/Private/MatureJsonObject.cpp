// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#include "MatureJsonObject.h"
//#include "MatureJsonConverter.h"
#include "MatureJsonList.h"
//#include "MatureJsonHelpers.h"
#include "MatureJsonEnums.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Policies/PrettyJsonPrintPolicy.h"



FMatureJsonObject::ObjectWrap::ObjectWrap()
	: Document(MakeShared<mature::Document>())
	, Object(Document->SetObject().GetObject())
{
}

//FMatureJsonObject::ObjectWrap::ObjectWrap(TSharedPtr<mature::Document> Doc)
//	: Document(Doc)
//	, Object(Document->SetObject().GetObject())
//{
//}
FMatureJsonObject::ObjectWrap::ObjectWrap(TSharedPtr<mature::Document> Doc,const mature::Object& Ref)
	: Document(Doc)
	, Object(Ref)
{
}
FMatureJsonObject::ObjectWrap::ObjectWrap(TSharedPtr<mature::Document> Doc, const mature::Object&& Ref)
	: Document(Doc)
	, Object(Ref)
{
}

mature::MemberIterator FMatureJsonObject::ObjectWrap::Begin() {
	return Object.MemberBegin();
}

mature::MemberIterator FMatureJsonObject::ObjectWrap::End() {
	return Object.MemberEnd();
}

FMatureJsonObject::FMatureJsonObject() 
	: ObjectPtr(MakeShared<ObjectWrap>())
{
}

FMatureJsonObject::FMatureJsonObject(TSharedPtr<mature::Document> Doc, const mature::Object& obj)
	: ObjectPtr(MakeShared<ObjectWrap>(Doc, obj))
{
}

FMatureJsonObject::FMatureJsonObject(TSharedPtr<mature::Document> Doc, const  mature::Object&& obj)
	: ObjectPtr(MakeShared<ObjectWrap>(Doc, obj))
{
}

FMatureJsonObject::FMatureJsonObject(const FMatureJsonObject& rhs)
	: ObjectPtr(rhs.ObjectPtr)
{

}

FMatureJsonObject::FMatureJsonObject(const FMatureJsonObject&& rhs)
	: ObjectPtr(rhs.ObjectPtr)
{

}


FMatureJsonValue FMatureJsonObject::AddKey(const FString& key) {
	if (!Object().HasMember(*key)) {
		Object().AddMember(mature::Value(*key, GetAllocator()), mature::Value(), GetAllocator());
	}
	return FMatureJsonValue(Document(), Object()[*key]);
}

FMatureJsonValue FMatureJsonObject::GetKey(const FString& key) const {
	if (!Object().HasMember(*key)) {
		return FMatureJsonValue();
	}
	return FMatureJsonValue(Document(), Object()[*key]);
}

//FMatureJsonObject& FMatureJsonObject::SetValue(const FString& key,const FMatureJsonValue& Value) {
//	AddKey(key).SetValue(Value);
//	return *this;
//}

FMatureJsonObject& FMatureJsonObject::SetValue( const FLinearColor& Value )
{
	Clear();
	AddKey(TEXT("r")).SetValue(Value.R);
	AddKey(TEXT("g")).SetValue(Value.G);
	AddKey(TEXT("b")).SetValue(Value.B);
	if (Value.A != 1.0f)
		AddKey(TEXT("a")).SetValue(Value.A);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const FRotator& Value )
{
	Clear();
	AddKey(TEXT("pitch")).SetValue(Value.Pitch);
	AddKey(TEXT("yaw")).SetValue(Value.Yaw);
	AddKey(TEXT("roll")).SetValue(Value.Roll);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const FTransform& Value )
{
	Clear();
	AddKey(TEXT("rotation")).SetValue(Value.Rotator());
	AddKey(TEXT("translation")).SetValue(Value.GetTranslation());
	const FVector Scale = Value.GetScale3D();
	if (Scale != FVector::OneVector)
	{
		if (Scale.IsUniform())
			AddKey(TEXT("scale")).SetValue(Scale.X);
		else
			AddKey(TEXT("scale")).SetValue(Scale);
	}
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const FVector& Value )
{
	Clear();
	AddKey(TEXT("x")).SetValue(Value.X);
	AddKey(TEXT("y")).SetValue(Value.Y);
	AddKey(TEXT("z")).SetValue(Value.Z);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue(const FMatureJsonObject& Value)
{
	Clear();
	auto it = Value.Object().MemberBegin();
	for (; it != Value.Object().MemberEnd(); it++) {
		AddKey(FString( it->name.GetString())).SetValue(FMatureJsonValue(Document(), it->value));
	}
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FMatureJsonValue>& Value )
{
	Clear();
	for ( const auto& Temp : Value )
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, bool>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, float>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, double>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, int32>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FString>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FDateTime>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FGuid>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FColor>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FLinearColor>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FRotator>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FTransform>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::SetValue( const TMap<FString, FVector>& Value )
{
	Clear();
	for (const auto& Temp : Value)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

int32 FMatureJsonObject::Size() const
{
	return Object().MemberCount();
}

bool FMatureJsonObject::IsEmpty()const {
	return Object().ObjectEmpty();
}

void FMatureJsonObject::Clear()
{
	Object().RemoveAllMembers();
}

bool FMatureJsonObject::HasKey( const FString& Key ) const
{
	return Object().HasMember(*Key);
}

void FMatureJsonObject::RemoveKey( const FString& Key )
{
	if (Object().HasMember(*Key)) {
		Object().RemoveMember(*Key);
	}
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FMatureJsonObject& rhs)
{
	auto it = rhs.Object().MemberBegin();
	for (; it != rhs.Object().MemberEnd(); it++) {
		AddKey(FString(it->name.GetString())).SetValue(FMatureJsonValue(Document(), it->value));
	}
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, bool>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, float>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, int32>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, double>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FString>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FDateTime>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FGuid>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FColor>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FLinearColor>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FRotator>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FTransform>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FVector>& Map)
{
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const TMap<FString, FMatureJsonValue>& Map) {
	for (const auto& Temp : Map)
		AddKey(Temp.Key).SetValue(Temp.Value);
	return *this;
}

FMatureJsonList FMatureJsonObject::AddList(const FString& Key) {
	return AddKey(Key).ToList();
}

FMatureJsonObject FMatureJsonObject::AddObject(const FString& Key) {
	return AddKey(Key).ToObject();
}

FMatureJsonValue FMatureJsonObject::AddValue(const FString& Key) {
	return AddKey(Key);
}

TArray<FString> FMatureJsonObject::GetKeys() const
{
	TArray<FString> Keys;
	auto it = Object().MemberBegin();
	for (; it != Object().MemberEnd(); it++) {
		Keys.Add(it->name.GetString());
	}
	return Keys;
}

void FMatureJsonObject::GetValue(FLinearColor& Value) {
	GetKey(TEXT("r")).GetValue(Value.R);
	GetKey(TEXT("g")).GetValue(Value.G);
	GetKey(TEXT("b")).GetValue(Value.B);
	GetKey(TEXT("a")).GetValue(Value.A);
}

void FMatureJsonObject::GetValue(FRotator& Value) {
	GetKey(TEXT("pitch")).GetValue(Value.Pitch);
	GetKey(TEXT("yaw")).GetValue(Value.Yaw);
	GetKey(TEXT("roll")).GetValue(Value.Roll);
}

void FMatureJsonObject::GetValue(FTransform& Value) {
	FRotator rotation;
	FVector translation;
	FVector scale;
	GetKey(TEXT("rotation")).GetValue(rotation);
	GetKey(TEXT("translation")).GetValue(translation);
	if (!GetKey(TEXT("scale")).GetValue(scale)) {
		double scalex=0.0;
		GetKey(TEXT("scale")).GetValue(scalex);
		scale = FVector(scalex);
	}
	Value = FTransform(rotation, translation, scale);
}

void FMatureJsonObject::GetValue(FVector& Value) {
	GetKey(TEXT("x")).GetValue(Value.X);
	GetKey(TEXT("z")).GetValue(Value.Y);
	GetKey(TEXT("y")).GetValue(Value.Z);
}


bool FMatureJsonObject::GetValue(const FString& Key, bool& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, float& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, uint32& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, int32& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, uint64& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, int64& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, double& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FString& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FGuid& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FColor& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FDateTime& value) const {
	if (!Object().HasMember(*Key))return false;
	return GetKey(Key).GetValue(value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FLinearColor& Value) const
{
	if (!Object().HasMember(*Key))return false;
	return  GetKey(Key).GetValue(Value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FRotator& Value) const
{
	if (!Object().HasMember(*Key))return false;
	return  GetKey(Key).GetValue(Value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FTransform& Value) const
{
	if (!Object().HasMember(*Key))return false;
	return  GetKey(Key).GetValue(Value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FVector& Value) const
{
	if (!Object().HasMember(*Key))return false;
	return  GetKey(Key).GetValue(Value);
}
bool FMatureJsonObject::GetValue(const FString& Key, FMatureJsonValue& Value) const
{
	if (!Object().HasMember(*Key))return false;
	Value = GetKey(Key);
	return  true;
}
bool FMatureJsonObject::GetValue(const FString& Key, FMatureJsonObject& Value) const
{
	if (!Object().HasMember(*Key))return false;
	Value = GetKey(Key).ToObject(true);
	return  true;
}
bool FMatureJsonObject::GetValue(const FString& Key, FMatureJsonList& Value) const
{
	if (!Object().HasMember(*Key))return false;
	Value = GetKey(Key).ToList(true);
	return  true;
}


FMatureJsonValue  FMatureJsonObject::ToValue(const FString& Key) const {
	FMatureJsonValue value;
	GetValue(Key, value);
	return value;
}

FMatureJsonObject FMatureJsonObject::ToObject(const FString& Key) const {
	FMatureJsonObject value;
	GetValue(Key, value);
	return value;
}

FMatureJsonList   FMatureJsonObject::ToList(const FString& Key) const {
	FMatureJsonList value;
	GetValue(Key, value);
	return value;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, bool Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, float Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, int32 Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, double Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const TCHAR* Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FString& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FDateTime& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FGuid& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FColor& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FLinearColor& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FRotator& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FTransform& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FVector& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FMatureJsonValue& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FMatureJsonObject& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const FMatureJsonList& Value)
{
	AddKey(*Key).SetValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const TArray<FMatureJsonValue>& Value)
{
	AddKey(*Key).ToList().AddValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::AddValue(const FString& Key, const TMap<FString, FMatureJsonValue>& Value)
{
	AddKey(*Key).ToObject().AddValue(Value);
	return *this;
}

FMatureJsonObject& FMatureJsonObject::operator=(const FMatureJsonObject& rhs) {
	ObjectPtr = rhs.ObjectPtr;
	return *this;
}

TSharedPtr<mature::Document> FMatureJsonObject::Document() {
	return ObjectPtr->Document;
}
TSharedPtr<mature::Document> FMatureJsonObject::Document()const {
	return ObjectPtr->Document;
}
inline mature::Object& FMatureJsonObject::Object(){
	return ObjectPtr->Object;
}
inline mature::Object& FMatureJsonObject::Object() const {
	return ObjectPtr->Object;
}
inline mature::Allocator& FMatureJsonObject::GetAllocator() {
	return ObjectPtr->Document->GetAllocator();
}
inline mature::Allocator& FMatureJsonObject::GetAllocator()const {
	return ObjectPtr->Document->GetAllocator();
}


FMatureJsonObjectIterator::FMatureJsonObjectIterator()
	: ObjectPtr(nullptr), Iterator()
{
}

FMatureJsonObjectIterator::FMatureJsonObjectIterator(const FMatureJsonObject& Value)
	: ObjectPtr(Value.ObjectPtr), Iterator(ObjectPtr->Begin())
{
}

FMatureJsonObjectIterator& FMatureJsonObjectIterator::Begin() {
	if (nullptr != ObjectPtr)
		Iterator = ObjectPtr->Begin(); 
	return *this;
}
FMatureJsonObjectIterator& FMatureJsonObjectIterator::End() {
	if (nullptr != ObjectPtr)
		Iterator = ObjectPtr->End();
	return *this;
}

bool FMatureJsonObjectIterator::IsValid()const {
	if (nullptr == ObjectPtr)return false;
	if (Iterator == ObjectPtr->End())return false;
	return ObjectPtr->Begin() <= Iterator;
}

void FMatureJsonObjectIterator::Next(int step) {
	Iterator = Iterator + step;
}

FString FMatureJsonObjectIterator::Key() {
	return Iterator->name.GetString();
}

FMatureJsonValue FMatureJsonObjectIterator::Value() {
	return FMatureJsonValue(ObjectPtr->Document, Iterator->value);
}

FString FMatureJsonObjectIterator::Key() const {
	return Iterator->name.GetString();
}

FMatureJsonValue FMatureJsonObjectIterator::Value() const {
	return FMatureJsonValue(ObjectPtr->Document, Iterator->value);
}

FMatureJsonObjectIterator& FMatureJsonObjectIterator::operator++() {
	Iterator++;
	return *this;
}

FMatureJsonObjectIterator& FMatureJsonObjectIterator::operator--() {
	Iterator--;
	return *this;
}

FMatureJsonObjectIterator& FMatureJsonObjectIterator::operator++(int) {
	++Iterator;
	return *this;
}
FMatureJsonObjectIterator& FMatureJsonObjectIterator::operator--(int) { 
	--Iterator;
	return *this;
}

FMatureJsonObjectIterator& FMatureJsonObjectIterator::operator=(const FMatureJsonObject& Value) {
	ObjectPtr = Value.ObjectPtr;
	Iterator = ObjectPtr->Begin();
	return *this;
}

FMatureJsonObjectIterator& FMatureJsonObjectIterator::operator=(const FMatureJsonObjectIterator& Value) {
	ObjectPtr = Value.ObjectPtr;
	Iterator = Value.Iterator;
	return *this;
}
