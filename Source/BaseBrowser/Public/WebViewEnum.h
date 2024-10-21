// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebViewEnum.generated.h"



UENUM(BlueprintType, Category = "Web View", meta = (DisplayName = "DocumentState"))
enum class EWebView_DocumentState : uint8
{
	NoDocument = 3 UMETA(DisplayName = "NoDocument"),
	Error      = 2 UMETA(DisplayName = "Error") ,
	Completed  = 0  UMETA(DisplayName = "Completed"),
	Loading    = 1  UMETA(DisplayName = "Loading"),
};

