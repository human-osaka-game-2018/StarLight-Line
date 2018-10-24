#include <Windows.h>
#include <d3dx9.h>
#include "../../../GameManager/GameManager.h"
#include "../../../FBX/FbxRelated.h"
#include "../../../CustomVertices/CustomVertices.h"
#include "../../../Draw/Draw.h"
#include "TitleScene.h"

VOID TitleScene::Update()
{
	KeyBoardState& rKeyState = m_inputData.m_keyBoardState;

	//���j���[�̑I�� �J�n//
	static MenuID menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };

	const int SelectingMenu = 1;												//���ݑI�΂�Ă���menu�������Ă���menuReel�̗v�f�ԍ�

	if (rKeyState.m_keyPush[DIK_W] || rKeyState.m_keyPush[DIK_UP])				//menu�̐ؑ�
	{
		MenuID menuReelTmp[MENU_MAX] = { menuReel[1],menuReel[2],menuReel[0] };	//�{�^������������menuReel�̒��g������Ă���

		memcpy(&menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_S] || rKeyState.m_keyPush[DIK_DOWN])
	{
		MenuID menuReelTmp[MENU_MAX] = { menuReel[2],menuReel[0],menuReel[1] };

		memcpy(&menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_RETURN])										//menu�̑I��
	{
		switch (menuReel[SelectingMenu])
		{
		case NEW_GAME:
			//m_pNextScene = 

			break;

		case LOAD_GAME:
			//m_pNextScene = 

			break;

		case END_GAME:
			//m_pNextScene = 

			break;
		}
	}
	//���j���[�̑I�� �I��//
}

VOID TitleScene::Render()
{
	//���C�g�̐ݒ�@�J�n//�N���X�ɂ���\��
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	D3DXVECTOR3 vecDirection(-0.5f, -1.0f, 1.0f);	//���C�g�̕���
	light.Direction = vecDirection;

	light.Type = D3DLIGHT_DIRECTIONAL;	//���C�g�̎�� ����͒������C�g

	light.Diffuse.r = 1.5f;	//���C�g�̐F�̐ݒ�
	light.Diffuse.g = 1.5f;
	light.Diffuse.b = 1.5f;

	light.Specular.r = 10.0f;
	light.Specular.b = 10.0f;
	light.Specular.g = 10.0f;

	light.Ambient.r = 10.f;
	light.Ambient.b = 10.f;
	light.Ambient.g = 10.f;

	light.Range = 0.f;	//���C�g�͈̔́@�������C�g�̏ꍇ�͕K�v�Ȃ�

	LPDIRECT3DDEVICE9 pDirectX3DDevice = m_pGameManager->GetDirectX3DDevice();	//3D�f�o�C�X�̎擾
	pDirectX3DDevice->SetLight(0, &light);	//0�Ԗڂ̃J�����ɐݒ�
	pDirectX3DDevice->LightEnable(0, TRUE);	//���C�g��L����
	//���C�g�̐ݒ�@�I��//
}
