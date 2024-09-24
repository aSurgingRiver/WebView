// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "json_cast.hpp"
#include "MatureJsonEnums.h"
#include "MatureJsonValue.generated.h"

typedef struct FMatureJsonList FMatureJsonList;
typedef struct FMatureJsonObject FMatureJsonObject;

USTRUCT(BlueprintType, meta = (DisplayName = "Mature JSON|Value"))
struct MATUREJSON_API FMatureJsonValue
{
	GENERATED_USTRUCT_BODY()
public:

	FMatureJsonValue(/*const TSharedPtr<mature::Document>& Doc*/);
	FMatureJsonValue(const TSharedPtr<mature::Document>& Doc, mature::Value&);

	FMatureJsonValue(const FMatureJsonValue& Doc);
public:
	FMatureJsonValue& SetValue( );
	FMatureJsonValue& SetValue(const bool Value );
	FMatureJsonValue& SetValue(const float Value );
	FMatureJsonValue& SetValue(const double Value );
	FMatureJsonValue& SetValue(const int8 Value );
	FMatureJsonValue& SetValue(const uint8 Value );
	FMatureJsonValue& SetValue(const int16 Value );
	FMatureJsonValue& SetValue(const uint16 Value );
	FMatureJsonValue& SetValue(const int32 Value );
	FMatureJsonValue& SetValue(const uint32 Value );
	FMatureJsonValue& SetValue(const int64 Value );
	FMatureJsonValue& SetValue(const uint64 Value );
	FMatureJsonValue& SetValue(const TCHAR* Value);
	FMatureJsonValue& SetValue(const FString& Value );
	FMatureJsonValue& SetValue(const FDateTime& Value );
	FMatureJsonValue& SetValue(const FGuid& Value );
	FMatureJsonValue& SetValue(const FColor& Value );
	FMatureJsonValue& SetValue(const FTransform& Value);
	FMatureJsonValue& SetValue(const FVector& Value);
	FMatureJsonValue& SetValue(const FRotator& Value);
	FMatureJsonValue& SetValue(const FLinearColor& Value);
	FMatureJsonValue& SetValue(const FMatureJsonValue& Value);
	FMatureJsonValue& SetValue(const FMatureJsonObject& Value);
	FMatureJsonValue& SetValue(const FMatureJsonList& Value);
	
	EMatureJsonTypeNumber NumberType()const;
	// Get the JSON type of this value.
	EMatureJsonType GetType() const;
	int  Size()  const ;
	bool IsEmpty()  const;
	void Clear();

	// Convert this value to a boolean.
	bool ToBoolean() const;
	// Convert this value to a float.
	float ToFloat() const;
	// Convert this value to an integer.
	int32 ToInteger() const;
	// Convert this value to a number.
	double ToNumber() const;
	// Convert this value to a string.
	FString ToString() const;

	// Convert this value to a date/time.
	FDateTime ToDateTime() const;
	// Convert this value to a GUID.
	FGuid ToGuid() const;
	// Convert this value to a LinearColor.
	FLinearColor ToLinearColor() const;

	// Convert this value to a color.
	FColor ToColor() const;
	// Convert this value to a JSON object.
	FMatureJsonObject ToObject(bool check = false) const;
	// Convert this value to a JSON array.
	FMatureJsonList ToList(bool check = false) const;

	// Convert this value to a 32-bit signed integer.
	int32 ToInt32() const;
	// Convert this value to a 64-bit signed integer.
	int64 ToInt64() const;
	// Convert this value to a 32-bit unsigned integer.
	uint32 ToUInt32() const;
	// Convert this value to a 64-bit unsigned integer.
	uint64 ToUInt64() const;

	bool GetValue(bool& value) const;
	bool GetValue(float& value) const;
	bool GetValue(int32& value)const;
	bool GetValue(int64& value)const;
	bool GetValue(uint32& value)const;
	bool GetValue(uint64& value)const;
	bool GetValue(double& value)const;
	bool GetValue(FString& value)const;
	bool GetValue(FDateTime& value)const;
	bool GetValue(FGuid& value)const;
	bool GetValue(FColor& value)const;
	bool GetValue(FLinearColor& value)const;
	bool GetValue(FRotator& value)const;
	bool GetValue(FVector& value)const;
	bool GetValue(FTransform& value)const;

	TSharedPtr<mature::Document> Document();
	TSharedPtr<mature::Document> Document() const;
protected:
	class ValueWrap {
	public:
		ValueWrap();
		ValueWrap(TSharedPtr<mature::Document> Doc);
		ValueWrap(TSharedPtr<mature::Document> Doc, mature::Value& Ref);
		bool IsRoot();
		TSharedPtr<mature::Document> Document;
		mature::Value& ValueRef;
	};
	TSharedPtr<ValueWrap> ValueCache;

	inline mature::Value& ValueRef();
	mature::Value& ValueRef() const;

	inline mature::Allocator& GetAllocator();
	inline mature::Allocator& GetAllocator()const;
	//TSharedPtr<mature::Document> Document;
	//mature::Value ValueRef;
	FMatureJsonValue& SetValue(mature::Value& Value);
public:


	// Check if this value is a date time.
	bool IsDateTime() const;
	// Check if this value is a guid.
	bool IsGuid() const;

	// Check if this value is a COLOR.
	bool IsColor(FString hex_string) const;

	bool Parse(const FString& Text);
	bool ParseFile(const FString& FileName);

	FString SaveString()const;
	bool SaveFile(FString filename)const;
	FMatureJsonValue& operator=(const FMatureJsonValue& Value);

private:	
	friend struct FMatureJsonList;
	friend struct FMatureJsonObject;
};
