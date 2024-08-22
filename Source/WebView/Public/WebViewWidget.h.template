// Copyright aXiuShen. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Styling/SlateTypes.h"
#ifdef JSON_LIB
#include "JsonLibrary.h"
#endif
#include "WebBase.h"
#include "WebViewWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WEBVIEW_API UWebViewWidget : public UWebBase
{
	GENERATED_UCLASS_BODY()
protected:
	virtual bool Asyn(const FString& Name, FString& Data, const FString& Callback) override;
public:
	/* this party use for jsonlibaray ,if use ,please delete comment.*/
	//@TEMPLATE DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnJsEvent, const FString&, Key, FJsonLibraryValue, Json, const FString&, Callback);
	//@TEMPLATE UPROPERTY(BlueprintAssignable, Category = "Web View | Events") 
	//@TEMPLATE FOnJsEvent OnJsEvent;
	//@TEMPLATE UFUNCTION(BlueprintCallable, Category = "Web View", meta = (AdvancedDisplay = "Data", AutoCreateRefTerm = "Data"))
	//@TEMPLATE void Call(const FString& Function, const FJsonLibraryValue& Data); 
	//@TEMPLATE void ParseAsncHand(const FString& Name, FJsonLibraryValue& Json, const FString& Callback);
};


UCLASS(BlueprintType, Blueprintable)
class WEBVIEW_API UJLParse : public UObject {
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Web View")
	void SyncParse(FString json);
	//@TEMPLATE DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParse, FJsonLibraryValue, Json);
	//@TEMPLATE UPROPERTY(BlueprintAssignable, Category = "Web View | Events") 
	//@TEMPLATE FOnParse OnParse; 
};


