// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "json_cast.hpp"
#include "MatureJsonList.generated.h"

typedef struct FMatureJsonObject FMatureJsonObject;
typedef struct FMatureJsonValue FMatureJsonValue;

USTRUCT(BlueprintType, meta = (DisplayName = "Mature JSON|List"))
struct MATUREJSON_API FMatureJsonList
{
	GENERATED_USTRUCT_BODY()
public:
	FMatureJsonList();
	FMatureJsonList(const TSharedPtr<mature::Document>& Doc, const mature::Array& );
	FMatureJsonList(const TSharedPtr<mature::Document>& Doc, const mature::Array&&);
	FMatureJsonList(const FMatureJsonList& rhs);

public:

	// Get the number of items in this list.
	int32 Size() const;
	// Check is null in this list.
	bool IsEmpty() const;
	// Clear the items in this list.
	void Clear();
	// Append a JSON array to this list.
	FMatureJsonList& Append(const FMatureJsonList& List);
	// Append an array of JSON values to this list.
	FMatureJsonList& Append(const TArray<FMatureJsonValue>& Value);

	// Add a boolean to this list.
	FMatureJsonList& AddValue( bool Value );
	// Add a float to this list.
	FMatureJsonList& AddValue( float Value );
	// Add an integer to this list.
	FMatureJsonList& AddValue( int32 Value );
	// Add a number to this list.
	FMatureJsonList& AddValue( double Value );
	// Add a string to this list.
	FMatureJsonList& AddValue( const TCHAR* Value);
	// Add a string to this list.
	FMatureJsonList& AddValue( const FString& Value );
	// Add a date/time to this list.
	FMatureJsonList& AddValue( const FDateTime& Value );
	// Add a GUID to this list.
	FMatureJsonList& AddValue( const FGuid& Value );
	// Add a color to this list.
	FMatureJsonList& AddValue( const FColor& Value );
	// Add a color to this list.
	FMatureJsonList& AddValue( const FLinearColor& Value);
	// Add a color to this list.
	FMatureJsonList& AddValue( const FRotator& Value);
	// Add a color to this list.
	FMatureJsonList& AddValue( const FTransform& Value);
	// Set an item as a vector.
	FMatureJsonList& AddValue( const FVector& Value);
	// Add a JSON value to this list.
	FMatureJsonList& AddValue( const FMatureJsonValue& Value );
	// Add a JSON object to this list.
	FMatureJsonList& AddValue( const FMatureJsonObject& Value );
	// Add a JSON array to this list.
	FMatureJsonList& AddValue( const FMatureJsonList& Value );
	// Add an array of JSON values to this list.
	FMatureJsonList& AddValue( const TArray<FMatureJsonValue>& Value );


	// Set an item as a boolean.
	FMatureJsonList& AddValue(const TArray<bool>& Value);
	// Set an item as a float.
	FMatureJsonList& AddValue(const TArray<float>& Value);
	// Set an item as an integer.
	FMatureJsonList& AddValue(const TArray<int32>& Value);
	// Set an item as a number.
	FMatureJsonList& AddValue(const TArray<double>& Value);
	// Set an item as a string.
	FMatureJsonList& AddValue(const TArray<FString>& Value);
	// Set an item as a date/time.
	FMatureJsonList& AddValue(const TArray<FDateTime>& Value);
	// Set an item as a GUID.
	FMatureJsonList& AddValue(const TArray<FGuid>& Value);
	// Set an item as a color.
	FMatureJsonList& AddValue(const TArray<FColor>& Value);
	// Set an item as a linear color.
	FMatureJsonList& AddValue(const TArray<FLinearColor>& Value);
	// Set an item as a rotator.
	FMatureJsonList& AddValue(const TArray<FRotator>& Value);
	// Set an item as a transform.
	FMatureJsonList& AddValue(const TArray<FTransform>& Value);
	// Set an item as a vector.
	FMatureJsonList& AddValue(const TArray<FVector>& Value);
	// Add a null value to this list
	FMatureJsonValue AddValue() const;
	// Add a null value to this list
	FMatureJsonObject AddObject();
	// Add a null value to this list
	FMatureJsonList AddList();
	// Set an item as a boolean.
	FMatureJsonList AddList(const TArray<bool>& Value);
	// Set an item as a float.
	FMatureJsonList AddList(const TArray<float>& Value);
	// Set an item as an integer.
	FMatureJsonList AddList(const TArray<int32>& Value);
	// Set an item as a number.
	FMatureJsonList AddList(const TArray<double>& Value);
	// Set an item as a string.
	FMatureJsonList AddList(const TArray<FString>& Value);
	// Set an item as a date/time.
	FMatureJsonList AddList(const TArray<FDateTime>& Value);
	// Set an item as a GUID.
	FMatureJsonList AddList(const TArray<FGuid>& Value);
	// Set an item as a color.
	FMatureJsonList AddList(const TArray<FColor>& Value);
	// Set an item as a linear color.
	FMatureJsonList AddList(const TArray<FLinearColor>& Value);
	// Set an item as a rotator.
	FMatureJsonList AddList(const TArray<FRotator>& Value);
	// Set an item as a transform.
	FMatureJsonList AddList(const TArray<FTransform>& Value);
	// Set an item as a vector.
	FMatureJsonList AddList(const TArray<FVector>& Value);

	// Set an item as a vector.
	FMatureJsonList& MergeList(const FMatureJsonList&);


	// Set an item as a boolean.
	FMatureJsonList& SetValue( int32 Index);
	// Set an item as a boolean.
	FMatureJsonList& SetValue( int32 Index, bool Value );
	// Set an item as a float.
	FMatureJsonList& SetValue( int32 Index, float Value );
	// Set an item as an integer.
	FMatureJsonList& SetValue( int32 Index, int32 Value );
	// Set an item as a number.
	FMatureJsonList& SetValue( int32 Index, double Value );
	// Set an item as a string.
	FMatureJsonList& SetValue(int32 Index, const TCHAR* Value);
	// Set an item as a string.
	FMatureJsonList& SetValue( int32 Index, const FString& Value );
	// Set an item as a date/time.
	FMatureJsonList& SetValue( int32 Index, const FDateTime& Value );
	// Set an item as a GUID.
	FMatureJsonList& SetValue( int32 Index, const FGuid& Value );
	// Set an item as a color.
	FMatureJsonList& SetValue( int32 Index, const FColor& Value );
	// Set an item as a linear color.
	FMatureJsonList& SetValue( int32 Index, const FLinearColor& Value );
	// Set an item as a rotator.
	FMatureJsonList& SetValue( int32 Index, const FRotator& Value );
	// Set an item as a transform.
	FMatureJsonList& SetValue( int32 Index, const FTransform& Value );
	// Set an item as a vector.
	FMatureJsonList& SetValue( int32 Index, const FVector& Value );
	// Set an item as a JSON value.
	FMatureJsonList& SetValue( int32 Index, const FMatureJsonValue& Value );
	// Set an item as a JSON object.
	FMatureJsonList& SetValue( int32 Index, const FMatureJsonObject& Value );
	// Set an item as a JSON array.
	FMatureJsonList& SetValue( int32 Index, const FMatureJsonList& Value );
	
	// Set an item as an array of JSON values.
	FMatureJsonList& SetValue( int32 Index, const TArray<FMatureJsonValue>& Value );
	// Set an item as a map of JSON values.
	FMatureJsonList& SetValue( int32 Index, const TMap<FString, FMatureJsonValue>& Value );

	FMatureJsonValue GetValue(int Index) const;
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
	bool GetValue(int32 Index, FMatureJsonList& Value)const;

	FMatureJsonValue  ToValue(int32 Index) const;
	FMatureJsonObject ToObject(int32 Index) const;
	FMatureJsonList   ToList(int32 Index) const;

	// Remove an item from this list.
	FMatureJsonList& Remove(unsigned int Index,unsigned int num );

	FMatureJsonList& operator=(const FMatureJsonList& Value);
	TSharedPtr<mature::Document> Document();
	TSharedPtr<mature::Document> Document()const;
protected:

	class ListWrap {
	public:
		ListWrap();
		ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array& Ref);
		ListWrap(TSharedPtr<mature::Document> Doc, const mature::Array&& Ref);
	private:
		TSharedPtr<mature::Document> Document;
		mature::Array List;
		friend struct FMatureJsonList;
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
};
