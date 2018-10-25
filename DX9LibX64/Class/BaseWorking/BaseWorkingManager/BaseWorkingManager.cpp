#include "BaseWorkingManager.h"

BaseWorkingManager::~BaseWorkingManager()
{
	for (BaseWorking* pI : m_pBaseWorkings)
	{
		delete pI;
	}

	m_pBaseWorkings.shrink_to_fit();
}

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

VOID BaseWorkingManager::Resist(BaseWorking* pBaseWorking)
{
	m_pBaseWorkings.push_back(pBaseWorking);
}
