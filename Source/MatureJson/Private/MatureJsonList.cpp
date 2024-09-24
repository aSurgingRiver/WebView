// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#include "MatureJsonList.h"
#include "MatureJsonEnums.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
//#include "MatureJsonHelpers.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Policies/PrettyJsonPrintPolicy.h"


FMatureJsonList::ListWrap::ListWrap()
	: Document(MakeShared<mature::Document>())
	, List(Document->SetArray().GetArray())
{
}

FMatureJsonList::ListWrap::ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array& Ref)
	: Document(Doc)
	, List(Ref)
{
}
FMatureJsonList::ListWrap::ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array&& Ref)
	: Document(Doc)
	, List(Ref)
{
}



FMatureJsonList::FMatureJsonList()
	: ListPtr(MakeShared<ListWrap>())
{
}
FMatureJsonList::FMatureJsonList(const TSharedPtr<mature::Document>& Doc,const mature::Array& a)
	: ListPtr(MakeShared<ListWrap>(Doc, a))
{
}
FMatureJsonList::FMatureJsonList(const TSharedPtr<mature::Document>& Doc, const mature::Array&& a)
	: ListPtr(MakeShared<ListWrap>(Doc, a))
{
}

FMatureJsonList::FMatureJsonList(const FMatureJsonList& rhs)
	: ListPtr(rhs.ListPtr)
{
}

int32 FMatureJsonList::Size() const
{
	return List().Size();
}

bool FMatureJsonList::IsEmpty() const
{
	return List().Empty();
}

void FMatureJsonList::Clear()
{
	List().Clear();
}

FMatureJsonList& FMatureJsonList::Append(const FMatureJsonList& List)
{
	auto it = List.List().Begin();
	for (; it != List.List().End(); it++) {
		AddValue().SetValue(*it);
	}
	return *this;
}

FMatureJsonList& FMatureJsonList::Append(const TArray<FMatureJsonValue>& Value) {
	for (auto& it : Value) {
		AddValue().SetValue(it);
	}
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( bool Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( float Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( int32 Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( double Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue(const TCHAR* Value)
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( const FString& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( const FDateTime& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( const FGuid& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( const FColor& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue(const FLinearColor& Value)
{
	AddValue().SetValue(Value);
	return *this;
} 
FMatureJsonList& FMatureJsonList::AddValue(const FRotator& Value)
{
	AddValue().SetValue(Value);
	return *this;
} 
FMatureJsonList& FMatureJsonList::AddValue(const FTransform& Value)
{
	AddValue().SetValue(Value);
	return *this;
} 
FMatureJsonList& FMatureJsonList::AddValue(const FVector& Value)
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( const FMatureJsonValue& Value )
{
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue(const FMatureJsonObject& Value) {
	AddValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( const FMatureJsonList& Value)
{
	auto NewList = AddValue().ToList();
	for (auto& it : Value.List()) {
		NewList.List().PushBack(it, GetAllocator());
	}
	return *this;
}

FMatureJsonList& FMatureJsonList::AddValue( const TArray<FMatureJsonValue>& Value )
{
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.List().PushBack(it.ValueRef(), GetAllocator());
	}
	return *this;
}

// Set an item as a boolean.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<bool>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a float.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<float>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as an integer.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<int32>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a number.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<double>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a string.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FString>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a date/time.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FDateTime>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a GUID.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FGuid>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a color.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FColor>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a linear color.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FLinearColor>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a rotator.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FRotator>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a transform.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FTransform>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}
// Set an item as a vector.
FMatureJsonList& FMatureJsonList::AddValue(const TArray<FVector>& Value) {
	for (auto& it : Value) {
		AddValue(it);
	}
	return *this;
}

FMatureJsonValue FMatureJsonList::AddValue()const {
	const int idx = List().Size();
	List().PushBack(mature::Value(), GetAllocator());
	return FMatureJsonValue(Document(), List()[idx]);
}

FMatureJsonObject FMatureJsonList::AddObject() {
	const int idx = List().Size();
	List().PushBack(mature::Value(), GetAllocator());
	return FMatureJsonValue(Document(), List()[idx]).ToObject();
}

FMatureJsonList FMatureJsonList::AddList() {
	const int idx = List().Size();
	List().PushBack(mature::Value(), GetAllocator());
	return FMatureJsonValue(Document(), List()[idx]).ToList();
}

// Set an item as a boolean.
FMatureJsonList FMatureJsonList::AddList(const TArray<bool>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}

// Set an item as a float.
FMatureJsonList FMatureJsonList::AddList(const TArray<float>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as an integer.
FMatureJsonList FMatureJsonList::AddList(const TArray<int32>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a number.
FMatureJsonList FMatureJsonList::AddList(const TArray<double>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a string.
FMatureJsonList FMatureJsonList::AddList(const TArray<FString>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a date/time.
FMatureJsonList FMatureJsonList::AddList(const TArray<FDateTime>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a GUID.
FMatureJsonList FMatureJsonList::AddList(const TArray<FGuid>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a color.
FMatureJsonList FMatureJsonList::AddList(const TArray<FColor>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a linear color.
FMatureJsonList FMatureJsonList::AddList(const TArray<FLinearColor>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a rotator.
FMatureJsonList FMatureJsonList::AddList(const TArray<FRotator>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a transform.
FMatureJsonList FMatureJsonList::AddList(const TArray<FTransform>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}
// Set an item as a vector.
FMatureJsonList FMatureJsonList::AddList(const TArray<FVector>& Value) {
	auto NewList = AddValue().ToList();
	for (auto& it : Value) {
		NewList.AddValue(it);
	}
	return NewList;
}


// Set an item as a vector.
FMatureJsonList& FMatureJsonList::MergeList(const FMatureJsonList& rhs) {
	int idx = 0;
	for (; idx < rhs.Size(); idx++) {
		AddValue(rhs.GetValue(idx));
	}
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue(int32 Index) {
	GetValue(Index).SetValue();
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, bool Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, float Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, int32 Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, double Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue(int32 Index, const TCHAR* Value) {
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const FString& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const FDateTime& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const FGuid& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const FColor& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}


FMatureJsonList& FMatureJsonList::SetValue(int32 Index, const FLinearColor& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue(int32 Index, const FRotator& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}
FMatureJsonList& FMatureJsonList::SetValue(int32 Index, const FTransform& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue(int32 Index, const FVector& Value)
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const FMatureJsonValue& Value )
{
	GetValue(Index).SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const FMatureJsonObject& Value )
{
	GetValue(Index).SetValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const FMatureJsonList& Value )
{
	GetValue(Index).SetValue().SetValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const TArray<FMatureJsonValue>& Value )
{
	GetValue(Index).SetValue().ToList().AddValue(Value);
	return *this;
}

FMatureJsonList& FMatureJsonList::SetValue( int32 Index, const TMap<FString, FMatureJsonValue>& Value )
{
	GetValue(Index).SetValue().ToObject().AddValue(Value);
	return *this;
}

FMatureJsonValue FMatureJsonList::GetValue(int Index)const {
	if (Index < 0)return FMatureJsonValue();
	if (Size() <= Index) {
		int l = Index;
		for (; Size() <= l; l--) {
			AddValue();
		}
	}
	return FMatureJsonValue(Document(), List()[Index]);
}


bool FMatureJsonList::GetValue(int32 Index, bool& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, float& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, int32& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, double& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FString& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FDateTime& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FGuid& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FColor& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}


bool FMatureJsonList::GetValue(int32 Index, FLinearColor& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FRotator& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}
bool FMatureJsonList::GetValue(int32 Index, FTransform& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FVector& Value)const
{
	if (Size() <= Index) return false;
	GetValue(Index).GetValue(Value);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FMatureJsonValue& Value)const
{
	Value = GetValue(Index);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FMatureJsonObject& Value)const
{
	Value = GetValue(Index).ToObject(true);
	return true;
}

bool FMatureJsonList::GetValue(int32 Index, FMatureJsonList& Value)const
{
	Value = GetValue(Index).ToList(true);
	return true;
}

FMatureJsonValue  FMatureJsonList::ToValue( int32 Index) const {
	FMatureJsonValue value;
	GetValue(Index, value);
	return value;
}

FMatureJsonObject FMatureJsonList::ToObject( int32 Index) const {
	FMatureJsonObject value;
	GetValue(Index, value);
	return value;
}

FMatureJsonList   FMatureJsonList::ToList( int32 Index) const {
	FMatureJsonList value;
	GetValue(Index, value);
	return value;
}


FMatureJsonList& FMatureJsonList::Remove(unsigned int Index, unsigned int num)
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

FMatureJsonList& FMatureJsonList::operator=(const FMatureJsonList& rhs) {
	ListPtr = rhs.ListPtr;
	return *this;
}

TSharedPtr<mature::Document> FMatureJsonList::Document() {
	return ListPtr->Document;
}
TSharedPtr<mature::Document> FMatureJsonList::Document()const {
	return ListPtr->Document;
}
inline mature::Array& FMatureJsonList::List() {
	return ListPtr->List;
}
inline mature::Array& FMatureJsonList::List()const {
	return ListPtr->List;
}
inline mature::Allocator& FMatureJsonList::GetAllocator() {
	return ListPtr->Document->GetAllocator();
}
inline mature::Allocator& FMatureJsonList::GetAllocator()const {
	return ListPtr->Document->GetAllocator();
}
