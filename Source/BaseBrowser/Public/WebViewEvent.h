// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
//#include "WebViewEnum.generated.h"
#include "WebViewEnum.h"
#include "MatureJsonValue.h"
#include "Engine/Texture.h"
#include "Delegates/DelegateCombinations.h"

namespace webview {
	typedef TMap<FString, FString> HtmlHeaders;
	DECLARE_DELEGATE_OneParam(FOnWebState, EWebView_DocumentState /*NewState*/);
	DECLARE_DELEGATE_OneParam(FOnTitleChanged, FString /*NewTitle*/);
	DECLARE_DELEGATE_OneParam(FOnUrlChanged, const FString& /*NewUrl*/);
	DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnChkTrans, const FGeometry&, const FPointerEvent& /*NewUrl*/);
	DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforePopupDelegate, FString, FString);
	DECLARE_DELEGATE_TwoParams(FOnDownloadComplete, FString, FString);
	DECLARE_DELEGATE_TwoParams(FOnPostResponse, const FString&, const FString&);
	DECLARE_DELEGATE_TwoParams(FOnDragEvent, bool , FString);
	DECLARE_DELEGATE_OneParam(FOnRenderCrash, FString);
	DECLARE_DELEGATE_OneParam(FOnTexture2D, UTexture*);
	DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnResourceLoad, FString, int, HtmlHeaders&);
	DECLARE_DELEGATE_OneParam(FOnNeedsRedraw, bool);
	DECLARE_DELEGATE_ThreeParams(FOnJsStr, const FString&, const FString&, const FString&);
	DECLARE_DELEGATE_ThreeParams(FOnJs, const FString&, const FMatureJsonValue&, const FString&);
	DECLARE_DELEGATE_FourParams(FOnWebError, const FString&, const FString&, const FString&, int);
	DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforePopup, FString, FString); 
}

