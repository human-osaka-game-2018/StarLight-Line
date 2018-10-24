#pragma once
#include <windows.h>
#include "../Scene.h"

#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

class TitleScene :public Scene
{
public:
	VOID Update();
	VOID Render();

private:
	enum MenuID
	{
		NEW_GAME,
		LOAD_GAME,
		END_GAME,
		MENU_MAX
	};

	MenuID m_menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };				//表示用menuの並び

	const int M_SELECTING_MENU = 1;												//現在選ばれているmenuが入っているmenuReelの要素番号

	bool m_canSelectMenu = false;
};
