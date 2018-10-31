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

	BOOL PreventDecideMenuUnintended();								//�Ӑ}���Ȃ����j���[�I����h���֐� true�Ȃ�return����
	VOID SelectMenu();												//���j���[��I������֐�

	MenuID m_menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };	//�\���p���j���[�̕���
	const INT M_SELECTING_MENU = 1;									//���ݑI�΂�Ă��郁�j���[�������Ă���menuReel�̗v�f�ԍ�
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
