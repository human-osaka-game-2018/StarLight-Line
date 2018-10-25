#include <windows.h>
#include <vector>
#include <algorithm>
#include <functional>
#include "../GameManager/GameManager.h"
#include "../CustomVertices/CustomVertices.h"
#include "../Draw/Draw.h"
#include "../FileManager/FileManager.h"
#include "../BaseWorking/BaseWorkingManager/BaseWorkingManager.h"
#include "Object2D\Object2D.h"
#include "Object2DManager.h"

#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

Object2DManager::Object2DManager()
{
	m_pGameManager = GameManager::CopyInstance();
	m_inputData = m_pGameManager->GetInputData();
	m_pCustomVertices = CustomVertices::GetInstance();
	m_pDraw = Draw::GetInstance();
	m_pFileManager = FileManager::GetInstace();
}

VOID Object2DManager::Control()
{
	for (BaseWorking* pI : m_pBaseWorkings)
	{
		dynamic_cast<Object2D*>(pI)->syncLibInstance(m_pGameManager, 
			m_pCustomVertices, m_pDraw, m_inputData, m_pFileManager);

		pI->Update();
	}
}

VOID Object2DManager::Render()
{
	std::vector<Object2D*>pObject2Ds;

	for (BaseWorking* pI : m_pBaseWorkings)
	{
		pObject2Ds.push_back(dynamic_cast<Object2D*>(pI));
	}

	//std::sort(pObject2Ds.begin(), pObject2Ds.end(), &this->cmpLarge);

	for (Object2D* pI : pObject2Ds)
	{
		pI->Render();
	}
}

//bool Object2DManager::cmpLarge(Object2D* p1, Object2D* p2)
//{
//	return(p1->GetZ() > p2->GetZ());
//}
