// Clear Before Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonList.h"
#include "MatureJsonListHelpers.generated.h"



UCLASS()
class MATUREJSON_API UMatureJsonListHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static void Remove(UPARAM(ref) FMatureJsonList& JList, const int index,const int num = 1);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static FMatureJsonValue GetValue(const FMatureJsonList& JList,const int index);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static int Size(const FMatureJsonList& JList);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static bool IsEmpty(const FMatureJsonList& JList);

	UFUNCTION(BlueprintPure, Category = "Mature Json")
		static void Clear(UPARAM(ref) FMatureJsonList& JList);

	// Clear Before Copy an array of booleans to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Boolean Array To List"), Category = "Mature Json|Array")
		static FMatureJsonList FromBooleanArray(const TArray<bool>& Value);
	// Clear Before Copy an array of floats to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Float Array To List"), Category = "Mature Json|Array")
		static FMatureJsonList FromFloatArray(const TArray<float>& Value);
	// Clear Before Copy an array of integers to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Integer Array To List"), Category = "Mature Json|Array")
		static FMatureJsonList FromIntegerArray(const TArray<int32>& Value);
	// Clear Before Copy an array of strings to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy String Array To List"), Category = "Mature Json|Array")
		static FMatureJsonList FromStringArray(const TArray<FString>& Value);
	// Clear Before Copy an array of date/times to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Date/Time Array To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList FromDateTimeArray(const TArray<FDateTime>& Value);
	// Clear Before Copy an array of GUIDs to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy GUID Array To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList FromGuidArray(const TArray<FGuid>& Value);
	// Clear Before Copy an array of colors to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Color Array To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList FromColorArray(const TArray<FColor>& Value);
	// Clear Before Copy an array of linear colors to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Linear Color Array To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList FromLinearColorArray(const TArray<FLinearColor>& Value);
	// Clear Before Copy an array of rotators to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Rotator Array To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList FromRotatorArray(const TArray<FRotator>& Value);
	// Clear Before Copy an array of transforms to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Transform Array To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList FromTransformArray(const TArray<FTransform>& Value);
	// Clear Before Copy an array of vectors to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Vector Array To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList FromVectorArray(const TArray<FVector>& Value);
	// Clear Before Copy an array of JSON objects to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Object Array To List"), Category = "Mature Json|Array")
		static FMatureJsonList FromObjectArray(const TArray<FMatureJsonObject>& Value);
	// Clear Before Copy an array of JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Object Array To List"), Category = "Mature Json|Array")
		static FMatureJsonList FromValueArray(const TArray<FMatureJsonValue>& Value);

	// Add an booleans to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Boolean To List"), Category = "Mature Json|Array")
		static int AddBoolean(FMatureJsonList JList, const bool Value);
	// Add an floats to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Float To List"), Category = "Mature Json|Array")
		static int AddFloat(FMatureJsonList JList, const float Value);
	// Add an integers to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Integer To List"), Category = "Mature Json|Array")
		static int AddInteger(FMatureJsonList JList, const int32 Value);
	// Add an strings to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add String To List"), Category = "Mature Json|Array")
		static int AddString(FMatureJsonList JList, const FString& Value);
	// Add an date/times to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Date/Time To List"), Category = "Mature Json|Array|Engine")
		static int AddDateTime(FMatureJsonList JList, const FDateTime& Value);
	// Add an GUIDs to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add GUID To List"), Category = "Mature Json|Array|Engine")
		static int AddGuid(FMatureJsonList JList, const FGuid& Value);
	// Add an colors to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Color To List"), Category = "Mature Json|Array|Engine")
		static int AddColor(FMatureJsonList JList, const FColor& Value);
	// Add an linear colors to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Linear Color To List"), Category = "Mature Json|Array|Engine")
		static int AddLinearColor(FMatureJsonList JList, const FLinearColor& Value);
	// Add an rotators to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Rotator To List"), Category = "Mature Json|Array|Engine")
		static int AddRotator(FMatureJsonList JList, const FRotator& Value);
	// Add an transforms to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Transform To List"), Category = "Mature Json|Array|Engine")
		static int AddTransform(FMatureJsonList JList, const FTransform& Value);
	// Add an vectors to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Vector To List"), Category = "Mature Json|Array|Engine")
		static int AddVector(FMatureJsonList JList, const FVector& Value);
	// Add an JSON objects to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static int AddObject(FMatureJsonList JList, const FMatureJsonObject& Value);
	// Add an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static int AddValue(FMatureJsonList JList, const FMatureJsonValue& Value);
	// Add an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static int AddNull(FMatureJsonList JList);
	// Add an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static int AddList(FMatureJsonList JList, const FMatureJsonList& Value);

	// merge an JSON value to a JSON array.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static FMatureJsonList MergeList(FMatureJsonList JList, const FMatureJsonList& Value);


	// Convert a JSON value valueto a boolean.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static bool GetBoolean(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a float.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static float GetFloat(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto an integer.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static int32 GetInteger(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a string.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FString GetString(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a date/time.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FDateTime GetDateTime(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a GUID.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FGuid GetGuid(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FColor GetColor(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FLinearColor GetLinearColor(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FRotator GetRotator(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FVector GetVector(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a linear color.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array|Engine")
		static FTransform GetTransform(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a JSON object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonObject GetObject(UPARAM(ref) FMatureJsonList& Value, int index);
	// Convert a JSON value valueto a JSON array.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Array")
		static FMatureJsonList GetList(UPARAM(ref) FMatureJsonList& Value, int index);


	// Update an booleans to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Boolean To List"), Category = "Mature Json|Array")
		static FMatureJsonList UpdateBoolean(FMatureJsonList JList, const int index, const bool Value);
	// Update an floats to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Float To List"), Category = "Mature Json|Array")
		static FMatureJsonList UpdateFloat(FMatureJsonList JList, const int index, const float Value);
	// Update an integers to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Integer To List"), Category = "Mature Json|Array")
		static FMatureJsonList UpdateInteger(FMatureJsonList JList, const int index, const int32 Value);
	// Update an strings to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add String To List"), Category = "Mature Json|Array")
		static FMatureJsonList UpdateString(FMatureJsonList JList, const int index, const FString& Value);
	// Update an date/times to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Date/Time To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList UpdateDateTime(FMatureJsonList JList, const int index, const FDateTime& Value);
	// Update an GUIDs to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add GUID To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList UpdateGuid(FMatureJsonList JList, const int index, const FGuid& Value);
	// Update an colors to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Color To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList UpdateColor(FMatureJsonList JList, const int index, const FColor& Value);
	// Update an linear colors to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Linear Color To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList UpdateLinearColor(FMatureJsonList JList, const int index, const FLinearColor& Value);
	// Update an rotators to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Rotator To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList UpdateRotator(FMatureJsonList JList, const int index, const FRotator& Value);
	// Update an transforms to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Transform To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList UpdateTransform(FMatureJsonList JList, const int index, const FTransform& Value);
	// Update an vectors to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Vector To List"), Category = "Mature Json|Array|Engine")
		static FMatureJsonList UpdateVector(FMatureJsonList JList, const int index, const FVector& Value);
	// Update an JSON objects to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static FMatureJsonList UpdateObject(FMatureJsonList JList, const int index, const FMatureJsonObject& Value);
	// Update an JSON value to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static FMatureJsonList UpdateValue(FMatureJsonList JList, const int index, const FMatureJsonValue& Value);
	// Update an JSON value to a JSON array by index .
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object To List"), Category = "Mature Json|Array")
		static FMatureJsonList UpdateNull(FMatureJsonList JList, const int index);


};
