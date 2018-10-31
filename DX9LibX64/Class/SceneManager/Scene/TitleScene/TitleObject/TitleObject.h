#pragma once
#include "../../../../BaseWorking/BaseWorking.h"
#include "../../../../ObjectManager/Object/Object.h"
#include "../../Scene.h"

class TitleBack :public Object
{
public:
	TitleBack(Scene* pScene);
	~TitleBack() {};

	VOID Init();
	VOID Update() {};
	VOID Render();
};

class TitleLogo :public Object
{
public:
	TitleLogo(Scene* pScene);
	~TitleLogo() {};

	VOID Init();
	VOID Update() {};
	VOID Render();
};

class TitleInputPrompt :public Object
{
public:
	TitleInputPrompt(Scene* pScene);
	~TitleInputPrompt() {};

	VOID Init();
	VOID Update();
	VOID Render();
};

class TitleMenu :public Object
{
public:
	TitleMenu(Scene* pScene);
	~TitleMenu() {};

	VOID Init();
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

	BOOL PreventDecideMenuUnintended();								//意図しないメニュー選択を防ぐ関数 trueならreturnする
	VOID SelectMenu();												//メニューを選択する関数

	MenuID m_menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };	//表示用メニューの並び
	const INT M_SELECTING_MENU = 1;									//現在選ばれているメニューが入っているmenuReelの要素番号
};

class TitleStarEffect :public Object
{
public:
	TitleStarEffect(Scene* pScene);
	~TitleStarEffect() {};

	VOID Init();
	VOID Update() {};
	VOID Render();

private:
	struct starEffect
	{
	public:
		BOOL m_canInit = true;
		D3DXVECTOR3 m_movement;
		ObjectData m_data;
		CustomVertex m_vertices[4];
	};
};
