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

	struct starEffect
	{
	public:
		static const int  M_INIT_STAR_EFFECT_COUNT = -999;
		int m_stageCount = M_INIT_STAR_EFFECT_COUNT;
		D3DXVECTOR3 m_center;
		D3DXVECTOR3 m_rotationDegree;
		D3DXVECTOR3 m_movement;
		DWORD m_color;
		CustomVertex m_vertices[4];
	};

	MenuID m_menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };				//表示用menuの並び

	const int M_SELECTING_MENU = 1;												//現在選ばれているmenuが入っているmenuReelの要素番号

	bool m_canSelectMenu = false;
};
