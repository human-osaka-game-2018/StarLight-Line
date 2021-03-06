#pragma once
#include <windows.h>
#include "../Scene.h"

class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();

	VOID Update();
	VOID Render();
	BOOL GetCanSelectMenu();
	VOID SetCanSelectMenu(BOOL canSelectMenu);
	VOID ChangeNextScene(SceneID sceneID);

private:
	bool m_canSelectMenu = false;	//メニューを表示するかフラグ
};
