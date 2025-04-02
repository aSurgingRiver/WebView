// Copyright aXiuShen. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
//#ifdef WEBVIEW_ANDROID
#ifdef BUILD_EDITOR
#	ifdef ANDROIDBROWSER_EXPORT
#		define ANDROIDBROWSER_LIB DLLEXPORT
#	else
#		define ANDROIDBROWSER_LIB DLLIMPORT
#	endif
#else
#   ifdef ANDROIDBROWSER_EXPORT
//#      define ANDROIDBROWSER_LIB __attribute__((visibility("default")))
#      define ANDROIDBROWSER_LIB DLLEXPORT
#   else
#      define ANDROIDBROWSER_LIB DLLIMPORT
#   endif
#endif
//#endif
