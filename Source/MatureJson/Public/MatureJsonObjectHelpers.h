// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"
#include "MatureJsonObjectHelpers.generated.h"

UCLASS()
class MATUREJSON_API UMatureJsonObjectHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonValue AddKey(FMatureJsonObject JObject,const FString& key);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonValue GetKey(UPARAM(ref) FMatureJsonObject& JObject,const FString& key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static int32 Size(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static bool  IsEmpty(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static void  Clear(FMatureJsonObject JObject);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static bool  HasKey(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static void  RemoveKey(FMatureJsonObject JObject,const FString& Key);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static TArray<FString> GetKeys(UPARAM(ref) FMatureJsonObject& JObject) ;


	// convert a map of booleans to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonObject FromBooleanMap(const TMap<FString, bool>& Map);
	// convert a map of floats to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonObject FromFloatMap(const TMap<FString, float>& Map);
	// convert a map of integers to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonObject FromIntegerMap(const TMap<FString, int32>& Map);
	// convert a map of numbers to object.
	//UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
	static FMatureJsonObject FromDoubleMap(const TMap<FString, double>& Map);
	// convert a map of strings to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromStringMap(const TMap<FString, FString>& Map);
	// convert a map of date/times to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromDateTimeMap(const TMap<FString, FDateTime>& Map);
	// convert a map of GUIDs to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromGuidMap(const TMap<FString, FGuid>& Map);
	// convert a map of colors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromColorMap(const TMap<FString, FColor>& Map);
	// convert a map of linear colors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromLinearColorMap(const TMap<FString, FLinearColor>& Map);
	// convert a map of rotators to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromRotatorMap(const TMap<FString, FRotator>& Map);
	// convert a map of transforms to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromTransformMap(const TMap<FString, FTransform>& Map);
	// convert a map of vectors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromVectorMap(const TMap<FString, FVector>& Map);
	// convert a map of vectors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonObject FromValueMap(const TMap<FString, FMatureJsonValue>& Map);

	// Merge a JSON object to this object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& MergeObject(FMatureJsonObject& JObject, const FMatureJsonObject& inValue);
	// 
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddMapValue(FMatureJsonObject JObject, const TMap<FString, FMatureJsonValue>& Map);

	// Set a property as a boolean.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& SetBoolean(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, bool Value);
	// Set a property as a float.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& SetFloat(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, float Value);
	// Set a property as an integer.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& SetInteger(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, int32 Value);
	// Set a property as a number.
	//UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
	static FMatureJsonObject& SetDouble(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, double Value);
	// Set a property as a string.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetString(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FString& Value);
	// Set a property as a date/time.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetDateTime(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FDateTime& Value);
	// Set a property as a GUID.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetGuid(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FGuid& Value);
	// Set a property as a color.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FColor& Value);
	// Set a property as a linear color.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetLinearColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FLinearColor& Value);
	// Set a property as a rotator.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetRotator(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FRotator& Value);
	// Set a property as a transform.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetTransform(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FTransform& Value);
	// Set a property as a vector.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject& SetVector(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FVector& Value);
	// Set a property as a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& SetValue(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FMatureJsonValue& Value);
	// Set a property as a JSON object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& SetObject(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FMatureJsonObject& Value);
	// Set a property as a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& SetArray(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key, const FMatureJsonArray& Value);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject& SetNull(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
	static FLinearColor ToLinearColor(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
	static FRotator ToRotator(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
	static FTransform ToTransform(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
	static FVector ToVector(UPARAM(ref) FMatureJsonObject& JObject);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static bool GetBoolean(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static float GetFloat(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static int32 GetInt(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static int64 GetInt64(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static uint32 GetUint(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static uint64 GetUint64(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	//UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
	static double GetDouble(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FString GetString(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FGuid GetGuid(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FColor GetColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FDateTime GetDateTime(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FLinearColor GetLinearColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FRotator GetRotator(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FTransform GetTransform(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Engine")
		static FVector GetVector(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonValue GetValue(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonObject GetObject(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonArray GetArray(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonValue NewValue(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonObject NewObject(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
		static FMatureJsonArray NewArray(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
};

UCLASS()
class MATUREJSON_API UMatureJsonObjectIteratorHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FMatureJsonObjectIterator Begin(UPARAM(ref) FMatureJsonObject& JObject);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FMatureJsonObjectIterator End(UPARAM(ref) FMatureJsonObject& JObject);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static void Next(UPARAM(ref) FMatureJsonObjectIterator& Iterator,int step=1);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object Iterator")
		static bool IsValid(UPARAM(ref) FMatureJsonObjectIterator& Iterator);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FString Key(UPARAM(ref) FMatureJsonObjectIterator& Iterator);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FMatureJsonValue Value(UPARAM(ref) FMatureJsonObjectIterator& Iterator);

};
