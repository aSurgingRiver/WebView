// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"
#include "MatureJsonValuePureHelpers.generated.h"

UCLASS()
class MATUREJSON_API UMatureJsonValuePureHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Parse a JSON string.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue Parse(const FString& Text);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FString SaveString(UPARAM(ref) FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static int Size(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool IsEmpty(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static EMatureJsonType Type(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool IsObject(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool IsArray(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool IsString(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool IsNumber(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool IsNull(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool IsBool(UPARAM(ref)const FMatureJsonValue& JValue);


	// Convert a boolean to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromBoolean(bool Value);
	// Convert a float to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromFloat(float Value);
	// Convert an integer to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromInteger(int32 Value);
	// Convert a string to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromString(const FString& Value);
	// Convert a date/time to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromDateTime(const FDateTime& Value);
	// Convert a GUID to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromGuid(const FGuid& Value);
	// Convert a color to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromColor(const FColor& Value);
	// Convert a linear color to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromLinearColor(const FLinearColor& Value);
	// Convert a rotator to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromRotator(const FRotator& Value);
	// Convert a transform to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromTransform(const FTransform& Value);
	// Convert a vector to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromVector(const FVector& Value);
	// Convert a JSON object to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromObject(const FMatureJsonObject& Value);
	// Convert a JSON array to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromArray(const FMatureJsonArray& Value);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonValue FromValue(const FMatureJsonValue& Value);

	// Convert a JSON value valueto a boolean.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static bool ToBoolean(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a float.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static float ToFloat(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto an integer.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static int32 ToInteger(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a string.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FString ToString(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a date/time.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FDateTime ToDateTime(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a GUID.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FGuid ToGuid(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FColor ToColor(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FLinearColor ToLinearColor(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FRotator ToRotator(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FVector ToVector(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FTransform ToTransform(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a JSON object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonObject ToObject(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Value|Pure")
		static FMatureJsonArray ToArray(const FMatureJsonValue& JValue);

};
