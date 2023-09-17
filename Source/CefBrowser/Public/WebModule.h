// Copyright aSurgingRiver, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Materials/MaterialInterface.h"

/**
 * WebBrowserModule interface
 */
class IWebModule : public IModuleInterface
{
public:
	/**
	 * Get or load the Web Browser Module
	 * @return The loaded module
	 */
	static inline IWebModule& Get() {
		return FModuleManager::LoadModuleChecked< IWebModule >("CefBrowser");
	}
	
	/**
	 * Check whether the module has already been loaded
	 * 
	 * @return True if the module is loaded
	 */
	static inline bool IsAvailable(){
		return FModuleManager::Get().IsModuleLoaded("CefBrowser");
	}

	virtual void OnBeginPIE() = 0;
	virtual void OnEndPIE() = 0;
};
