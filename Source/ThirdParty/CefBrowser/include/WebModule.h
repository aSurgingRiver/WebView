// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Materials/MaterialInterface.h"
#include "cef_export_macro.h"


namespace webview {
	class CEFBROWSER_DLL IBrowserInstance
	{
	public:
		/**
		 * Get or load the Web Browser Module
		 * @return The loaded module
		 */
		static IBrowserInstance& Get();

		/**
		 * Check whether the module has already been loaded
		 *
		 * @return True if the module is loaded
		 */

		virtual void OnBeginPIE()=0;
		virtual void OnEndPIE()=0;
		virtual void Load()=0;
		virtual void UnLoad()=0;
		virtual bool check_brand(int brand)=0;
	};

}

