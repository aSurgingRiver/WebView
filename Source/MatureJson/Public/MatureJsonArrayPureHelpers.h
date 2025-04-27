// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"
#include "MatureJsonArrayPureHelpers.generated.h"



UCLASS()
class MATUREJSON_API UMatureJsonArrayPureHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static int Size(const FMatureJsonArray& JArray);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static bool IsEmpty(const FMatureJsonArray& JArray);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static bool HasIndex(const FMatureJsonArray& JArray, const int index);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray Parse(const FString& Text);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FString ToString(const FMatureJsonArray& JArray);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonValue ToValue(const FMatureJsonArray& JArray);

	// Clear Before Copy an array of booleans to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromBooleanArray(const TArray<bool>& Value);
	// Clear Before Copy an array of floats to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromFloatArray(const TArray<float>& Value);
	// Clear Before Copy an array of integers to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromIntegerArray(const TArray<int32>& Value);
	// Clear Before Copy an array of strings to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromStringArray(const TArray<FString>& Value);
	// Clear Before Copy an array of date/times to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromDateTimeArray(const TArray<FDateTime>& Value);
	// Clear Before Copy an array of GUIDs to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromGuidArray(const TArray<FGuid>& Value);
	// Clear Before Copy an array of colors to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromColorArray(const TArray<FColor>& Value);
	// Clear Before Copy an array of linear colors to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromLinearColorArray(const TArray<FLinearColor>& Value);
	// Clear Before Copy an array of rotators to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromRotatorArray(const TArray<FRotator>& Value);
	// Clear Before Copy an array of transforms to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromTransformArray(const TArray<FTransform>& Value);
	// Clear Before Copy an array of vectors to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromVectorArray(const TArray<FVector>& Value);
	// Clear Before Copy an array of JSON objects to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromObjectArray(const TArray<FMatureJsonObject>& Value);
	// Clear Before Copy an array of JSON value to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray FromValueArray(const TArray<FMatureJsonValue>& Value);

	// Convert a JSON value valueto a boolean.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static bool GetBoolean(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a float.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static float GetFloat(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto an integer.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static int32 GetInteger(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a string.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FString GetString(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a date/time.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FDateTime GetDateTime(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a GUID.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FGuid GetGuid(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FColor GetColor(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FLinearColor GetLinearColor(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FRotator GetRotator(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FVector GetVector(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FTransform GetTransform(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a JSON object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonObject GetObject(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonArray GetArray(UPARAM(ref) FMatureJsonArray& JArray, int index);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
		static FMatureJsonValue GetValue(const FMatureJsonArray& JArray, const int index);


	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
	FMatureJsonValue NewValue(FMatureJsonArray& JArray, const int index);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
	FMatureJsonObject NewObject(FMatureJsonArray& JArray, const int index);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Pure")
	FMatureJsonArray NewArray(FMatureJsonArray& JArray, const int index);
};
