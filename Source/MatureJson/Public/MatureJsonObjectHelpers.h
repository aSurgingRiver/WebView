// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonList.h"
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
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static int32 Size(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
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
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject FromMapBool(const TMap<FString, bool>& Map);
	// convert a map of floats to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject FromMapFloat(const TMap<FString, float>& Map);
	// convert a map of integers to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject FromMapInt(const TMap<FString, int32>& Map);
	// convert a map of numbers to object.
	//UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject FromMapDouble(const TMap<FString, double>& Map);
	// convert a map of strings to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapString(const TMap<FString, FString>& Map);
	// convert a map of date/times to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapDateTime(const TMap<FString, FDateTime>& Map);
	// convert a map of GUIDs to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapGuid(const TMap<FString, FGuid>& Map);
	// convert a map of colors to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapColor(const TMap<FString, FColor>& Map);
	// convert a map of linear colors to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapLinearColor(const TMap<FString, FLinearColor>& Map);
	// convert a map of rotators to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapRotator(const TMap<FString, FRotator>& Map);
	// convert a map of transforms to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapTransform(const TMap<FString, FTransform>& Map);
	// convert a map of vectors to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject FromMapVector(const TMap<FString, FVector>& Map);
	// convert a map of vectors to object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject FromMapValue(const TMap<FString, FMatureJsonValue>& Map);

	// Merge a JSON object to this object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject MergeObject(FMatureJsonObject JObject, const FMatureJsonObject& inValue);
	// 
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddMapValue(FMatureJsonObject JObject, const TMap<FString, FMatureJsonValue>& Map);
	// Set a property as a boolean.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddKeyBool(FMatureJsonObject JObject, const FString& Key, bool Value);
	// Set a property as a float.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddKeyFloat(FMatureJsonObject JObject, const FString& Key, float Value);
	// Set a property as an integer.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddKeyInt(FMatureJsonObject JObject, const FString& Key, int32 Value);
	// Set a property as a number.
	//UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddKeyDouble(FMatureJsonObject JObject, const FString& Key, double Value);
	// Set a property as a string.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyString(FMatureJsonObject JObject, const FString& Key, const FString& Value);
	// Set a property as a date/time.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyDateTime(FMatureJsonObject JObject, const FString& Key, const FDateTime& Value);
	// Set a property as a GUID.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyGuid(FMatureJsonObject JObject, const FString& Key, const FGuid& Value);
	// Set a property as a color.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyColor(FMatureJsonObject JObject, const FString& Key, const FColor& Value);
	// Set a property as a linear color.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyLinearColor(FMatureJsonObject JObject, const FString& Key, const FLinearColor& Value);
	// Set a property as a rotator.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyRotator(FMatureJsonObject JObject, const FString& Key, const FRotator& Value);
	// Set a property as a transform.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyTransform(FMatureJsonObject JObject, const FString& Key, const FTransform& Value);
	// Set a property as a vector.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
		static FMatureJsonObject AddKeyVector(FMatureJsonObject JObject, const FString& Key, const FVector& Value);
	// Set a property as a JSON value.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddKeyValue(FMatureJsonObject JObject, const FString& Key, const FMatureJsonValue& Value);
	// Set a property as a JSON object.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddKeyObject(FMatureJsonObject JObject, const FString& Key, const FMatureJsonObject& Value);
	// Set a property as a JSON array.
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
		static FMatureJsonObject AddKeyList(FMatureJsonObject JObject, const FString& Key, const FMatureJsonList& Value);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FLinearColor GetLinearColor(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FRotator GetRotator(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FTransform GetTransform(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FVector GetVector(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
	static bool GetKeyBool(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
	static float GetKeyFloat(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
	static int32 GetKeyInt(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static int64 GetKeyInt64(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static uint32 GetKeyUint(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	static uint64 GetKeyUint64(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	//UFUNCTION(BlueprintCallable, Category = "Mature Json|Object")
	static double GetKeyDouble(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FString GetKeyString(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FGuid GetKeyGuid(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FColor GetKeyColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FDateTime GetKeyDateTime(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FLinearColor GetKeyLinearColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FRotator GetKeyRotator(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FTransform GetKeyTransform(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Engine")
	static FVector GetKeyVector(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
	static FMatureJsonValue GetKeyValue(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
	static FMatureJsonObject GetKeyObject(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object")
	static FMatureJsonList GetKeyList(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;
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
		static void Next( FMatureJsonObjectIterator Iterator,int step=1);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static bool IsValid(UPARAM(ref) FMatureJsonObjectIterator& Iterator);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FString Key(UPARAM(ref) FMatureJsonObjectIterator& Iterator);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object Iterator")
		static FMatureJsonValue Value(UPARAM(ref) FMatureJsonObjectIterator& Iterator);


};
