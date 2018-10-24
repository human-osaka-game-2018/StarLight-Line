#include "BaseWorkingManager.h"

VOID BaseWorkingManager::Update()
{
	for (BaseWorking* pBaseWorking : m_pBaseWorkings)
	{
		pBaseWorking->Update();
	}
}

VOID BaseWorkingManager::Render()
{
	for (BaseWorking* pBaseWorking : m_pBaseWorkings)
	{
		pBaseWorking->Render();
	}
}
