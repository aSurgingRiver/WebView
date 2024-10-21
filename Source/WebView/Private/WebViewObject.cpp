// Copyright aXiuShen. All Rights Reserved.

#include "WebViewObject.h"
#include "MatureJsonValue.h"
#include "WebBase.h"


void UWebViewObject::Asyn(const FString& Name, FString& Data, const FString& Callback)
{
	if (!UMG.IsValid())
		return;
	if (false == using_json_object) {// this is old 
		UMG->Asyn(Name, Data, Callback);
		return;
	}
	/*if (sync_json)*/ {
		FMatureJsonValue json;
		json.ParseString(Data);
		UMG->Asyn(Name, json, Callback);
		return;
	}
	//AsyncTask(ENamedThreads::Type::AnyThread, [UMG= UMG, Name= Name, Data= Data, Callback= Callback]() {
	//	FMatureJsonValue json;
	//	json.Parse(Data);
	//	AsyncTask(ENamedThreads::Type::GameThread, [UMG,Name,json, Callback]() {
	//		UMG->Asyn(Name, json, Callback);
	//		}
	//	);
	//	}
	//);
}

void UWebViewObject::SetUMG(UWebBase* InUMG){
	UMG = InUMG;// StaticCast<UWebViewWidget*>(InWidget);
}
UWebViewObject::~UWebViewObject() {
	
}

void UWebViewObject::SetJsonObject(bool yes) {
	using_json_object = yes;
}

void UWebViewObject::SetJsonSync(bool yes) {
	sync_json = yes;
}