// Copyright aXiuShen. All Rights Reserved.


#include "WebViewJSScripting.h"




//class Error;

/**
 * Implements handling of bridging UObjects client side with JavaScript renderer side.
 */

FWebViewJSScripting::FWebViewJSScripting(bool bInJSBindingToLoweringEnabled)
	: BaseGuid(FGuid::NewGuid())
	, HideName(TEXT("$.$"))
	//, bJSBindingToLoweringEnabled(bInJSBindingToLoweringEnabled)
{}

//#if (ENGINE_MAJOR_VERSION*100+ENGINE_MINOR_VERSION) >= 500
FString FWebViewJSScripting::GetReferencerName() const
{
	return FString::Printf(TEXT("WebCefJSScripting%p"), this);//WebCefJSScripting;
}
//#elif 
//
//#endif

FString FWebViewJSScripting::GetBindingName(const FString& Name, UObject* Object) const
{
	return Name.ToLower();// return bJSBindingToLoweringEnabled ? Name.ToLower() : Name;
}

FString FWebViewJSScripting::GetBindingName(const FFieldVariant& Property) const
{
	return Property.GetName().ToLower();//return bJSBindingToLoweringEnabled ? Property.GetName().ToLower() : Property.GetName();
}
void FWebViewJSScripting::CopyBind(FWebViewJSScripting* dst) {
	auto CachedPermanentUObjectsByName = BoundObjects;
	for (auto& Entry : CachedPermanentUObjectsByName) {
		if (!UKismetSystemLibrary::IsValid(Entry.Key))continue;
		for (auto& it : Entry.Value.Names) {
			if (it.Key == Entry.Key->GetName()) continue;
			dst->BindUObject(it.Key, Entry.Key, Entry.Value.bIsPermanent);
		}
	}
}

void FWebViewJSScripting::ReBind() {
	auto CachedPermanentUObjectsByName = BoundObjects;
	BoundObjects.Empty();
	for (auto& Entry : CachedPermanentUObjectsByName) {
		if (!UKismetSystemLibrary::IsValid(Entry.Key))continue;
		for (auto& it : Entry.Value.Names) {
			if (it.Key == Entry.Key->GetName()) continue;
			BindUObject(it.Key, Entry.Key, Entry.Value.bIsPermanent);
		}
	}
}

void FWebViewJSScripting::UnBind() {
	auto CachedPermanentUObjectsByName = BoundObjects;
	for (auto& Entry : CachedPermanentUObjectsByName) {
		if (!UKismetSystemLibrary::IsValid(Entry.Key))continue;
		for (auto& it : Entry.Value.Names) {
			if (it.Key == Entry.Key->GetName()) continue;
			UnbindUObject(it.Key, Entry.Key, Entry.Value.bIsPermanent);
		}
	}
	BoundObjects = CachedPermanentUObjectsByName;
}
// FGCObject API
void FWebViewJSScripting::AddReferencedObjects( FReferenceCollector& Collector )
{
	// Ensure bound UObjects are not garbage collected as long as this object is valid.
	for (auto& Binding : BoundObjects)
	{
		if(!UKismetSystemLibrary::IsValid(Binding.Key))continue;
		Collector.AddReferencedObject(Binding.Key);
	}
}

// Creates a reversible memory addres -> psuedo-guid mapping.
// This is done by xoring the address with the first 64 bits of a base guid owned by the instance.
// Used to identify UObjects from the render process withough exposing internal pointers.
FGuid FWebViewJSScripting::PtrToGuid(UObject* Ptr)
{
	FGuid Guid = BaseGuid;
	if (Ptr == nullptr)
	{
		Guid.Invalidate();
	}
	else
	{
		UPTRINT IntPtr = reinterpret_cast<UPTRINT>(Ptr);
		if (sizeof(UPTRINT) > 4)
		{
			Guid[0] ^= (static_cast<uint64>(IntPtr) >> 32);
		}
		Guid[1] ^= IntPtr & 0xFFFFFFFF;
	}
	return Guid;
}

// In addition to reversing the mapping, it verifies that we are currently holding on to an instance of that UObject
UObject* FWebViewJSScripting::GuidToPtr(const FGuid& Guid)
{
	UPTRINT IntPtr = 0;
	if (sizeof(UPTRINT) > 4)
	{
		IntPtr = static_cast<UPTRINT>(static_cast<uint64>(Guid[0] ^ BaseGuid[0]) << 32);
	}
	IntPtr |= (Guid[1] ^ BaseGuid[1]) & 0xFFFFFFFF;

	UObject* Result = reinterpret_cast<UObject*>(IntPtr);
	if (BoundObjects.Contains(Result))
	{
		return Result;
	}
	else
	{
		return nullptr;
	}
}

void FWebViewJSScripting::RetainBinding(UObject* Object, FString Name)
{
	if (Name.IsEmpty()) return;//Name = HideName;
	if (BoundObjects.Contains(Object))
	{
		//UE_LOG(WebViewLog, Warning, TEXT("RetainBinding: ++ %s"), *Object->GetName());
		if(!BoundObjects[Object].bIsPermanent)
		{
			BoundObjects[Object].Refcount++;
			if (!BoundObjects[Object].Names.Contains(Name)) {
				BoundObjects[Object].Names.Add(Name,0);
			}
			BoundObjects[Object].Names[Name] += 1;
		}
	}
	else
	{
		//UE_LOG(WebViewLog, Warning, TEXT("RetainBinding: Add %s"), *Object->GetName());
		TMap<FString,int> Names ;
		Names.Add(Name, 1);
		BoundObjects.Add(Object, {false, 1,Names });
	}
}

void FWebViewJSScripting::ReleaseBinding(UObject* Object, FString Name)
{
	if (BoundObjects.Contains(Object))
	{
		//UE_LOG(WebViewLog, Warning, TEXT("RetainBinding: Remove "));
		auto& Binding = BoundObjects[Object];
		if(!Binding.bIsPermanent)
		{
			Binding.Refcount--;
			if (Binding.Names.Contains(Name)) {
				auto& Refcount = Binding.Names[Name];
				if ((--Refcount) == 0) {
					Binding.Names.Remove(Name);
				}
			}
			if (Binding.Refcount <= 0)
			{
				BoundObjects.Remove(Object);
			}
		}
	}
}

