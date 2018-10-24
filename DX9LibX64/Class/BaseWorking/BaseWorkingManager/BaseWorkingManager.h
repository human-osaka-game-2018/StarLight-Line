#pragma once
#include <vector>
#include "../BaseWorking.h"

class BaseWorkingManager
{
public:
	virtual VOID Update();
	virtual VOID Render();

private:
	std::vector<BaseWorking*> pBaseWorkings;
};
