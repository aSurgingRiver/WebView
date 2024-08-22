// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebViewObject.generated.h"

class UWebBase;

UCLASS()
class WEBVIEW_API UWebViewObject : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Web View")
	void Asyn(const FString& Name, FString& Data, const FString& Callback);

	void SetUMG(UWebBase* InWidget);

	virtual ~UWebViewObject();
private:
	TWeakObjectPtr<UWebBase> UMG;
};


