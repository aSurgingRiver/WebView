// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "json_cast.h"
#include "MatureJsonArray.generated.h"

typedef struct FMatureJsonObject FMatureJsonObject;
typedef struct FMatureJsonValue FMatureJsonValue;

USTRUCT(BlueprintType, meta = (DisplayName = "Mature JSON|Array"))
struct MATUREJSON_API FMatureJsonArray
{
	GENERATED_USTRUCT_BODY()
public:
	FMatureJsonArray();
	FMatureJsonArray(const TSharedPtr<mature::Document>& Doc, const mature::Array& );
	FMatureJsonArray(const TSharedPtr<mature::Document>& Doc, const mature::Array&&);
	FMatureJsonArray(const FMatureJsonArray& rhs);

public:

	// Get the number of items in this list.
	int32 Size() const;
	// Check is null in this list.
	bool IsEmpty() const;
	//
	bool HasIndex(const int index) const;
	// Clear the items in this list.
	void Clear();
	// Append a JSON array to this list.
	FMatureJsonArray& Append(const FMatureJsonArray& List);
	// Append an array of JSON values to this list.
	FMatureJsonArray& Append(const TArray<FMatureJsonValue>& Value);

	// Add a boolean to this list.
	FMatureJsonArray& AddValue( bool Value );
	// Add a float to this list.
	FMatureJsonArray& AddValue( float Value );
	// Add an integer to this list.
	FMatureJsonArray& AddValue( int32 Value );
	// Add a number to this list.
	FMatureJsonArray& AddValue( double Value );
	// Add a string to this list.
	FMatureJsonArray& AddValue( const TCHAR* Value);
	// Add a string to this list.
	FMatureJsonArray& AddValue( const FString& Value );
	// Add a date/time to this list.
	FMatureJsonArray& AddValue( const FDateTime& Value );
	// Add a GUID to this list.
	FMatureJsonArray& AddValue( const FGuid& Value );
	// Add a color to this list.
	FMatureJsonArray& AddValue( const FColor& Value );
	// Add a color to this list.
	FMatureJsonArray& AddValue( const FLinearColor& Value);
	// Add a color to this list.
	FMatureJsonArray& AddValue( const FRotator& Value);
	// Add a color to this list.
	FMatureJsonArray& AddValue( const FTransform& Value);
	// Set an item as a vector.
	FMatureJsonArray& AddValue( const FVector& Value);
	// Add a JSON value to this list.
	FMatureJsonArray& AddValue( const FMatureJsonValue& Value );
	// Add a JSON object to this list.
	FMatureJsonArray& AddValue( const FMatureJsonObject& Value );
	// Add a JSON array to this list.
	FMatureJsonArray& AddValue( const FMatureJsonArray& Value );
	// Add an array of JSON values to this list.
	FMatureJsonArray& AddValue( const TArray<FMatureJsonValue>& Value );


	// Set an item as a boolean.
	FMatureJsonArray& AddValue(const TArray<bool>& Value);
	// Set an item as a float.
	FMatureJsonArray& AddValue(const TArray<float>& Value);
	// Set an item as an integer.
	FMatureJsonArray& AddValue(const TArray<int32>& Value);
	// Set an item as a number.
	FMatureJsonArray& AddValue(const TArray<double>& Value);
	// Set an item as a string.
	FMatureJsonArray& AddValue(const TArray<FString>& Value);
	// Set an item as a date/time.
	FMatureJsonArray& AddValue(const TArray<FDateTime>& Value);
	// Set an item as a GUID.
	FMatureJsonArray& AddValue(const TArray<FGuid>& Value);
	// Set an item as a color.
	FMatureJsonArray& AddValue(const TArray<FColor>& Value);
	// Set an item as a linear color.
	FMatureJsonArray& AddValue(const TArray<FLinearColor>& Value);
	// Set an item as a rotator.
	FMatureJsonArray& AddValue(const TArray<FRotator>& Value);
	// Set an item as a transform.
	FMatureJsonArray& AddValue(const TArray<FTransform>& Value);
	// Set an item as a vector.
	FMatureJsonArray& AddValue(const TArray<FVector>& Value);
	// Add a null value to this list
	FMatureJsonValue AddValue() const;
	// Add a null value to this list
	FMatureJsonObject AddObject();
	// Add a null value to this list
	FMatureJsonArray AddArray();
	// Set an item as a boolean.
	FMatureJsonArray AddArray(const TArray<bool>& Value);
	// Set an item as a float.
	FMatureJsonArray AddArray(const TArray<float>& Value);
	// Set an item as an integer.
	FMatureJsonArray AddArray(const TArray<int32>& Value);
	// Set an item as a number.
	FMatureJsonArray AddArray(const TArray<double>& Value);
	// Set an item as a string.
	FMatureJsonArray AddArray(const TArray<FString>& Value);
	// Set an item as a date/time.
	FMatureJsonArray AddArray(const TArray<FDateTime>& Value);
	// Set an item as a GUID.
	FMatureJsonArray AddArray(const TArray<FGuid>& Value);
	// Set an item as a color.
	FMatureJsonArray AddArray(const TArray<FColor>& Value);
	// Set an item as a linear color.
	FMatureJsonArray AddArray(const TArray<FLinearColor>& Value);
	// Set an item as a rotator.
	FMatureJsonArray AddArray(const TArray<FRotator>& Value);
	// Set an item as a transform.
	FMatureJsonArray AddArray(const TArray<FTransform>& Value);
	// Set an item as a vector.
	FMatureJsonArray AddArray(const TArray<FVector>& Value);
	// Set an item as a vector.
	FMatureJsonArray& MergeList(const FMatureJsonArray&);


	// Set an item as a boolean.
	FMatureJsonValue SetValue( int32 Index);
	// Set an item as a boolean.
	FMatureJsonArray SetArray(int32 Index);
	// Set an item as a boolean.
	FMatureJsonObject SetObject(int32 Index);
	// Set an item as a boolean.
	FMatureJsonArray& SetValue( int32 Index, bool Value );
	// Set an item as a float.
	FMatureJsonArray& SetValue( int32 Index, float Value );
	// Set an item as an integer.
	FMatureJsonArray& SetValue( int32 Index, int32 Value );
	// Set an item as a number.
	FMatureJsonArray& SetValue( int32 Index, double Value );
	// Set an item as a string.
	FMatureJsonArray& SetValue(int32 Index, const TCHAR* Value);
	// Set an item as a string.
	FMatureJsonArray& SetValue( int32 Index, const FString& Value );
	// Set an item as a date/time.
	FMatureJsonArray& SetValue( int32 Index, const FDateTime& Value );
	// Set an item as a GUID.
	FMatureJsonArray& SetValue( int32 Index, const FGuid& Value );
	// Set an item as a color.
	FMatureJsonArray& SetValue( int32 Index, const FColor& Value );
	// Set an item as a linear color.
	FMatureJsonArray& SetValue( int32 Index, const FLinearColor& Value );
	// Set an item as a rotator.
	FMatureJsonArray& SetValue( int32 Index, const FRotator& Value );
	// Set an item as a transform.
	FMatureJsonArray& SetValue( int32 Index, const FTransform& Value );
	// Set an item as a vector.
	FMatureJsonArray& SetValue( int32 Index, const FVector& Value );
	// Set an item as a JSON value.
	FMatureJsonArray& SetValue( int32 Index, const FMatureJsonValue& Value );
	// Set an item as a JSON object.
	FMatureJsonArray& SetValue( int32 Index, const FMatureJsonObject& Value );
	// Set an item as a JSON array.
	FMatureJsonArray& SetValue( int32 Index, const FMatureJsonArray& Value );
	
	// Set an item as an array of JSON values.
	FMatureJsonArray& SetValue( int32 Index, const TArray<FMatureJsonValue>& Value );
	// Set an item as a map of JSON values.
	FMatureJsonArray& SetValue( int32 Index, const TMap<FString, FMatureJsonValue>& Value );

	// Get an item as a boolean.
	bool GetValue(int32 Index, bool& Value) const;
	// Get an item as a float.
	bool GetValue(int32 Index, float& Value)const;
	// Get an item as an integer.
	bool GetValue(int32 Index, int32& Value)const;
	// Get an item as a number.
	bool GetValue(int32 Index, double& Value)const;
	// Get an item as a string.
	bool GetValue(int32 Index, FString& Value)const;
	// Get an item as a date/time.
	bool GetValue(int32 Index, FDateTime& Value)const;
	// Get an item as a GUID.
	bool GetValue(int32 Index, FGuid& Value)const;
	// Get an item as a color.
	bool GetValue(int32 Index, FColor& Value)const;
	// Get an item as a linear color.
	bool GetValue(int32 Index, FLinearColor& Value)const;
	// Get an item as a rotator.
	bool GetValue(int32 Index, FRotator& Value)const;
	// Get an item as a transform.
	bool GetValue(int32 Index, FTransform& Value)const;
	// Get an item as a vector.
	bool GetValue(int32 Index, FVector& Value)const;
	// Get an item as a JSON value.
	bool GetValue(int32 Index, FMatureJsonValue& Value)const;
	// Get an item as a JSON object.
	bool GetValue(int32 Index, FMatureJsonObject& Value)const;
	// Get an item as a JSON array.
	bool GetValue(int32 Index, FMatureJsonArray& Value)const;

	//FMatureJsonValue  ToValue(int32 Index) const;
	FMatureJsonValue  GetValue(int32 Index) const;
	FMatureJsonObject GetObject(int32 Index) const;
	FMatureJsonArray  GetArray(int32 Index) const;

	// Remove an item from this list.
	FMatureJsonArray& Remove(unsigned int Index,unsigned int num );

	FMatureJsonArray& operator=(const FMatureJsonArray& Value);
	TSharedPtr<mature::Document> Document();
	TSharedPtr<mature::Document> Document()const;
protected:

	class ListWrap {
	public:
		ListWrap();
		ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array& Ref);
		ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array&& Ref);
		int Size();
	private:
		TSharedPtr<mature::Document> Document;
		mature::Array List;
		friend struct FMatureJsonArray;
		friend struct FMatureJsonArrayIterator;
	};
	TSharedPtr<ListWrap> ListPtr;
	inline mature::Array& List();
	inline mature::Array& List()const;
	inline mature::Allocator& GetAllocator();
	inline mature::Allocator& GetAllocator()const;
	//TSharedPtr<mature::Document> Document;
	//mature::Array ArrayRef;

private:
	friend struct FMatureJsonObject;
	friend struct FMatureJsonValue;
	friend struct FMatureJsonArrayIterator;
};

USTRUCT(BlueprintType, meta = (DisplayName = "Mature JSON|Object Iterator"))
struct MATUREJSON_API FMatureJsonArrayIterator {
	GENERATED_USTRUCT_BODY()
public:

	FMatureJsonArrayIterator();
	FMatureJsonArrayIterator(const FMatureJsonArray& Value);

	FMatureJsonArrayIterator& Begin();
	FMatureJsonArrayIterator& End();

	bool IsValid()const;
	void Next(int step = 1);

	int Index();
	FMatureJsonValue Value();
	int Index() const;
	FMatureJsonValue Value()const;

	FMatureJsonArrayIterator& operator++();
	FMatureJsonArrayIterator& operator--();
	FMatureJsonArrayIterator& operator++(int);
	FMatureJsonArrayIterator& operator--(int);
	FMatureJsonArrayIterator& operator=(const FMatureJsonArray& Value);
	FMatureJsonArrayIterator& operator=(const FMatureJsonArrayIterator& Value);

private:
	TSharedPtr<FMatureJsonArray::ListWrap> ListPtr;
	int Iterator;
};
