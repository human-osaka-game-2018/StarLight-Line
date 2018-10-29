#include <windows.h>
#include <crtdbg.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include "../GameManager/GameManager.h"
#include "../BaseWorking/BaseWorkingManager/BaseWorkingManager.h"
#include "Object\Object.h"
#include "ObjectManager.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (Object* pI : m_VPObjects)
	{
		delete pI;
	}

	m_VPObjects.shrink_to_fit();
}

VOID ObjectManager::Resist(Object* pObject)
{
	m_VPObjects.push_back(pObject);
}

VOID ObjectManager::Control()
{
	for (Object* pI : m_VPObjects)
	{
		pI->Update();
	}
}

VOID ObjectManager::Render()
{
	std::vector<Object*>VPSortObjects;

	for (Object* pI : m_VPObjects)
	{
		VPSortObjects.push_back(pI);
	}

	std::sort(VPSortObjects.begin(), VPSortObjects.end(), &this->cmpLarge);

	for (Object* pI : VPSortObjects)
	{
		pI->Render();
	}
}

bool ObjectManager::cmpLarge(Object* p1, Object* p2)
{
	return(p1->GetZ() > p2->GetZ());
}
