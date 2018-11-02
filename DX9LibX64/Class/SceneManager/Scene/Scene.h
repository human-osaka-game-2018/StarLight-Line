#pragma once
#include <Windows.h>
#include "../../GameManager/GameManager.h"
#include "../../BaseWorking/BaseWorking.h"
#include "../../FBX/ClassFBX.h"
#include "../../ObjectManager/ObjectManager.h"

enum class SceneID;

class GameManager;

class Scene :public BaseWorking
{
public:
	Scene();
	~Scene() {};

	VOID syncNextScene(SceneID* pNextScene);

protected:
	static SceneID* m_pNextScene;
	GameManager* m_pGameManager;
	InputData* m_pInputData;
	ObjectManager m_sceneObjectManager;
	LONGLONG m_frame = -1;
};
