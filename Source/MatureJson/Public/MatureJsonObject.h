// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Serialization/JsonTypes.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "UObject/StructOnScope.h"
#include "MatureJsonValue.h"
#include "json_cast.h"
#include "MatureJsonObject.generated.h"

typedef struct FMatureJsonArray FMatureJsonArray;


USTRUCT(BlueprintType, meta = (DisplayName = "Mature JSON|Object"))
struct MATUREJSON_API FMatureJsonObject
{
	GENERATED_USTRUCT_BODY()

public:
	FMatureJsonObject();
	FMatureJsonObject(TSharedPtr<mature::Document> Doc, const mature::Object&);
	FMatureJsonObject(TSharedPtr<mature::Document> Doc, const mature::Object&&);
	FMatureJsonObject(const FMatureJsonObject& rhs);
	FMatureJsonObject(const FMatureJsonObject&& rhs);
public:

	FMatureJsonValue GetKey(const FString& key) const ;

	//FMatureJsonObject& SetValue( const FString& key, const FMatureJsonValue& Value);
	FMatureJsonObject& SetValue( const FLinearColor& Value );
	FMatureJsonObject& SetValue( const FRotator& Value );
	FMatureJsonObject& SetValue( const FTransform& Value );
	FMatureJsonObject& SetValue( const FVector& Value );
	FMatureJsonObject& SetValue( const FMatureJsonObject& Value);
	FMatureJsonObject& SetValue( const TMap<FString, FMatureJsonValue>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, bool>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, float>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, double>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, int32>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FString>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FDateTime>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FGuid>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FColor>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FLinearColor>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FRotator>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FTransform>& Value );
	FMatureJsonObject& SetValue( const TMap<FString, FVector>& Value );

	// Get the number of properties in this object.
	int32 Size() const;
	// Check is empty in this object.
	bool IsEmpty()const;
	// Clear the properties in this object.
	void Clear();
	
	// Check if this object has a property.
	bool HasKey( const FString& Key ) const;
	// Remove a property from this object.
	void RemoveKey( const FString& Key );

	// Add a JSON object to this object.
	FMatureJsonObject& AddValue(const FMatureJsonObject& Object);
	// Add a map of booleans to this object.
	FMatureJsonObject& AddValue(const TMap<FString, bool>& Map);
	// Add a map of floats to this object.
	FMatureJsonObject& AddValue(const TMap<FString, float>& Map);
	// Add a map of integers to this object.
	FMatureJsonObject& AddValue(const TMap<FString, int32>& Map);
	// Add a map of numbers to this object.
	FMatureJsonObject& AddValue(const TMap<FString, double>& Map);
	// Add a map of strings to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FString>& Map);

	// Add a map of date/times to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FDateTime>& Map);
	// Add a map of GUIDs to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FGuid>& Map);

	// Add a map of colors to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FColor>& Map);
	// Add a map of linear colors to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FLinearColor>& Map);

	// Add a map of rotators to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FRotator>& Map);
	// Add a map of transforms to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FTransform>& Map);
	// Add a map of vectors to this object.
	FMatureJsonObject& AddValue(const TMap<FString, FVector>& Map);
	// 
	FMatureJsonObject& AddValue(const TMap<FString, FMatureJsonValue>& Map);

	// Set a property as a boolean.
	FMatureJsonObject& SetValue(const FString& Key, bool Value);
	// Set a property as a float.
	FMatureJsonObject& SetValue(const FString& Key, float Value);
	// Set a property as an integer.
	FMatureJsonObject& SetValue(const FString& Key, int32 Value);
	// Set a property as a number.
	FMatureJsonObject& SetValue(const FString& Key, double Value);
	// Set a property as a string.
	FMatureJsonObject& SetValue(const FString& Key, const TCHAR* Value);
	// Set a property as a string.
	FMatureJsonObject& SetValue(const FString& Key, const FString& Value);
	// Set a property as a date/time.
	FMatureJsonObject& SetValue(const FString& Key, const FDateTime& Value);
	// Set a property as a GUID.
	FMatureJsonObject& SetValue(const FString& Key, const FGuid& Value);
	// Set a property as a color.
	FMatureJsonObject& SetValue(const FString& Key, const FColor& Value);
	// Set a property as a linear color.
	FMatureJsonObject& SetValue(const FString& Key, const FLinearColor& Value);
	// Set a property as a rotator.
	FMatureJsonObject& SetValue(const FString& Key, const FRotator& Value);
	// Set a property as a transform.
	FMatureJsonObject& SetValue(const FString& Key, const FTransform& Value);
	// Set a property as a vector.
	FMatureJsonObject& SetValue(const FString& Key, const FVector& Value);
	// Set a property as a JSON value.
	FMatureJsonObject& SetValue(const FString& Key, const FMatureJsonValue& Value);
	// Set a property as a JSON object.
	FMatureJsonObject& SetValue(const FString& Key, const FMatureJsonObject& Value);
	// Set a property as a JSON array.
	FMatureJsonObject& SetValue(const FString& Key, const FMatureJsonArray& Value);
	// Set a property as an array of JSON values.
	FMatureJsonObject& SetValue(const FString& Key, const TArray<FMatureJsonValue>& Value);
	// Set a property as a map of JSON values.
	FMatureJsonObject& SetValue(const FString& Key, const TMap<FString, FMatureJsonValue>& Value);
	// Set a property as a list.
	FMatureJsonArray SetArray(const FString& Key);
	// Set a property as a object.
	FMatureJsonObject SetObject(const FString& Key);
	//
	FMatureJsonValue SetValue(const FString& key);

	TArray<FString> GetKeys() const;

	void GetValue(FLinearColor& value);
	void GetValue(FRotator& value);
	void GetValue(FTransform& value);
	void GetValue(FVector& value);
	bool GetValue(const FString& Key, bool& ) const;
	bool GetValue(const FString& Key, float&) const;
	bool GetValue(const FString& Key, uint32&) const;
	bool GetValue(const FString& Key, int32&) const;
	bool GetValue(const FString& Key, uint64&) const;
	bool GetValue(const FString& Key, int64&) const;
	bool GetValue(const FString& Key, double&) const;
	bool GetValue(const FString& Key, FString&) const;
	bool GetValue(const FString& Key, FGuid&) const;
	bool GetValue(const FString& Key, FColor&) const;
	bool GetValue(const FString& Key, FDateTime&) const;
	bool GetValue(const FString& Key, FLinearColor&) const;
	bool GetValue(const FString& Key, FRotator&) const;
	bool GetValue(const FString& Key, FTransform&) const;
	bool GetValue(const FString& Key, FVector&) const;
	bool GetValue(const FString& Key, FMatureJsonValue&) const;
	bool GetValue(const FString& Key, FMatureJsonObject&) const;
	bool GetValue(const FString& Key, FMatureJsonArray&) const;

	FMatureJsonValue  GetValue(const FString& Key) const;
	FMatureJsonObject GetObject(const FString& Key) const;
	FMatureJsonArray  GetArray(const FString& Key) const;

	FMatureJsonObject& operator=(const FMatureJsonObject& Value);
	TSharedPtr<mature::Document> Document();
	TSharedPtr<mature::Document> Document()const;
protected:
	class ObjectWrap {
	public:
		ObjectWrap();
		//ObjectWrap(TSharedPtr<mature::Document> Doc);
		ObjectWrap(TSharedPtr<mature::Document> Doc, const mature::Object& Ref);
		ObjectWrap(TSharedPtr<mature::Document> Doc, const mature::Object&& Ref);
		mature::MemberIterator Begin();
		mature::MemberIterator End();

	private:
		TSharedPtr<mature::Document> Document;
		mature::Object Object;
		friend struct FMatureJsonObject;
		friend struct FMatureJsonObjectIterator;
	};
	TSharedPtr<ObjectWrap> ObjectPtr;
	FMatureJsonValue AddKey(const FString& key) ;
	inline mature::Object& Object();
	inline mature::Object& Object() const;
	inline mature::Allocator& GetAllocator();
	inline mature::Allocator& GetAllocator()const;

private:
	friend struct FMatureJsonArray;
	friend struct FMatureJsonValue;
	friend struct FMatureJsonObjectIterator;
};




USTRUCT(BlueprintType, meta = (DisplayName = "Mature JSON|Object Iterator"))
struct MATUREJSON_API FMatureJsonObjectIterator {
	GENERATED_USTRUCT_BODY()
public:
	
	FMatureJsonObjectIterator();
	FMatureJsonObjectIterator(const FMatureJsonObject& Value);

	FMatureJsonObjectIterator& Begin();
	FMatureJsonObjectIterator& End();


	bool IsValid()const;
	void Next(int step = 1);

	FString Key() ;
	FMatureJsonValue Value();
	FString Key() const;
	FMatureJsonValue Value()const;

	FMatureJsonObjectIterator& operator++();
	FMatureJsonObjectIterator& operator--();
	FMatureJsonObjectIterator& operator++(int);
	FMatureJsonObjectIterator& operator--(int);
	FMatureJsonObjectIterator& operator=(const FMatureJsonObject& Value);
	FMatureJsonObjectIterator& operator=(const FMatureJsonObjectIterator& Value);

private:
	TSharedPtr<FMatureJsonObject::ObjectWrap> ObjectPtr;
	mature::MemberIterator Iterator;
};
