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

	InputData* pInputData;
	m_pGameManager->GetInputData(&pInputData);
	m_pKeyState = &pInputData->m_keyBoardState;
	m_pMouseState = &pInputData->m_mouseState;

	Init();
}

Object::~Object()
{
}

Type Object::GetType()
{
	return m_type;
}

FLOAT Object::GetZ()
{
	return m_z;
}
