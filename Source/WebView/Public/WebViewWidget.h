// Copyright aXiuShen. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Styling/SlateTypes.h"
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

};


UCLASS(BlueprintType, Blueprintable)
class WEBVIEW_API UJLParse : public UObject {
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Web View")
	void SyncParse(FString json);
};


