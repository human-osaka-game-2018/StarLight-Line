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

private:

	bool m_canSelectMenu = false;	//���j���[��\�����邩�t���O
};
