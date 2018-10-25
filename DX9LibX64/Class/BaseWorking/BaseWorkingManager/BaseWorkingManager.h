#pragma once
#include <vector>
#include "../BaseWorking.h"

class BaseWorkingManager
{
public:
	BaseWorkingManager() {};
	~BaseWorkingManager();

	virtual VOID Update();
	virtual VOID Render();
	virtual VOID Resist(BaseWorking* pBaseWorking);

protected:
	std::vector<BaseWorking*> m_pBaseWorkings;
};
