// Copyright aXiuShen. All Rights Reserved.

#include "WebViewWidget.h"
//#include "SCefBrowser.h"
#include "Async/Async.h"
#include "WebViewObject.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Async/TaskGraphInterfaces.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/ConfigCacheIni.h"


#if WITH_EDITOR
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialExpressionMaterialFunctionCall.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Materials/MaterialFunction.h"
#include "Factories/MaterialFactoryNew.h"
//#include "AssetRegistryModule.h"
#include "PackageHelperFunctions.h"
#endif

#define LOCTEXT_NAMESPACE "WebViewWidget"

/////////////////////////////////////////////////////
// UWebViewWidget

UWebViewWidget::UWebViewWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}



bool UWebViewWidget::Asyn(const FString& Name, FString& Data, const FString& Callback) {
	if (UWebBase::Asyn(Name, Data, Callback))return true;
	return false;
}

/////////////////////////////////////////////////////
#ifdef JSON_LIB
void UWebViewWidget::Call(const FString& Function, const FJsonLibraryValue& Data)
{
	//if (Json == nullptr)return;
	CallJsonStr(Function, Data.Stringify());
}

void UWebViewWidget::ParseAsncHand(const FString& Name, FJsonLibraryValue& Json, const FString& Callback) {
	OnJsEvent.Broadcast(Name,Json, Callback);
}

#endif


UJLParse::UJLParse(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UJLParse::SyncParse(FString json) {

}

#undef LOCTEXT_NAMESPACE
