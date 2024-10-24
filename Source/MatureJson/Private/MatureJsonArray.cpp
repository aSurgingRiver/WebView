// Copyright aXiuShen. All Rights Reserved.
#include "MatureJsonArray.h"
#include "MatureJsonEnums.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
//#include "MatureJsonHelpers.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Policies/PrettyJsonPrintPolicy.h"


FMatureJsonArray::ListWrap::ListWrap()
	: Document(MakeShared<mature::Document>())
	, List(Document->SetArray().GetArray())
{
}

FMatureJsonArray::ListWrap::ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array& Ref)
	: Document(Doc)
	, List(Ref)
{
}
FMatureJsonArray::ListWrap::ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array&& Ref)
	: Document(Doc)
	, List(Ref)
{
}
int FMatureJsonArray::ListWrap::Size() {
	return List.Size();
}


FMatureJsonArray::FMatureJsonArray()
	: ListPtr(MakeShared<ListWrap>())
{
}
FMatureJsonArray::FMatureJsonArray(const TSharedPtr<mature::Document>& Doc,const mature::Array& a)
	: ListPtr(MakeShared<ListWrap>(Doc, a))
{
}
FMatureJsonArray::FMatureJsonArray(const TSharedPtr<mature::Document>& Doc, const mature::Array&& a)
	: ListPtr(MakeShared<ListWrap>(Doc, a))
{
}

FMatureJsonArray::FMatureJsonArray(const FMatureJsonArray& rhs)
	: ListPtr(rhs.ListPtr)
{
}

int32 FMatureJsonArray::Size() const
{
	return List().Size();
}

bool FMatureJsonArray::IsEmpty() const
{
	return List().Empty();
}

bool FMatureJsonArray::HasIndex(const int index) const
{
	if (index < 0 || Size() <= index) return false;
	return true;
}

void FMatureJsonArray::Clear()
{
	List().Clear();
}

FMatureJsonArray& FMatureJsonArray::Append(const FMatureJsonArray& List)
{
	auto it = List.List().Begin();
	for (; it != List.List().End(); it++) {
		AddValue().SetValue(*it);
	}
	return *this;
}

FMatureJsonArray& FMatureJsonArray::Append(const TArray<FMatureJsonValue>& Value) {
	for (auto& it : Value) {
		AddValue().SetValue(it);
	}
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( bool Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( float Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( int32 Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( double Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue(const TCHAR* Value)
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( const FString& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( const FDateTime& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( const FGuid& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( const FColor& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue(const FLinearColor& Value)
{
	AddValue().SetValue(Value);
	return *this;
} 
FMatureJsonArray& FMatureJsonArray::AddValue(const FRotator& Value)
{
	AddValue().SetValue(Value);
	return *this;
} 
FMatureJsonArray& FMatureJsonArray::AddValue(const FTransform& Value)
{
	AddValue().SetValue(Value);
	return *this;
} 
FMatureJsonArray& FMatureJsonArray::AddValue(const FVector& Value)
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( const FMatureJsonValue& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue(const FMatureJsonObject& Value) {
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( const FMatureJsonArray& Value)
{
	auto NewList = AddValue().ToArray();
	for (auto& it : Value.List()) {
		NewList.List().PushBack(it, GetAllocator());
	}
	return *this;
}

FMatureJsonArray& FMatureJsonArray::AddValue( const TArray<FMatureJsonValue>& Value )
{
	auto NewList = AddValue().ToArray();
	for (auto& it : Value) {
		NewList.AddValue().SetValue(it);
	}
	return *this;
}

// Set an item as a boolean.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<bool>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a float.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<float>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as an integer.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<int32>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a number.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<double>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a string.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FString>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a date/time.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FDateTime>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a GUID.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FGuid>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a color.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FColor>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a linear color.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FLinearColor>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a rotator.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FRotator>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a transform.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FTransform>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a vector.
FMatureJsonArray& FMatureJsonArray::AddValue(const TArray<FVector>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}

FMatureJsonValue FMatureJsonArray::AddValue()const {
	const int idx = List().Size();
	List().PushBack(mature::Value(), GetAllocator());
	return FMatureJsonValue(Document(), List()[idx]);
}

FMatureJsonObject FMatureJsonArray::AddObject() {
	return AddValue().ToObject();
}

FMatureJsonArray FMatureJsonArray::AddArray() {
	return AddValue().ToArray();
}

// Set an item as a boolean.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<bool>& Value) {
	return AddValue().ToArray().AddValue(Value);
}

// Set an item as a float.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<float>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as an integer.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<int32>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a number.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<double>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a string.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FString>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a date/time.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FDateTime>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a GUID.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FGuid>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a color.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FColor>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a linear color.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FLinearColor>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a rotator.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FRotator>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a transform.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FTransform>& Value) {
	return AddValue().ToArray().AddValue(Value);
}
// Set an item as a vector.
FMatureJsonArray FMatureJsonArray::AddArray(const TArray<FVector>& Value) {
	return AddValue().ToArray().AddValue(Value);
}


// Set an item as a vector.
FMatureJsonArray& FMatureJsonArray::MergeList(const FMatureJsonArray& rhs) {
	int idx = 0;
	for (; idx < rhs.Size(); idx++) {
		AddValue(rhs.GetValue(idx));
	}
	return *this;
}

FMatureJsonValue FMatureJsonArray::SetValue(int32 Index) {
	return GetValue(Index).SetValue();
}

FMatureJsonArray FMatureJsonArray::SetArray(int32 Index) {
	return GetValue(Index).ToArray();
}

FMatureJsonObject FMatureJsonArray::SetObject(int32 Index) {
	return GetValue(Index).ToObject();
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, bool Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, float Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, int32 Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, double Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue(int32 Index, const TCHAR* Value) {
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const FString& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const FDateTime& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const FGuid& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const FColor& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}


FMatureJsonArray& FMatureJsonArray::SetValue(int32 Index, const FLinearColor& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue(int32 Index, const FRotator& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}
FMatureJsonArray& FMatureJsonArray::SetValue(int32 Index, const FTransform& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue(int32 Index, const FVector& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const FMatureJsonValue& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const FMatureJsonObject& Value )
{
	GetValue(Index).SetValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const FMatureJsonArray& Value )
{
	GetValue(Index).SetValue().SetValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const TArray<FMatureJsonValue>& Value )
{
	GetValue(Index).SetValue().ToArray().AddValue(Value);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::SetValue( int32 Index, const TMap<FString, FMatureJsonValue>& Value )
{
	GetValue(Index).SetValue().ToObject().AddValue(Value);
	return *this;
}

bool FMatureJsonArray::GetValue(int32 Index, bool& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, float& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, int32& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, double& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FString& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FDateTime& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FGuid& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FColor& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}


bool FMatureJsonArray::GetValue(int32 Index, FLinearColor& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FRotator& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}
bool FMatureJsonArray::GetValue(int32 Index, FTransform& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FVector& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FMatureJsonValue& Value)const
{
	Value = GetValue(Index);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FMatureJsonObject& Value)const
{
	Value = GetValue(Index).ToObject(true);
	return true;
}

bool FMatureJsonArray::GetValue(int32 Index, FMatureJsonArray& Value)const
{
	Value = GetValue(Index).ToArray(true);
	return true;
}

FMatureJsonValue FMatureJsonArray::GetValue(int32 Index)const {
	if (Index < 0 || Size() <= Index)return FMatureJsonValue();
	return FMatureJsonValue(Document(), List()[Index]);
}

FMatureJsonObject FMatureJsonArray::GetObject( int32 Index) const {
	FMatureJsonObject value;
	GetValue(Index, value);
	return value;
}

FMatureJsonArray   FMatureJsonArray::GetArray( int32 Index) const {
	FMatureJsonArray value;
	GetValue(Index, value);
	return value;
}

FMatureJsonArray& FMatureJsonArray::Remove(unsigned int Index, unsigned int num)
{
	if (List().Size() <= Index || num==0)return *this;
	unsigned int idx = 0;
	mature::Array::ConstValueIterator begin = List().End();
	mature::Array::ConstValueIterator end = List().Begin();
	//mature::Array::ConstValueIterator it = List().Begin();
	for (; end != List().End(); idx++, end++) {
		if (idx == Index) {
			begin = end;
		}
		else if ((Index + num)<=idx) {
			break;
		}
	}
	List().Erase(begin,end);
	return *this;
}

FMatureJsonArray& FMatureJsonArray::operator=(const FMatureJsonArray& rhs) {
	ListPtr = rhs.ListPtr;
	return *this;
}

TSharedPtr<mature::Document> FMatureJsonArray::Document() {
	return ListPtr->Document;
}
TSharedPtr<mature::Document> FMatureJsonArray::Document()const {
	return ListPtr->Document;
}
inline mature::Array& FMatureJsonArray::List() {
	return ListPtr->List;
}
inline mature::Array& FMatureJsonArray::List()const {
	return ListPtr->List;
}
inline mature::Allocator& FMatureJsonArray::GetAllocator() {
	return ListPtr->Document->GetAllocator();
}
inline mature::Allocator& FMatureJsonArray::GetAllocator()const {
	return ListPtr->Document->GetAllocator();
}




FMatureJsonArrayIterator::FMatureJsonArrayIterator()
	: ListPtr(nullptr), Iterator(0)
{
}

FMatureJsonArrayIterator::FMatureJsonArrayIterator(const FMatureJsonArray& Value)
	: ListPtr(Value.ListPtr), Iterator(0)
{
}

FMatureJsonArrayIterator& FMatureJsonArrayIterator::Begin() {
	Iterator = 0;
	return *this;
}
FMatureJsonArrayIterator& FMatureJsonArrayIterator::End() {
	if (nullptr != ListPtr)
		Iterator = ListPtr->Size();
	return *this;
}

bool FMatureJsonArrayIterator::IsValid()const {
	if (nullptr == ListPtr)return false;
	if (Iterator < 0 || ListPtr->Size()<= Iterator)return false;
	return true;
}

void FMatureJsonArrayIterator::Next(int step) {
	Iterator = Iterator + step;
}

int FMatureJsonArrayIterator::Index() {
	return Iterator;
}

FMatureJsonValue FMatureJsonArrayIterator::Value() {
	return FMatureJsonValue(ListPtr->Document, ListPtr->List[Iterator]);
}

int FMatureJsonArrayIterator::Index() const {
	return Iterator;
}

FMatureJsonValue FMatureJsonArrayIterator::Value() const {
	return FMatureJsonValue(ListPtr->Document, ListPtr->List[Iterator]);
}

FMatureJsonArrayIterator& FMatureJsonArrayIterator::operator++() {
	Iterator++;
	return *this;
}

FMatureJsonArrayIterator& FMatureJsonArrayIterator::operator--() {
	Iterator--;
	return *this;
}

FMatureJsonArrayIterator& FMatureJsonArrayIterator::operator++(int) {
	++Iterator;
	return *this;
}
FMatureJsonArrayIterator& FMatureJsonArrayIterator::operator--(int) {
	--Iterator;
	return *this;
}

FMatureJsonArrayIterator& FMatureJsonArrayIterator::operator=(const FMatureJsonArray& Value) {
	ListPtr = Value.ListPtr;
	Iterator = 0;
	return *this;
}

FMatureJsonArrayIterator& FMatureJsonArrayIterator::operator=(const FMatureJsonArrayIterator& Value) {
	ListPtr = Value.ListPtr;
	Iterator = Value.Iterator;
	return *this;
}
