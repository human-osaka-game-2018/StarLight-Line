#pragma once
#include <windows.h>
#include "../BaseWorking/BaseWorking.h"
#include "Scene\Scene.h"

enum class SceneID
{
	VOID_SCENE,

	TITLE_SCENE,

	HOME_SCENE,

	MAIN_SCENE,
};

class Scene;

class SceneManager :public BaseWorking
{
public:
	static SceneManager * GetInstance();
	VOID Release();
	VOID Update();
	VOID Render();

private:
	SceneManager();
	~SceneManager();

	VOID Manage();

	static SceneManager* m_pSceneManager;
	Scene* m_pScene = NULL;
	SceneID m_currentScene = SceneID::VOID_SCENE;
	SceneID m_nextScene = SceneID::TITLE_SCENE;
};
