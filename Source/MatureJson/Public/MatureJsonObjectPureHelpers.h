// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"
#include "MatureJsonObjectPureHelpers.generated.h"


UCLASS()
class MATUREJSON_API UMatureJsonObjectPureHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static int32 Size(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static bool  IsEmpty(UPARAM(ref) FMatureJsonObject& JObject);

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Pure")
		static bool  HasKey(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key) ;

	UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Pure")
		static TArray<FString> GetKeys(UPARAM(ref) FMatureJsonObject& JObject) ;


	// Parse a JSON string.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject Parse(const FString& Text);

	// convert a map of booleans to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromBooleanMap(const TMap<FString, bool>& Map);
	// convert a map of floats to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromFloatMap(const TMap<FString, float>& Map);
	// convert a map of integers to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromIntegerMap(const TMap<FString, int32>& Map);
	// convert a map of numbers to object.
	//UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
	static FMatureJsonObject FromDoubleMap(const TMap<FString, double>& Map);
	// convert a map of strings to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromStringMap(const TMap<FString, FString>& Map);
	// convert a map of date/times to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromDateTimeMap(const TMap<FString, FDateTime>& Map);
	// convert a map of GUIDs to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromGuidMap(const TMap<FString, FGuid>& Map);
	// convert a map of colors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromColorMap(const TMap<FString, FColor>& Map);
	// convert a map of linear colors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromLinearColorMap(const TMap<FString, FLinearColor>& Map);
	// convert a map of rotators to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromRotatorMap(const TMap<FString, FRotator>& Map);
	// convert a map of transforms to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromTransformMap(const TMap<FString, FTransform>& Map);
	// convert a map of vectors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromVectorMap(const TMap<FString, FVector>& Map);
	// convert a map of vectors to object.
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject FromValueMap(const TMap<FString, FMatureJsonValue>& Map);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
	static FLinearColor ToLinearColor(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
	static FRotator ToRotator(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
	static FTransform ToTransform(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
	static FVector ToVector(UPARAM(ref) FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
	static FString ToString(const FMatureJsonObject& JObject);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
	static FMatureJsonValue ToValue(const FMatureJsonObject& JObject);


	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static bool GetBoolean(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static float GetFloat(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static int32 GetInt(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static int64 GetInt64(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static uint32 GetUint(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	static uint64 GetUint64(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	//UFUNCTION(BlueprintCallable, Category = "Mature Json|Object|Pure")
	static double GetDouble(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FString GetString(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FGuid GetGuid(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FColor GetColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FDateTime GetDateTime(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FLinearColor GetLinearColor(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FRotator GetRotator(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FTransform GetTransform(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FVector GetVector(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonValue GetValue(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject GetObject(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonArray GetArray(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);

	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonValue NewValue(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonObject NewObject(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);
	UFUNCTION(BlueprintPure, Category = "Mature Json|Object|Pure")
		static FMatureJsonArray NewArray(UPARAM(ref) FMatureJsonObject& JObject, const FString& Key);

};
