#include <windows.h>
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#include "Scene.h"
#include "../../BaseWorking/BaseWorking.h"
#include "../../GameManager/GameManager.h"
#include "../../FBX/ClassFBX.h"
#include "../../CustomVertices/CustomVertices.h"
#include "../../Draw/Draw.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

SceneID* Scene::m_pNextScene = NULL;

Scene::Scene()
{
	m_pGameManager = GameManager::CopyInstance();
	m_pGameManager->GetInputData(&m_pInputData);
}

VOID Scene::syncNextScene(SceneID* pNextScene)
{
	m_pNextScene = pNextScene;
}

