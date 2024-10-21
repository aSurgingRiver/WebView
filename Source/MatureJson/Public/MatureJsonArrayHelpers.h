// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"
#include "MatureJsonArrayHelpers.generated.h"



UCLASS()
class MATUREJSON_API UMatureJsonArrayHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static void Remove(UPARAM(ref) FMatureJsonArray& JArray, const int index,const int num = 1);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static int Size(const FMatureJsonArray& JArray);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsEmpty(const FMatureJsonArray& JArray);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool HasIndex(const FMatureJsonArray& JArray, const int index);

	UFUNCTION(BlueprintCallable, Category = "Mature Json")
		static void Clear(UPARAM(ref) FMatureJsonArray& JArray);

	// Clear Before Copy an array of booleans to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonArray FromBooleanArray(const TArray<bool>& Value);
	// Clear Before Copy an array of floats to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonArray FromFloatArray(const TArray<float>& Value);
	// Clear Before Copy an array of integers to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonArray FromIntegerArray(const TArray<int32>& Value);
	// Clear Before Copy an array of strings to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonArray FromStringArray(const TArray<FString>& Value);
	// Clear Before Copy an array of date/times to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray FromDateTimeArray(const TArray<FDateTime>& Value);
	// Clear Before Copy an array of GUIDs to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray FromGuidArray(const TArray<FGuid>& Value);
	// Clear Before Copy an array of colors to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray FromColorArray(const TArray<FColor>& Value);
	// Clear Before Copy an array of linear colors to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray FromLinearColorArray(const TArray<FLinearColor>& Value);
	// Clear Before Copy an array of rotators to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray FromRotatorArray(const TArray<FRotator>& Value);
	// Clear Before Copy an array of transforms to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray FromTransformArray(const TArray<FTransform>& Value);
	// Clear Before Copy an array of vectors to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray FromVectorArray(const TArray<FVector>& Value);
	// Clear Before Copy an array of JSON objects to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonArray FromObjectArray(const TArray<FMatureJsonObject>& Value);
	// Clear Before Copy an array of JSON value to a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonArray FromValueArray(const TArray<FMatureJsonValue>& Value);

	// Add an booleans to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddBoolean(UPARAM(ref) FMatureJsonArray& JArray, const bool Value);
	// Add an floats to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddFloat(UPARAM(ref) FMatureJsonArray& JArray, const float Value);
	// Add an integers to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddInteger(UPARAM(ref) FMatureJsonArray& JArray, const int32 Value);
	// Add an strings to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddString(UPARAM(ref) FMatureJsonArray& JArray, const FString& Value);
	// Add an date/times to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static int AddDateTime(UPARAM(ref) FMatureJsonArray& JArray, const FDateTime& Value);
	// Add an GUIDs to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static int AddGuid(UPARAM(ref) FMatureJsonArray& JArray, const FGuid& Value);
	// Add an colors to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static int AddColor(UPARAM(ref) FMatureJsonArray& JArray, const FColor& Value);
	// Add an linear colors to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static int AddLinearColor(UPARAM(ref) FMatureJsonArray& JArray, const FLinearColor& Value);
	// Add an rotators to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static int AddRotator(UPARAM(ref) FMatureJsonArray& JArray, const FRotator& Value);
	// Add an transforms to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static int AddTransform(UPARAM(ref) FMatureJsonArray& JArray, const FTransform& Value);
	// Add an vectors to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static int AddVector(UPARAM(ref) FMatureJsonArray& JArray, const FVector& Value);
	// Add an JSON objects to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddObject(UPARAM(ref) FMatureJsonArray& JArray, const FMatureJsonObject& Value);
	// Add an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddValue(UPARAM(ref) FMatureJsonArray& JArray, const FMatureJsonValue& Value);
	// Add an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddNull(UPARAM(ref) FMatureJsonArray& JArray);
	// Add an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static int AddArray(UPARAM(ref) FMatureJsonArray& JArray, const FMatureJsonArray& Value);

	// merge an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Merge List"), Category = "Mature Json|Array")
		static FMatureJsonArray& MergeArray(UPARAM(ref) FMatureJsonArray& JArray, const FMatureJsonArray& Value);


	// Convert a JSON value valueto a boolean.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static bool GetBoolean(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a float.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static float GetFloat(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto an integer.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static int32 GetInteger(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a string.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FString GetString(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a date/time.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FDateTime GetDateTime(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a GUID.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FGuid GetGuid(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FColor GetColor(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FLinearColor GetLinearColor(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FRotator GetRotator(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FVector GetVector(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FTransform GetTransform(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a JSON object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonObject GetObject(UPARAM(ref) FMatureJsonArray& JArray, int index);
	// Convert a JSON value valueto a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonArray GetArray(UPARAM(ref) FMatureJsonArray& JArray, int index);
	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue GetValue(const FMatureJsonArray& JArray, const int index);


	// Set an booleans to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static FMatureJsonArray& SetBoolean(UPARAM(ref) FMatureJsonArray& JArray, const int index, const bool Value);
	// Set an floats to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static FMatureJsonArray& SetFloat(UPARAM(ref) FMatureJsonArray& JArray, const int index, const float Value);
	// Set an integers to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static FMatureJsonArray& SetInteger(UPARAM(ref) FMatureJsonArray& JArray, const int index, const int32 Value);
	// Set an strings to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static FMatureJsonArray& SetString(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FString& Value);
	// Set an date/times to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray& SetDateTime(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FDateTime& Value);
	// Set an GUIDs to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray& SetGuid(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FGuid& Value);
	// Set an colors to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray& SetColor(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FColor& Value);
	// Set an linear colors to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray& SetLinearColor(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FLinearColor& Value);
	// Set an rotators to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray& SetRotator(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FRotator& Value);
	// Set an transforms to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray& SetTransform(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FTransform& Value);
	// Set an vectors to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array|Engine")
		static FMatureJsonArray& SetVector(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FVector& Value);
	// Set an JSON objects to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static FMatureJsonArray& SetObject(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FMatureJsonObject& Value);
	// Set an JSON value to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static FMatureJsonArray& SetValue(UPARAM(ref) FMatureJsonArray& JArray, const int index, const FMatureJsonValue& Value);
	// Set an JSON value to a JSON array by index .
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
		static FMatureJsonArray& SetNull(UPARAM(ref) FMatureJsonArray& JArray, const int index);
	//
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
	FMatureJsonValue NewValue(FMatureJsonArray& JArray, const int index);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
	FMatureJsonObject NewObject(FMatureJsonArray& JArray, const int index);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Array")
	FMatureJsonArray NewArray(FMatureJsonArray& JArray, const int index);
};

UCLASS()
class MATUREJSON_API UMatureJsonArrayIteratorHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FMatureJsonArrayIterator Begin(UPARAM(ref) FMatureJsonArray& JArray);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FMatureJsonArrayIterator End(UPARAM(ref) FMatureJsonArray& JArray);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static void Next(UPARAM(ref) FMatureJsonArrayIterator& Iterator, int step = 1);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object Iterator")
		static bool IsValid(UPARAM(ref) FMatureJsonArrayIterator& Iterator);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static int Index(UPARAM(ref) FMatureJsonArrayIterator& Iterator);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FMatureJsonValue Value(UPARAM(ref) FMatureJsonArrayIterator& Iterator);

};
