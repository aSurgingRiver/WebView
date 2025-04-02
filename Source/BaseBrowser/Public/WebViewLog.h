// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

BASEBROWSER_API DECLARE_LOG_CATEGORY_EXTERN(WebViewLog, Log, All);

namespace webview {
	BASEBROWSER_API void PrintScreen(FString Content, FColor color = FColor::Green, float time = 1.0);
}