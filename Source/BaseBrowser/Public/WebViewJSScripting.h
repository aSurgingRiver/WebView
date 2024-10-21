// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Guid.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WebViewJSFunction.h"
#include "CoreWebLog.h"
#include "UObject/GCObject.h"



class Error;

/**
 * Implements handling of bridging UObjects client side with JavaScript renderer side.
 */
class BASEBROWSER_API FWebViewJSScripting
	: public FGCObject
{
public:
	FWebViewJSScripting(bool bInJSBindingToLoweringEnabled = true);

	virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) =0;
	virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) =0;


	virtual void InvokeJSFunction(FGuid FunctionId, int32 ArgCount, FWebViewJSParam Arguments[], bool bIsError=false) =0;
	virtual void InvokeJSErrorResult(FGuid FunctionId, const FString& Error) =0;

//#if (ENGINE_MAJOR_VERSION*100+ENGINE_MINOR_VERSION) >= 500
	virtual FString GetReferencerName() const;
//#elif 
//
//#endif

	FString GetBindingName(const FString& Name, UObject* Object) const;

	FString GetBindingName(const FFieldVariant& Property) const;
	void CopyBind(FWebViewJSScripting* dst);
	void ReBind();
	void UnBind();

public:

	// FGCObject API
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
protected:
	// Creates a reversible memory addres -> psuedo-guid mapping.
	// This is done by xoring the address with the first 64 bits of a base guid owned by the instance.
	// Used to identify UObjects from the render process withough exposing internal pointers.
	FGuid PtrToGuid(UObject* Ptr);

	// In addition to reversing the mapping, it verifies that we are currently holding on to an instance of that UObject
	UObject* GuidToPtr(const FGuid& Guid);

	void RetainBinding(UObject* Object,FString Name=TEXT(""));

	void ReleaseBinding(UObject* Object, FString Name = TEXT(""));

	struct ObjectBinding
	{
		bool bIsPermanent;
		int32 Refcount;
		TMap<FString,int> Names;
	};

	struct BindInfo {
		TMap<FString,int> NameS;
		bool bIsPermanent;// 是否含有持久对象
	};

	/** Private data */
	FGuid BaseGuid;

	const FString HideName;
	TMap<UObject*, BindInfo> BoundInfos;
	/** UObjects currently visible on the renderer side. */
	//TMap<UObject*, ObjectBinding> BoundObjects;
#if 50100<=WEBVIEW_ENGINE_VERSION
	TMap<TObjectPtr<UObject>, ObjectBinding> BoundObjects;
#else
	TMap<UObject*, ObjectBinding> BoundObjects;
#endif
	/** Reverse lookup for permanent bindings */
	TMap<FString, UObject*> PermanentUObjectsByName;

	/** The to-lowering option enable for the binding names. */
	// const bool bJSBindingToLoweringEnabled;
};



