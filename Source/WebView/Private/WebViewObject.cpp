// Copyright aXiuShen. All Rights Reserved.

#include "WebViewObject.h"
#include "WebBase.h"


void UWebViewObject::Asyn(const FString& Name, FString& Data, const FString& Callback)
{
	if (!UMG.IsValid())
		return;
	UMG->Asyn(Name, Data, Callback);
}

void UWebViewObject::SetUMG(UWebBase* InUMG){
	UMG = InUMG;// StaticCast<UWebViewWidget*>(InWidget);
}
UWebViewObject::~UWebViewObject() {
	//UE_LOG(LogTemp, Log, TEXT("UWebViewObject::~UWebViewObject"));
}