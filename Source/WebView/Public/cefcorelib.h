// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include <vector>

class  ICefCoreLIB {
public:
	static ICefCoreLIB* get();
	virtual bool can_load() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
};


