#pragma once
#include "../../../../BaseWorking/BaseWorking.h"
#include "../../../../ObjectManager/Object/Object.h"
#include "../../Scene.h"

class TitleScene;

class TitleObject :public Object
{
public:
	TitleObject(Scene* pScene);
	~TitleObject() {};

protected:
	TitleScene * m_pTitleScene;
};

class TitleBack :public TitleObject
{
public:
	TitleBack(Scene* pScene);
	~TitleBack() {};

	VOID Init();
	VOID Update() {};
	VOID Render();
};

class TitleLogo :public TitleObject
{
public:
	TitleLogo(Scene* pScene);
	~TitleLogo() {};

	VOID Init();
	VOID Update() {};
	VOID Render();
};

class TitleInputPrompt :public TitleObject
{
public:
	TitleInputPrompt(Scene* pScene);
	~TitleInputPrompt() {};

	VOID Init();
	VOID Update();
	VOID Render();

public:
	VOID SetAlpha();
	VOID ChangeFlashStrength();

	ObjectData m_data;
	const INT M_FLASH_COUNT_MAX = 127;		//flashCount�̍ő�l
	UCHAR m_flashCount = M_FLASH_COUNT_MAX;	//�e�L�X�g�̓_�łɗp����J�E���^
};

class TitleMenu :public TitleObject
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

	VOID RotateMenuUp();
	VOID RotateMenuDown();
	BOOL PreventDecideMenuUnintended();								//�Ӑ}���Ȃ����j���[�I����h���֐� true�Ȃ�return����
	VOID SelectMenu();												//���j���[��I������֐�

	MenuID m_menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };	//�\���p���j���[�̕���
	const INT M_SELECTING_MENU = 1;									//���ݑI�΂�Ă��郁�j���[�������Ă���menuReel�̗v�f�ԍ�
};

class TitleStarEffect :public TitleObject
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

	VOID InitStarEffects(starEffect* pStarEffect);

	D3DXVECTOR3 m_halfstarEffectScale;		//0.0027,0.6�@�f�t�H���g�̑傫��
	D3DXVECTOR3 m_unitStarEffectMovement;	//���x

};

class TitleSmallStarEffect :public TitleObject
{
public:
	TitleSmallStarEffect(Scene* pScene);
	~TitleSmallStarEffect() {};

	VOID Init();
	VOID Update() {};
	VOID Render();
private:
	struct SmallStarEffect
	{
	public:
		BOOL m_canCountUp = true;
		INT m_flashCount = TitleSmallStarEffect::M_INIT_COUNT;
		ObjectData m_data;
		D3DXVECTOR4 m_color;
		CustomVertex m_vertices[4];
	};

	static const INT M_INIT_COUNT = -1;
	const INT M_FLASH_COUNT_MAX = 210;
	const INT M_FLASH_COUNT_MIN = 20;
};
