// Copyright aXiuShen. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"


#ifdef WEBVIEW_CEF
	#ifdef BUILD_EDITOR
	#	ifdef CEFBROWSER_EXPORT
	#		define CEFBROWSER_DLL DLLEXPORT
	#	else
	#		define CEFBROWSER_DLL DLLIMPORT
	#	endif
	#else
	#	define CEFBROWSER_DLL
	#endif
#endif