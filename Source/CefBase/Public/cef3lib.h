// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include "Interfaces/IPluginManager.h"
#include <vector>

// WEB_CORE_API
class CEFBASE_API ICEF3LIB {
public:
	static ICEF3LIB* get();
	virtual void LoadCEF3Modules() = 0;
	virtual void UnloadCEF3Modules() = 0;
	virtual FString LibPath() = 0;
	virtual int Branch() = 0;
};


