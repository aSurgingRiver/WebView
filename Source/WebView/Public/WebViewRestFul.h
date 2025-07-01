#pragma once

#include "CoreMinimal.h"
#include "ImitateInput.h"
#include "BaseRestFul.h"
#include "MatureJsonValue.h"
#include "WebViewRestFul.generated.h"

class IBaseRestFul;

UCLASS(BlueprintType, Blueprintable)
class UWebViewRestFul : public UObject {
	GENERATED_UCLASS_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRestFul, const FString&, Url, const FMatureJsonValue&, response);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void SetMode(WebView_RestFul_Mode Mode= WebView_RestFul_Mode::WebView_RestFul_Mode_Post);


	UFUNCTION(BlueprintCallable, Category = "Web View")
	void Request(const FString& URL,const FMatureJsonValue& Data);

	UPROPERTY(BlueprintAssignable, Category = "Web View")
	FOnRestFul OnRestFul;
public:
	void BeginDestroy() override ;
	~UWebViewRestFul();
protected:
	TSharedPtr<IBaseRestFul> RestFul();

	void OnRestFulHandle(const FString&, const FMatureJsonValue&);
private:
	TSharedPtr<IBaseRestFul> resetful;
};


