
#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/SlateDelegates.h"
#include "ImitateInput.generated.h"



UENUM(BlueprintType, Category = "Web View", meta = (DisplayName = "Imitate Input Mouse"))
enum class WebView_ImitateInput_Mouse : uint8
{
	WebView_ImitateInput_Mouse_Down = 0 UMETA(DisplayName = "MouseDown"),
	WebView_ImitateInput_Mouse_Up = 1 UMETA(DisplayName = "MouseUp"),
	WebView_ImitateInput_Mouse_Move = 2 UMETA(DisplayName = "MouseMove"),
};

UENUM(BlueprintType, Category = "Web View", meta = (DisplayName = "Imitate Input Key"))
enum class WebView_ImitateInput_Key : uint8
{
	WebView_ImitateInput_Key_Down = 0 UMETA(DisplayName = "KeyDown"),
	WebView_ImitateInput_Key_Up = 1 UMETA(DisplayName = "KeyUp"),
	WebView_ImitateInput_Key_Char = 2 UMETA(DisplayName = "KeyChar"),
};


UCLASS(BlueprintType, Blueprintable)
class CEFBROWSER_API UImitateInput:public UObject
{
	GENERATED_UCLASS_BODY()
public:
	// spec url
	//UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Web View")
	//FString URL;

	// Show Imitate Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Web View")
	bool Show;

	// command interval time .ms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 10, UIMax = 10000), Category = "Web View")
	int interval;

	// command interval time .ms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Web View")
	FIntPoint Size;

	/* 
	{"type":"delay","ms":3000}
	{"type":"input","text":"content"}
	{"type":"key_down","code":0,"character":0,"modify":0}
	{"type":"key_char","code":0,"character":0,"modify":0}
	{"type":"key_up","code":0,"character":0,"modify":0}
	{"type":"mouse_down","pos":{"x":128,"y":256}}
	{"type":"mouse_move","pos":{"x":128,"y":256}}
	{"type":"mouse_up","pos":{"x":128,"y":256}}
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Web View")
	TArray<FString> Event;

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void AddMouse(const WebView_ImitateInput_Mouse mouse,const FIntPoint& point,const int idx=-1);
	
	UFUNCTION(BlueprintCallable, Category = "Web View")
	void AddClicked(const FIntPoint& point, const int idx = -1);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void AddText(const FString& text, const int idx = -1);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void AddDelay(const int ms, const int idx = -1);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void AddKeystroke(const WebView_ImitateInput_Key keyboard,const FKey& key,const TArray<FKey>& CombinKey, const int idx = -1);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void AddKey(const FKey& key, const TArray<FKey>& CombinKey, const int idx = -1);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void ShowLog(bool on=false);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	void Clear();
};

typedef UImitateInput FImitateInput;

UENUM(BlueprintType, Category = "Web View")
enum class WebView_Keyboard_Mode: uint8
{
	WebView_Keyboard_Mode_Scenes = 1 UMETA(DisplayName = "Scenes"),
	WebView_Keyboard_Mode_Blend = 0 UMETA(DisplayName = "Blend"),
	WebView_Keyboard_Mode_Both = 2 UMETA(DisplayName = "Both"),
};

