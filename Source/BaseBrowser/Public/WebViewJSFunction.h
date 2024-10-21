// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Misc/Guid.h"
#include "UObject/Class.h"
//#include "warp_macro.h"
#include "WebViewJSFunction.generated.h"


class FWebViewJSScripting;

struct BASEBROWSER_API FWebViewJSParam
{

	struct IStructWrapper
	{
		virtual ~IStructWrapper();
		virtual UStruct* GetTypeInfo() = 0;
		virtual const void* GetData() = 0;
		virtual IStructWrapper* Clone() = 0;
	};

	template <typename T> struct FStructWrapper
		: public IStructWrapper
	{
		T StructValue;
		FStructWrapper(const T& InValue)
			: StructValue(InValue)
		{}
		virtual ~FStructWrapper()
		{}
		virtual UStruct* GetTypeInfo() override
		{
			return T::StaticStruct();
		}
		virtual const void* GetData() override
		{
			return &StructValue;
		}
		virtual IStructWrapper* Clone() override
		{
			return new FStructWrapper<T>(StructValue);
		}
	};

	FWebViewJSParam();
	FWebViewJSParam(bool Value);
	FWebViewJSParam(int8 Value);
	FWebViewJSParam(int16 Value);
	FWebViewJSParam(int32 Value);
	FWebViewJSParam(uint8 Value);
	FWebViewJSParam(uint16 Value);
	FWebViewJSParam(uint32 Value);
	FWebViewJSParam(int64 Value);
	FWebViewJSParam(uint64 Value);
	FWebViewJSParam(double Value);
	FWebViewJSParam(float Value);
	FWebViewJSParam(const FString& Value);
	FWebViewJSParam(const FText& Value);
	FWebViewJSParam(const FName& Value);
	FWebViewJSParam(const TCHAR* Value);
	FWebViewJSParam(UObject* Value);
	template <typename T> FWebViewJSParam(const T& Value,
		typename TEnableIf<!TIsPointer<T>::Value, UStruct>::Type* InTypeInfo=T::StaticStruct())
		: Tag(PTYPE_STRUCT)
		, StructValue(new FStructWrapper<T>(Value))
	{}
	template <typename T> FWebViewJSParam(const TArray<T>& Value)
		: Tag(PTYPE_ARRAY)
	{
		ArrayValue = new TArray<FWebViewJSParam>();
		ArrayValue->Reserve(Value.Num());
		for(T Item : Value)
		{
			ArrayValue->Add(FWebViewJSParam(Item));
		}
	}
	template <typename T> FWebViewJSParam(const TMap<FString, T>& Value)
		: Tag(PTYPE_MAP)
	{
		MapValue = new TMap<FString, FWebViewJSParam>();
		MapValue->Reserve(Value.Num());
		for(const auto& Pair : Value)
		{
			MapValue->Add(Pair.Key, FWebViewJSParam(Pair.Value));
		}
	}
	template <typename K, typename T> FWebViewJSParam(const TMap<K, T>& Value)
		: Tag(PTYPE_MAP)
	{
		MapValue = new TMap<FString, FWebViewJSParam>();
		MapValue->Reserve(Value.Num());
		for(const auto& Pair : Value)
		{
			MapValue->Add(Pair.Key.ToString(), FWebViewJSParam(Pair.Value));
		}
	}
	FWebViewJSParam(const FWebViewJSParam& Other);
	FWebViewJSParam(FWebViewJSParam&& Other);
	~FWebViewJSParam();

	enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag;
	union
	{
		bool BoolValue;
		double DoubleValue;
		int32 IntValue;
		UObject* ObjectValue;
		const FString* StringValue;
		IStructWrapper* StructValue;
		TArray<FWebViewJSParam>* ArrayValue;
		TMap<FString, FWebViewJSParam>* MapValue;
	};

};

//class FWebViewJSScripting;

/** Base class for JS callback objects. */
USTRUCT()
struct BASEBROWSER_API FWebViewJSCallbackBase
{
	GENERATED_USTRUCT_BODY()

public:
	FWebViewJSCallbackBase();

	bool IsValid() const;


protected:
	FWebViewJSCallbackBase(TSharedPtr<FWebViewJSScripting> InScripting, const FGuid& InCallbackId);

	void Invoke(int32 ArgCount, FWebViewJSParam Arguments[], bool bIsError = false) const;

private:

	TWeakPtr<FWebViewJSScripting> ScriptingPtr;
	FGuid CallbackId;
};


/**
 * Representation of a remote JS function.
 * FWebViewJSFunction objects represent a JS function and allow calling them from native code.
 * FWebViewJSFunction objects can also be added to delegates and events using the Bind/AddLambda method.
 */
USTRUCT()
struct BASEBROWSER_API FWebViewJSFunction
	: public FWebViewJSCallbackBase
{
	GENERATED_USTRUCT_BODY()

	FWebViewJSFunction();

	FWebViewJSFunction(TSharedPtr<FWebViewJSScripting> InScripting, const FGuid& InFunctionId);

	template<typename ...ArgTypes> void operator()(ArgTypes... Args) const
	{
		FWebViewJSParam ArgArray[sizeof...(Args)] = {FWebViewJSParam(Args)...};
		Invoke(sizeof...(Args), ArgArray);
	}
};

/** 
 *  Representation of a remote JS async response object.
 *  UFUNCTIONs taking a FWebViewJSResponse will get it passed in automatically when called from a web browser.
 *  Pass a result or error back by invoking Success or Failure on the object.
 *  UFunctions accepting a FWebViewJSResponse should have a void return type, as any value returned from the function will be ignored.
 *  Calling the response methods does not have to happen before returning from the function, which means you can use this to implement asynchronous functionality.
 *
 *  Note that the remote object will become invalid as soon as a result has been delivered, so you can only call either Success or Failure once.
 */
USTRUCT()
struct BASEBROWSER_API FWebViewJSResponse
	: public FWebViewJSCallbackBase
{
	GENERATED_USTRUCT_BODY()

	FWebViewJSResponse();

	FWebViewJSResponse(TSharedPtr<FWebViewJSScripting> InScripting, const FGuid& InCallbackId);

	/**
	 * Indicate successful completion without a return value.
	 * The remote Promise's then() handler will be executed without arguments.
	 */
	void Success() const;

	/**
	 * Indicate successful completion passing a return value back.
	 * The remote Promise's then() handler will be executed with the value passed as its single argument.
	 */
	template<typename T>
	void Success(T Arg) const
	{
		FWebViewJSParam ArgArray[1] = {FWebViewJSParam(Arg)};
		Invoke(1, ArgArray, false);
	}

	/**
	 * Indicate failed completion, passing an error message back to JS.
	 * The remote Promise's catch() handler will be executed with the value passed as the error reason.
	 */
	template<typename T>
	void Failure(T Arg) const
	{
		FWebViewJSParam ArgArray[1] = {FWebViewJSParam(Arg)};
		Invoke(1, ArgArray, true);
	}


};


