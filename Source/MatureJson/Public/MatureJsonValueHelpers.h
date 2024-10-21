// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"
#include "MatureJsonValueHelpers.generated.h"

UCLASS()
class MATUREJSON_API UMatureJsonValueHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Parse a JSON string.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool ParseString(UPARAM(ref) FMatureJsonValue& JValue,const FString& Text );


	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool ParseFile(UPARAM(ref) FMatureJsonValue& JValue, const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FString SaveString(UPARAM(ref) FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static bool SaveFile(UPARAM(ref) FMatureJsonValue& JValue, const FString& FilePath);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static int Size(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsEmpty(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& Clear(UPARAM(ref) FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static EMatureJsonType Type(const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsObject(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsArray(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsString(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsNumber(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsNull(UPARAM(ref)const FMatureJsonValue& JValue);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsBool(UPARAM(ref)const FMatureJsonValue& JValue);


	// Convert a boolean to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue FromBoolean(bool Value);
	// Convert a float to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue FromFloat(float Value);
	// Convert an integer to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue FromInteger(int32 Value);
	// Convert a string to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue FromString(const FString& Value);
	// Convert a date/time to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FMatureJsonValue FromDateTime(const FDateTime& Value);
	// Convert a GUID to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FMatureJsonValue FromGuid(const FGuid& Value);
	// Convert a color to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FMatureJsonValue FromColor(const FColor& Value);
	// Convert a linear color to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FMatureJsonValue FromLinearColor(const FLinearColor& Value);
	// Convert a rotator to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FMatureJsonValue FromRotator(const FRotator& Value);
	// Convert a transform to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FMatureJsonValue FromTransform(const FTransform& Value);
	// Convert a vector to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FMatureJsonValue FromVector(const FVector& Value);
	// Convert a JSON object to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue FromObject(const FMatureJsonObject& Value);
	// Convert a JSON array to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue FromArray(const FMatureJsonArray& Value);
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue FromValue(const FMatureJsonValue& Value);

	// Convert a JSON value valueto a boolean.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool ToBoolean(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a float.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static float ToFloat(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto an integer.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static int32 ToInteger(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a string.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FString ToString(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a date/time.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FDateTime ToDateTime(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a GUID.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FGuid ToGuid(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FColor ToColor(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FLinearColor ToLinearColor(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FRotator ToRotator(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FVector ToVector(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Engine")
		static FTransform ToTransform(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a JSON object.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonObject ToObject(const FMatureJsonValue& JValue);
	// Convert a JSON value valueto a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonArray ToArray(const FMatureJsonValue& JValue);


	// Convert a Null to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& SetNull(UPARAM(ref) FMatureJsonValue& JValue);
	// Convert a boolean to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& SetBoolean(UPARAM(ref) FMatureJsonValue& JValue,bool Value);
	// Convert a float to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& SetFloat(UPARAM(ref) FMatureJsonValue& JValue, float Value);
	// Convert an integer to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& SetInteger(UPARAM(ref) FMatureJsonValue& JValue, int32 Value);
	// Convert a string to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& SetString(UPARAM(ref) FMatureJsonValue& JValue, const FString& Value);
	// Convert a date/time to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Engine")
		static FMatureJsonValue& SetDateTime(UPARAM(ref) FMatureJsonValue& JValue, const FDateTime& Value);
	// Convert a GUID to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Engine")
		static FMatureJsonValue& SetGuid(UPARAM(ref) FMatureJsonValue& JValue, const FGuid& Value);
	// Convert a color to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Engine")
		static FMatureJsonValue& SetColor(UPARAM(ref) FMatureJsonValue& JValue, const FColor& Value);
	// Convert a linear color to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Engine")
		static FMatureJsonValue& SetLinearColor(UPARAM(ref) FMatureJsonValue& JValue, const FLinearColor& Value);
	// Convert a rotator to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Engine")
		static FMatureJsonValue& SetRotator(UPARAM(ref) FMatureJsonValue& JValue, const FRotator& Value);
	// Convert a transform to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Engine")
		static FMatureJsonValue& SetTransform(UPARAM(ref) FMatureJsonValue& JValue, const FTransform& Value);
	// Convert a vector to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Engine")
		static FMatureJsonValue& SetVector(UPARAM(ref) FMatureJsonValue& JValue, const FVector& Value);
	// Convert a JSON object to a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& SetObject(UPARAM(ref) FMatureJsonValue& JValue, const FMatureJsonObject& Value);
	// Convert a JSON array to a JSON value.
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue& SetArray(UPARAM(ref) FMatureJsonValue& JValue, const FMatureJsonArray& Value);
	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static FMatureJsonValue& SetValue(UPARAM(ref) FMatureJsonValue& JValue, const FMatureJsonValue& Value);
};
