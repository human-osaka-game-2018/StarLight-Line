#include "Object2D.h"
#include "../../CustomVertices/CustomVertices.h"
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

Object2D::~Object2D()
{
	for (Object2DData* pI : m_pObject2DDatas)
	{
		delete pI;
	}

	m_pObject2DDatas.shrink_to_fit();
}

Type Object2D::GetType()
{
	return m_type;
}

FLOAT Object2D::GetZ()
{
	return m_pObject2DDatas[0]->m_center.z;
}

VOID Object2D::syncLibInstance(GameManager* pGameManager, CustomVertices* pCustomVertices, Draw* pDraw, InputData inputData, FileManager* pFileManager)
{
	m_pGameManager = pGameManager;
	m_pCustomVertices = m_pCustomVertices;
	m_pDraw = pDraw;
	m_inputData = inputData;
	m_pFileManager = pFileManager;
}
