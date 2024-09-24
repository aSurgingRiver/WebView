// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonList.h"
#include "MatureJsonValueHelpers.generated.h"

UCLASS()
class MATUREJSON_API UMatureJsonValueHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Parse a JSON string.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool Parse(UPARAM(ref) FMatureJsonValue& JValue,const FString& Text );


	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool ParseFile(UPARAM(ref) FMatureJsonValue& JValue, const FString& filepath);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FString SaveString(UPARAM(ref) FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool SaveFile(UPARAM(ref) FMatureJsonValue& JValue, const FString& filepath);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static int Size(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsEmpty(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue& Clear(UPARAM(ref) FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static EMatureJsonType Type(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool IsObject(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool IsArray(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool IsString(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool IsNumber(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool IsNull(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool IsBool(UPARAM(ref)const FMatureJsonValue& JValue);


	// Convert a boolean to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Boolean", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonValue FromBoolean(bool Value);
	// Convert a float to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Float", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonValue FromFloat(float Value);
	// Convert an integer to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Integer", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonValue FromInteger(int32 Value);
	// Convert a string to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From String", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonValue FromString(const FString& Value);

	// Convert a date/time to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Date/Time", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FMatureJsonValue FromDateTime(const FDateTime& Value);
	// Convert a GUID to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From GUID", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FMatureJsonValue FromGuid(const FGuid& Value);

	// Convert a color to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Color", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FMatureJsonValue FromColor(const FColor& Value);
	// Convert a linear color to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Linear Color", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FMatureJsonValue FromLinearColor(const FLinearColor& Value);

	// Convert a rotator to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Rotator", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FMatureJsonValue FromRotator(const FRotator& Value);
	// Convert a transform to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Transform", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FMatureJsonValue FromTransform(const FTransform& Value);
	// Convert a vector to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Vector", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FMatureJsonValue FromVector(const FVector& Value);

	// Convert a JSON object to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Object", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonValue FromObject(const FMatureJsonObject& Value);
	// Convert a JSON array to a JSON value.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From List", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonValue FromList(const FMatureJsonList& Value);
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From List", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonValue FromValue(const FMatureJsonValue& Value);

	// Convert a JSON value valueto a boolean.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Boolean", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static bool ToBoolean(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a float.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Float", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static float ToFloat(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto an integer.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Integer", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static int32 ToInteger(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a string.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FString ToString(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a date/time.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Date/Time", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FDateTime ToDateTime(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a GUID.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GUID", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FGuid ToGuid(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a color.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Color", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FColor ToColor(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Linear Color", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FLinearColor ToLinearColor(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Linear Color", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FRotator ToRotator(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Linear Color", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FVector ToVector(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Linear Color", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json|Engine")
		static FTransform ToTransform(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a JSON object.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Object", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonObject ToObject(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a JSON array.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To List", CompactNodeTitle = "->", BlueprintAutocast), Category = "Mature Json")
		static FMatureJsonList ToList(const FMatureJsonValue& JValue);


};
