#include <windows.h>
#include "TitleObject.h"
#include "../../../../ObjectManager/Object/Object.h"
#include "../TitleScene.h"
#include "../../../SceneManager.h"
#include "../../Scene.h"

TitleObject::TitleObject(Scene* pScene) :Object(pScene)
{
	m_pTitleScene = dynamic_cast<TitleScene*>(pScene);
}

TitleBack::TitleBack(Scene* pScene) : TitleObject(pScene)
{
	Init();
}

VOID TitleBack::Init()
{
	static BOOL canInit = true;															//��x��������������Ȃ��悤�ɂ���
	if (!canInit)return;
	canInit = false;

	m_type = Type::BACK;																//�`��^�C�v �w�i
	m_z = 1.0f;																			//�`�悷��Ƃ���Z�l ����ɂ��`�揇�����߂Ă���

	m_pGameManager->CreateTex(_T("Back"), _T("2DTextures/Title/title_background.png"));	//�摜�ǂݍ���
}

VOID TitleBack::Render()
{
	m_pGameManager->GetDisplaySize(&m_windowSize);

	ObjectData data;
	data.m_center = { m_windowSize.x*0.5f,m_windowSize.y*0.5f,1.0f };
	data.m_halfScale = { m_windowSize.x * 0.5f ,m_windowSize.y * 0.5f,0.0f };

	CustomVertex back[4];
	m_pGameManager->Create(back, &data);									//���_�f�[�^�̍쐬

	m_pGameManager->Render(back, m_pGameManager->GetTex(_T("Back")));		//�`��
}

TitleLogo::TitleLogo(Scene* pScene) :TitleObject(pScene)
{
	Init();
}

VOID TitleLogo::Init()
{
	static BOOL canInit = true;
	if (!canInit)return;
	canInit = false;

	m_type = Type::TRANSPARENCY;
	m_z = 0.98f;

	m_pGameManager->CreateTex(_T("Logo"), _T("2DTextures/Title/TitleLogo.png"));
}

VOID TitleLogo::Render()
{
	m_pGameManager->GetDisplaySize(&m_windowSize);

	ObjectData data;
	data.m_center = { m_windowSize.x*0.5f,m_windowSize.y*0.35f,0.98f };
	data.m_color = D3DCOLOR_ARGB(230, 255, 255, 255);
	data.m_halfScale = { m_windowSize.x * 0.29f ,m_windowSize.y * 0.2f,0.0f };

	CustomVertex logo[4];
	m_pGameManager->Create(logo, &data);								//���_�f�[�^�̍쐬

	m_pGameManager->Render(logo, m_pGameManager->GetTex(_T("Logo")));	//�`��
}

TitleInputPrompt::TitleInputPrompt(Scene* pScene) :TitleObject(pScene)
{
	Init();
}

VOID TitleInputPrompt::Init()
{
	static BOOL canInit = true;
	if (!canInit)return;
	canInit = false;

	m_type = Type::TRANSPARENCY;
	m_z = 0.98f;

	m_pGameManager->CreateTex(_T("WaitInput"), _T("2DTextures/Title/TitleWaitInput.png"));
}

VOID TitleInputPrompt::Update()
{
	for (INT i = 0; i < DIK_MEDIASELECT + 1 && !m_pTitleScene->GetCanSelectMenu(); ++i)	//�����{�^���������ꂽ�烁�j���[��\������
	{
		if (m_pKeyState->m_keyPush[i])
		{
			m_pTitleScene->SetCanSelectMenu(true);										//���j���[��\�����邩�t���Otrue

			return;
		}
	}
}

VOID TitleInputPrompt::SetAlpha()
{
	m_data.m_color = D3DCOLOR_ARGB((INT)(m_flashCount*1.5f) + 30, 255, 255, 255);	//�J�E���^��p���ăA���t�@�l�𑝌�������
}

VOID TitleInputPrompt::ChangeFlashStrength()
{
	static BOOL canCountUp = false;													//�A���t�@�l�̐܂�Ԃ������肷��t���O
	if (m_flashCount == M_FLASH_COUNT_MAX)canCountUp = false;						//�A���t�@�l�̐܂�Ԃ��ݒ�
	if (m_flashCount == 0)canCountUp = true;
	m_flashCount = (canCountUp) ? ++m_flashCount : --m_flashCount;					//canCountUp��true�Ȃ�+ false�Ȃ�-
}

VOID TitleInputPrompt::Render()
{
	if (m_pTitleScene->GetCanSelectMenu())											//���j���[��\���Ă���ԕ`�悵�Ȃ�
	{
		return;
	}

	m_pGameManager->GetDisplaySize(&m_windowSize);

	m_data.m_center = { m_windowSize.x*0.5f, m_windowSize.y*0.78f, 0.98f };
	m_data.m_halfScale = { m_windowSize.x * 0.07f, m_windowSize.y * 0.035f ,0.0f };

	SetAlpha();

	CustomVertex waitInput[4];
	m_pGameManager->Create(waitInput, &m_data);										//���_�f�[�^�̍쐬

	ChangeFlashStrength();

	m_pGameManager->Render(waitInput, m_pGameManager->GetTex(_T("WaitInput")));		//�`��
}

TitleMenu::TitleMenu(Scene* pScene) :TitleObject(pScene)
{
	Init();
}

VOID TitleMenu::Init()
{
	static BOOL canInit = true;
	if (!canInit)return;
	canInit = false;

	m_type = Type::TRANSPARENCY;
	m_z = 0.98f;

	m_pGameManager->CreateTex(_T("NewGame"), _T("2DTextures/Title/TitleMenuNewGame.png"));
	m_pGameManager->CreateTex(_T("LoadGame"), _T("2DTextures/Title/TitleMenuLoadGame.png"));
	m_pGameManager->CreateTex(_T("EndGame"), _T("2DTextures/Title/TitleMenuEndGame.png"));
}

BOOL TitleMenu::PreventDecideMenuUnintended()
{
	static BOOL isChanging = false;			//�{�^���������ꃁ�j���[���\�����ꂽ���ォ�t���O
	if (!m_pTitleScene->GetCanSelectMenu())
	{
		isChanging = false;

		return true;
	}

	if (m_pTitleScene->GetCanSelectMenu())
	{
		if (isChanging == false)			//��̃t���O��true�Ȃ�enter�Ń��j���[�\����true�ɂȂ����ꍇ,									
		{									//�Ӑ}�������j���[��I��ł��܂��̂ň�xreturn
			isChanging = true;

			return true;
		}
	}

	return false;
}

VOID TitleMenu::RotateMenuUp()
{
	MenuID menuReelTmp[MENU_MAX] = { m_menuReel[1],m_menuReel[2],m_menuReel[0] };							//�{�^������������menuReel�̒��g������Ă���

	memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
}

VOID TitleMenu::RotateMenuDown()
{
	MenuID menuReelTmp[MENU_MAX] = { m_menuReel[2],m_menuReel[0],m_menuReel[1] };

	memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
}

VOID TitleMenu::SelectMenu()
{
	if (m_pKeyState->m_keyPush[DIK_W] || m_pKeyState->m_keyPush[DIK_NUMPAD8] || m_pKeyState->m_keyPush[DIK_UP])	//menu�̐ؑ�
	{
		RotateMenuUp();
	}

	if (m_pKeyState->m_keyPush[DIK_S] || m_pKeyState->m_keyPush[DIK_NUMPAD2] || m_pKeyState->m_keyPush[DIK_DOWN])
	{
		RotateMenuDown();
	}

	if (m_pKeyState->m_keyPush[DIK_RETURN])																		//menu�̑I��
	{
		switch (m_menuReel[M_SELECTING_MENU])
		{
		case NEW_GAME:
			m_pTitleScene->ChangeNextScene(SceneID::MAIN_SCENE);
			m_pTitleScene->SetCanSelectMenu(false);

			break;

		case LOAD_GAME:
			m_pTitleScene->ChangeNextScene(SceneID::MAIN_SCENE);
			m_pTitleScene->SetCanSelectMenu(false);

			break;

		case END_GAME:
			m_pTitleScene->ChangeNextScene(SceneID::MAIN_SCENE);
			m_pTitleScene->SetCanSelectMenu(false);

			break;

		default:
			break;
		}
	}
}

VOID TitleMenu::Update()
{
	if (PreventDecideMenuUnintended())
	{
		return;
	}

	SelectMenu();
}

VOID TitleMenu::Render()
{
	if (!m_pTitleScene->GetCanSelectMenu())
	{
		return;
	}

	m_pGameManager->GetDisplaySize(&m_windowSize);

	ObjectData data;
	for (INT i = 0; i < MENU_MAX; ++i)
	{
		data.m_center = { m_windowSize.x*0.5f, m_windowSize.y*(0.65f + 0.07f*i), 0.98f };
		data.m_halfScale = { m_windowSize.x*0.055f, m_windowSize.y*0.029f ,0.0f };
		data.m_color = D3DCOLOR_ARGB(200, 255, 255, 255);

		CustomVertex menu[4];
		if (i != M_SELECTING_MENU)
		{
			m_pGameManager->Create(menu, &data);
		}

		if (i == M_SELECTING_MENU)														//�I�΂�Ă���menu�͊g�傷��
		{
			const FLOAT SELECTING_MENU_SCALE_MULTIPLY = 1.5f;
			data.m_halfScale *= SELECTING_MENU_SCALE_MULTIPLY;							//�g�嗦				

			m_pGameManager->Create(menu, &data);										//���_�f�[�^�̃Z�b�g
		}

		switch (m_menuReel[i])															//�`��
		{
		case NEW_GAME:
			m_pGameManager->Render(menu, m_pGameManager->GetTex(_T("NewGame")));

			break;

		case LOAD_GAME:
			m_pGameManager->Render(menu, m_pGameManager->GetTex(_T("LoadGame")));

			break;

		case END_GAME:
			m_pGameManager->Render(menu, m_pGameManager->GetTex(_T("EndGame")));

			break;

		default:
			break;
		}
	}
}

TitleStarEffect::TitleStarEffect(Scene* pScene) :TitleObject(pScene)
{
	Init();
}

VOID TitleStarEffect::Init()
{
	m_type = Type::TRANSPARENCY;
	m_z = 0.99f;

	static BOOL canInit = true;
	if (!canInit)return;
	canInit = false;

	m_pGameManager->CreateTex(_T("StarEffect"), _T("2DTextures/Title/StarEffect.png"));
	m_pGameManager->CreateTex(_T("OverStarEffect"), _T("2DTextures/Title/OverStarEffect.png"));
}

VOID TitleStarEffect::InitStarEffects(starEffect* pStarEffect)
{
	static D3DXMATRIX matRotate;

	pStarEffect->m_canInit = false;

	pStarEffect->m_movement = m_unitStarEffectMovement;

	static const INT STAR_EFFECT_COLORS_MAX = 11;
	static const DWORD STAR_EFFECT_COLORS[STAR_EFFECT_COLORS_MAX] =					//���G�t�F�N�g�̐F
	{
		D3DCOLOR_ARGB(255,63,255,20),
		D3DCOLOR_ARGB(255,20,255,95),
		D3DCOLOR_ARGB(255,20,255,212),
		D3DCOLOR_ARGB(255,20,181,255),
		D3DCOLOR_ARGB(255,20,63,255),
		D3DCOLOR_ARGB(255,95,20,255),
		D3DCOLOR_ARGB(255,212,20,255),
		D3DCOLOR_ARGB(255,255,20,181),
		D3DCOLOR_ARGB(255,255,20,63),
		D3DCOLOR_ARGB(255,255,95,20),
		D3DCOLOR_ARGB(255,255,212,20),
	};

	pStarEffect->m_data.m_center = { (FLOAT)(rand() % ((INT)(m_windowSize.x))) + m_windowSize.x*2.5f,	//�����ꏊ�������_���ōs��
		-(FLOAT)(rand() % (INT)(m_windowSize.x * 4)),0.99f };
	pStarEffect->m_data.m_halfScale = m_halfstarEffectScale;
	pStarEffect->m_data.m_degree.z = 45.0f;											//���̓��ˊp����
	pStarEffect->m_data.m_color = STAR_EFFECT_COLORS[rand() % STAR_EFFECT_COLORS_MAX];

	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(pStarEffect->m_data.m_degree.z));
	D3DXVec3TransformCoord(&pStarEffect->m_movement, &m_unitStarEffectMovement, &matRotate);			//���̈ړ��x�N�g���쐬
}

VOID TitleStarEffect::Render()
{
	m_pGameManager->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	m_pGameManager->GetDisplaySize(&m_windowSize);

	static const INT STAR_EFFECT_MAX = 5;																//���G�t�F�N�g�̍ő吔
	static starEffect starEffects[STAR_EFFECT_MAX];
	m_halfstarEffectScale = { m_windowSize.x*0.0025f, m_windowSize.y*0.6f, 0.0f };
	m_unitStarEffectMovement = { 0.0f, 30.0f, 0.0f };

	for (INT i = 0; i < STAR_EFFECT_MAX; ++i)
	{
		if (starEffects[i].m_canInit)
		{
			InitStarEffects(&starEffects[i]);
		}

		D3DXVec3Add(&starEffects[i].m_data.m_center,													//���̈ړ�
			&starEffects[i].m_data.m_center, &starEffects[i].m_movement);

		m_pGameManager->Create(starEffects[i].m_vertices, &starEffects[i].m_data);

		D3DXVECTOR3 starEffectRerativeRotatePos(0.0f, 0.0f, 0.0f);										//��]�̑��Β��S���W
		m_pGameManager->RotateZ(starEffects[i].m_vertices,												//���̉�]
			starEffects[i].m_data.m_degree.z, &starEffectRerativeRotatePos);

		if (starEffects[i].m_vertices[3].m_pos.y >= -100.0f)
		{
			m_pGameManager->Render(starEffects[i].m_vertices,
				m_pGameManager->GetTex(_T("StarEffect")));

			m_pGameManager->SetColor(starEffects[i].m_vertices, D3DCOLOR_ARGB(230, 255, 255, 255));
			m_pGameManager->Render(starEffects[i].m_vertices,
				m_pGameManager->GetTex(_T("OverStarEffect")));
		}

		if (starEffects[i].m_vertices[0].m_pos.y >= m_windowSize.y)
		{
			starEffects[i].m_canInit = true;
		}
	}

	m_pGameManager->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

TitleSmallStarEffect::TitleSmallStarEffect(Scene* pScene) :TitleObject(pScene)
{
	Init();
}

VOID TitleSmallStarEffect::Init()
{
	m_type = Type::TRANSPARENCY;
	m_z = 0.991f;

	static BOOL canInit = true;
	if (!canInit)return;
	canInit = false;

	m_pGameManager->CreateTex(_T("SmallStarEffect"), _T("2DTextures/Title/SmallStarEffect.png"));
	m_pGameManager->CreateTex(_T("OverSmallStarEffect"), _T("2DTextures/Title/OverSmallStarEffect.png"));
}

VOID TitleSmallStarEffect::Render()
{
	m_pGameManager->GetDisplaySize(&m_windowSize);

	const INT SMALL_STAR_EFFECTS_MAX = 150;
	static SmallStarEffect smallStarEffect[SMALL_STAR_EFFECTS_MAX];
	static const INT STAR_EFFECT_COLORS_MAX = 11;
	static const D3DXVECTOR4 STAR_EFFECT_COLORS[STAR_EFFECT_COLORS_MAX] =					//���G�t�F�N�g�̐F
	{
		{255,63,255,20},
		{255,20,255,95},
		{255,20,255,212},
		{255,20,181,255},
		{255,20,63,255},
		{255,95,20,255},
		{255,212,20,255},
		{255,255,20,181},
		{255,255,20,63},
		{255,255,95,20},
		{255,255,212,20},
	};

	for (int i = 0; i < SMALL_STAR_EFFECTS_MAX; ++i)
	{
		if (smallStarEffect[i].m_flashCount == M_INIT_COUNT)
		{
			smallStarEffect[i].m_flashCount = rand() % (M_FLASH_COUNT_MAX - M_FLASH_COUNT_MIN) + M_FLASH_COUNT_MIN;
			smallStarEffect[i].m_canCountUp = rand() % 1;
			smallStarEffect[i].m_data.m_center = { (FLOAT)(rand() % ((INT)(m_windowSize.x))),
				(FLOAT)(rand() % ((INT)(m_windowSize.y))),0.991f };
			FLOAT smallStarEffectHalfScale = 0.5f+rand()%2;
			smallStarEffect[i].m_data.m_halfScale = { smallStarEffectHalfScale,smallStarEffectHalfScale,0.0f };

			INT selectedColor = rand() % STAR_EFFECT_COLORS_MAX;

			smallStarEffect[i].m_color.x = STAR_EFFECT_COLORS[selectedColor].x;
			smallStarEffect[i].m_color.y = STAR_EFFECT_COLORS[selectedColor].y;
			smallStarEffect[i].m_color.z = STAR_EFFECT_COLORS[selectedColor].z;
		}

		CustomVertex OverEffect[4];
		memcpy(OverEffect, smallStarEffect[i].m_vertices, sizeof(CustomVertex) * 4);

		const FLOAT OVER_EFFECT_MULTIPLY = 3.0f;
		D3DXVECTOR2 OVER_EFFECT_MULTIPLYS(OVER_EFFECT_MULTIPLY, OVER_EFFECT_MULTIPLY);
		m_pGameManager->Rescale(OverEffect, &OVER_EFFECT_MULTIPLYS);

		DWORD OverEffectColor = D3DCOLOR_ARGB(250, 255, 255, 255);
		m_pGameManager->SetColor(OverEffect, OverEffectColor);

		m_pGameManager->Render(OverEffect, m_pGameManager->GetTex(_T("OverSmallStarEffect")));

		smallStarEffect[i].m_data.m_color = D3DCOLOR_ARGB((INT)(smallStarEffect[i].m_flashCount),
			(INT)smallStarEffect[i].m_color.x, (INT)smallStarEffect[i].m_color.y, (INT)smallStarEffect[i].m_color.z);

		m_pGameManager->Create(smallStarEffect[i].m_vertices, &smallStarEffect[i].m_data);

		m_pGameManager->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		m_pGameManager->Render(smallStarEffect[i].m_vertices, m_pGameManager->GetTex(_T("SmallStarEffect")));

		if (smallStarEffect[i].m_flashCount >= M_FLASH_COUNT_MAX)smallStarEffect[i].m_canCountUp = false;	//�A���t�@�l�̐܂�Ԃ��ݒ�
		if (smallStarEffect[i].m_flashCount <= M_FLASH_COUNT_MIN)smallStarEffect[i].m_canCountUp = true;

		smallStarEffect[i].m_flashCount = (smallStarEffect[i].m_canCountUp) ?
			smallStarEffect[i].m_flashCount += 5 : smallStarEffect[i].m_flashCount -= 5;		//canCountUp��true�Ȃ�+ false�Ȃ�-
	}

	m_pGameManager->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
