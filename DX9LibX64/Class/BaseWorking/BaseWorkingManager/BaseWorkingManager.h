#pragma once
#include <vector>
#include "../BaseWorking.h"

class BaseWorkingManager
{
public:
	virtual VOID Update();
	virtual VOID Render();

protected:
	std::vector<BaseWorking*> m_pBaseWorkings;
};
