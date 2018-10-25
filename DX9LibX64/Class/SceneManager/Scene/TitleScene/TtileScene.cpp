#include <Windows.h>
#include <d3dx9.h>
#include <time.h>
#include <stdlib.h>
#include "../../../GameManager/GameManager.h"
#include "../../../FBX/FbxRelated.h"
#include "../../../CustomVertices/CustomVertices.h"
#include "../../../Draw/Draw.h"
#include "TitleScene.h"

VOID TitleScene::Update()
{
	KeyBoardState& rKeyState = m_inputData.m_keyBoardState;

	for (int i = 0; i < DIK_MEDIASELECT + 1 && !m_canSelectMenu; ++i)
	{
		if (rKeyState.m_keyPush[i])
		{
			m_canSelectMenu = true;

			return;
		}
	}

	if (!m_canSelectMenu)return;														//���͑҂�����ԂŃL�[����͂��Ă��Ȃ��ꍇmenu�I���͂ł��Ȃ�

	//���j���[�̑I�� �J�n//

	if (rKeyState.m_keyPush[DIK_W] || rKeyState.m_keyPush[DIK_NUMPAD8])					//menu�̐ؑ�
	{
		MenuID menuReelTmp[MENU_MAX] = { m_menuReel[1],m_menuReel[2],m_menuReel[0] };	//�{�^������������menuReel�̒��g������Ă���

		memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_S] || rKeyState.m_keyPush[DIK_NUMPAD2])
	{
		MenuID menuReelTmp[MENU_MAX] = { m_menuReel[2],m_menuReel[0],m_menuReel[1] };

		memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_RETURN])												//menu�̑I��
	{
		switch (m_menuReel[M_SELECTING_MENU])
		{
		case NEW_GAME:
			m_canSelectMenu = false;

			//m_pNextScene = 

			break;

		case LOAD_GAME:
			//m_pNextScene = 
			m_canSelectMenu = false;

			break;

		case END_GAME:
			//m_pNextScene = 
			m_canSelectMenu = false;

			break;

		default:
			break;
		}
	}
	//���j���[�̑I�� �I��//
}

VOID TitleScene::Render()
{
	//������ �J�n//
	if (m_frame == -1)
	{
		m_frame = 0;

		m_pFileManager->CreateTex(_T("Back"), _T("2DTextures/Title/TitleBack.png"));	//�摜�ǂݍ���
		m_pFileManager->CreateTex(_T("Logo"), _T("2DTextures/Title/TitleLogo.png"));
		m_pFileManager->CreateTex(_T("WaitInput"), _T("2DTextures/Title/TitleWaitInput.png"));
		m_pFileManager->CreateTex(_T("NewGame"), _T("2DTextures/Title/TitleMenuNewGame.png"));
		m_pFileManager->CreateTex(_T("LoadGame"), _T("2DTextures/Title/TitleMenuLoadGame.png"));
		m_pFileManager->CreateTex(_T("EndGame"), _T("2DTextures/Title/TitleMenuEndGame.png"));
		m_pFileManager->CreateTex(_T("StarEffect"), _T("2DTextures/Title/StarEffect.png"));

		srand((unsigned int)(time(NULL)));
	}
	//������ �I��//

	D3DXVECTOR2 windowSize;	//window�̃T�C�Y
	m_pGameManager->GetDisplaySize(&windowSize);

	//�w�i�̕`�� �J�n//�N���X�ɂ��邩������Ȃ�
	D3DXVECTOR3 backCenter(windowSize.x*0.5f, windowSize.y*0.5f, 1.0f);
	D3DXVECTOR2 halfBackScale = windowSize * 0.5f;
	CustomVertex back[4];

	m_pCustomVertices->Create(back, &backCenter, &halfBackScale);		//���_�f�[�^�̃Z�b�g

	m_pDraw->Render(back, m_pFileManager->GetTex(_T("Back")));			//�`��
	//�w�i�̕`�� �I��//

	//�G�t�F�N�g�̕`�� �J�n//
	const int STAR_EFFECT_MAX = 60;

	const int STAR_EFFECT_COLORS_MAX = 11;
	const DWORD STAR_EFFECT_COLORS[STAR_EFFECT_COLORS_MAX] =
	{
		D3DCOLOR_ARGB(140,63,255,20),
		D3DCOLOR_ARGB(140,20,255,95),
		D3DCOLOR_ARGB(140,20,255,212),
		D3DCOLOR_ARGB(140,20,181,255),
		D3DCOLOR_ARGB(140,20,63,255),
		D3DCOLOR_ARGB(140,95,20,255),
		D3DCOLOR_ARGB(140,212,20,255),
		D3DCOLOR_ARGB(140,255,20,181),
		D3DCOLOR_ARGB(140,255,20,63),
		D3DCOLOR_ARGB(140,255,95,20),
		D3DCOLOR_ARGB(140,255,212,20),
	};

	static starEffect starEffects[STAR_EFFECT_MAX];
	D3DXVECTOR2 halfstarEffectScale(windowSize.x*0.0023f, windowSize.y*0.6f);
	D3DXVECTOR3 unitStarEffectMovement(0.0f, 60.0f, 0.0f);
	D3DXMATRIX matRotate;

	for (int i = 0; i < STAR_EFFECT_MAX; ++i)
	{
		if (starEffects[i].m_stageCount == starEffect::M_INIT_STAR_EFFECT_COUNT)
		{
			starEffects[i].m_stageCount = -(rand() % 300);

			starEffects[i].m_rotationDegree.x = 0.0f;
			starEffects[i].m_rotationDegree.y = 0.0f;
			starEffects[i].m_rotationDegree.z = (float)(rand() % 30 + 30);

			D3DXMatrixRotationZ(&matRotate, D3DXToRadian(starEffects[i].m_rotationDegree.z));

			D3DXVec3TransformCoord(&starEffects[i].m_movement, &unitStarEffectMovement, &matRotate);

			starEffects[i].m_center.x = (float)(rand() % ((int)(windowSize.x)))+ windowSize.x*3.0f;
			starEffects[i].m_center.y = -4000.0f;
			starEffects[i].m_center.z = 0.99f;

			starEffects[i].m_color = STAR_EFFECT_COLORS[rand() % STAR_EFFECT_COLORS_MAX];
		}

		D3DXVec3Add(&starEffects[i].m_center, &starEffects[i].m_center, &starEffects[i].m_movement);

		m_pCustomVertices->Create(starEffects[i].m_vertices, &starEffects[i].m_center, &halfstarEffectScale, starEffects[i].m_color);

		D3DXVECTOR3 starEffectRerativeRotatePos(0.0f, 0.0f, 0.0f);
		m_pCustomVertices->RotateZ(starEffects[i].m_vertices, starEffects[i].m_rotationDegree.z, &starEffectRerativeRotatePos);

		if (starEffects[i].m_stageCount>0)
		{
			m_pDraw->Render(starEffects[i].m_vertices, m_pFileManager->GetTex(_T("StarEffect")));
		}

		++starEffects[i].m_stageCount;
		if (starEffects[i].m_stageCount == 120)
		{
			starEffects[i].m_stageCount = starEffect::M_INIT_STAR_EFFECT_COUNT;
		}
	}
	//�G�t�F�N�g�̕`�� �I��//

	//���S�̕`�� �J�n//�N���X�ɂ��邩������Ȃ�
	D3DXVECTOR3 logoCenter(windowSize.x*0.5f, windowSize.y*0.35f, 0.98f);
	D3DXVECTOR2 halflogoScale(windowSize.x * 0.29f, windowSize.y * 0.2f);
	CustomVertex logo[4];

	m_pCustomVertices->Create(logo, &logoCenter, &halflogoScale, D3DCOLOR_ARGB(230, 255, 255, 255));	//���_�f�[�^�̃Z�b�g

	m_pDraw->Render(logo, m_pFileManager->GetTex(_T("Logo")));											//�`��
	//���S�̕`�� �I��//

	if (!m_canSelectMenu)
	{
		//���͑҂��e�L�X�g�̕`�� �J�n//�N���X�ɂ��邩������Ȃ�
		D3DXVECTOR3 waitInputCenter(windowSize.x*0.5f, windowSize.y*0.78f, 0.98f);
		D3DXVECTOR2 halfwaitInputScale(windowSize.x * 0.07f, windowSize.y * 0.035f);
		CustomVertex waitInput[4];

		const int FLASH_COUNT_MAX = 127;																											//flashCount�̍ő�l
		static unsigned char flashCount = FLASH_COUNT_MAX;																							//�e�L�X�g�̓_�łɗp����J�E���^

		static bool canCountUp = false;																												//�A���t�@�l�̐܂�Ԃ������肷��t���O

		m_pCustomVertices->Create(waitInput, &waitInputCenter, &halfwaitInputScale, D3DCOLOR_ARGB((int)(flashCount*1.5f) + 30, 255, 255, 255));		//���_�f�[�^�̃Z�b�g

		if (flashCount == FLASH_COUNT_MAX)canCountUp = false;																						//�A���t�@�l�̐܂�Ԃ��ݒ�
		if (flashCount == 0)canCountUp = true;

		flashCount = (canCountUp) ? ++flashCount : --flashCount;																					//canCountUp��true�Ȃ�+ false�Ȃ�-

		m_pDraw->Render(waitInput, m_pFileManager->GetTex(_T("WaitInput")));																			//�`��
		//���͑҂��e�L�X�g�̕`�� �I��//
	}

	if (m_canSelectMenu)
	{
		//menu�e�L�X�g�̕`�� �J�n//�N���X�ɂ��邩������Ȃ�
		for (int i = 0; i < MENU_MAX; ++i)
		{
			D3DXVECTOR3 menuCenter(windowSize.x*0.5f, windowSize.y*(0.65f + 0.07f*i), 0.98f);

			D3DXVECTOR2 halfMenuScale(windowSize.x*0.055f, windowSize.y*0.029f);

			CustomVertex menu[4];

			m_pCustomVertices->Create(menu, &menuCenter, &halfMenuScale, D3DCOLOR_ARGB(200, 255, 255, 255));

			if (i == M_SELECTING_MENU)																				//�I�΂�Ă���menu�͊g�傷��
			{
				const float SELECTING_MENU_SCALE_MULTIPLY = 1.5f;													//�g�嗦
				halfMenuScale.x *= SELECTING_MENU_SCALE_MULTIPLY;
				halfMenuScale.y *= SELECTING_MENU_SCALE_MULTIPLY;

				m_pCustomVertices->Create(menu, &menuCenter, &halfMenuScale, D3DCOLOR_ARGB(230, 255, 255, 255));	//���_�f�[�^�̃Z�b�g
			}

			switch (m_menuReel[i])																					//�`��
			{
			case NEW_GAME:
				m_pDraw->Render(menu, m_pFileManager->GetTex(_T("NewGame")));

				break;

			case LOAD_GAME:
				m_pDraw->Render(menu, m_pFileManager->GetTex(_T("LoadGame")));

				break;

			case END_GAME:
				m_pDraw->Render(menu, m_pFileManager->GetTex(_T("EndGame")));

				break;

			default:
				break;
			}
		}
		//menu�e�L�X�g�̕`�� �I��//
	}

	++m_frame;						//���߂��牽�t���[����������

	if (m_frame < 0)m_frame = 0;	//�I�[�o�[�t���[������0���
}
