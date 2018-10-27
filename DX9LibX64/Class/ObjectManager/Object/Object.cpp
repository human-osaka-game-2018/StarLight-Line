#include "Object.h"
#include "../../CustomVertices/CustomVertices.h"
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

Object::Object(Scene* pScene)
{
	m_pScene = pScene;

	m_pGameManager = GameManager::CopyInstance();

	m_pGameManager->GetInputData(&m_pInputData);

	Init();
}

Object::~Object()
{
	for (ObjectData* pI : m_pObjectDatas)
	{
		delete pI;
	}

	m_pObjectDatas.shrink_to_fit();
}

Type Object::GetType()
{
	return m_type;
}

FLOAT Object::GetZ()
{
	return m_pObjectDatas[0]->m_center.z;
}
