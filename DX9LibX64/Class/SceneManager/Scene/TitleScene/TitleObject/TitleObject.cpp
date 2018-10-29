#include <windows.h>
#include "TitleObject.h"
#include "../../../../ObjectManager/Object/Object.h"
#include "../TitleScene.h"
#include "../../../SceneManager.h"
#include "../../Scene.h"

TitleBack::TitleBack(Scene* pScene) :Object(pScene)
{
	Init();
}

VOID TitleBack::Init()
{
	m_type = Type::BACK;
	m_z = 1.0f;

	static bool canInit = true;
	if (!canInit)return;
	canInit = false;

	m_pGameManager->CreateTex(_T("Back"), _T("2DTextures/Title/TitleBack.png"));	//画像読み込み
}

VOID TitleBack::Render()
{
	D3DXVECTOR2 windowSize;	//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	ObjectData data;
	data.m_center = { windowSize.x*0.5f,windowSize.y*0.5f,1.0f };
	data.m_halfScale = { windowSize.x * 0.5f ,windowSize.y * 0.5f,0.0f };

	CustomVertex back[4];
	m_pGameManager->Create(back, &data);								//頂点データのセット

	m_pGameManager->Render(back, m_pGameManager->GetTex(_T("Back")));	//描画
}

TitleLogo::TitleLogo(Scene* pScene) :Object(pScene)
{
	Init();
}

VOID TitleLogo::Init()
{
	m_type = Type::TRANSPARENCY;
	m_z = 0.98f;

	static bool canInit = true;
	if (!canInit)return;
	canInit = false;

	m_pGameManager->CreateTex(_T("Logo"), _T("2DTextures/Title/TitleLogo.png"));
}

VOID TitleLogo::Render()
{
	D3DXVECTOR2 windowSize;												//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	ObjectData data;
	data.m_center = { windowSize.x*0.5f,windowSize.y*0.35f,0.98f };
	data.m_color = D3DCOLOR_ARGB(230, 255, 255, 255);
	data.m_halfScale = { windowSize.x * 0.29f ,windowSize.y * 0.2f,0.0f };

	CustomVertex logo[4];
	m_pGameManager->Create(logo, &data);								//頂点データのセット

	m_pGameManager->Render(logo, m_pGameManager->GetTex(_T("Logo")));	//描画
}

TitleInputPrompt::TitleInputPrompt(Scene* pScene) :Object(pScene)
{
	Init();
}

VOID TitleInputPrompt::Init()
{
	m_type = Type::TRANSPARENCY;
	m_z = 0.98f;

	static bool canInit = true;
	if (!canInit)return;
	canInit = false;

	m_pGameManager->CreateTex(_T("WaitInput"), _T("2DTextures/Title/TitleWaitInput.png"));
}

VOID TitleInputPrompt::Update()
{
	KeyBoardState& rKeyState = m_pInputData->m_keyBoardState;

	TitleScene* pTitleScene = dynamic_cast<TitleScene*>(m_pScene);

	for (INT i = 0; i < DIK_MEDIASELECT + 1 && !pTitleScene->GetCanSelectMenu(); ++i)	//何かボタンが押されたらメニューを表示する
	{
		if (rKeyState.m_keyPush[i])
		{
			pTitleScene->SetCanSelectMenu(true);										//メニューを表示するかフラグtrue

			return;
		}
	}
}

VOID TitleInputPrompt::Render()
{
	TitleScene* pTitleScene = dynamic_cast<TitleScene*>(m_pScene);

	if (pTitleScene->GetCanSelectMenu())										//メニューを表示ている間描画しない
	{
		return;
	}

	D3DXVECTOR2 windowSize;														//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	ObjectData data;
	data.m_center = { windowSize.x*0.5f, windowSize.y*0.78f, 0.98f };
	data.m_halfScale = { windowSize.x * 0.07f, windowSize.y * 0.035f ,0.0f };

	const INT FLASH_COUNT_MAX = 127;											//flashCountの最大値
	static unsigned char flashCount = FLASH_COUNT_MAX;							//テキストの点滅に用いるカウンタ
	data.m_color = D3DCOLOR_ARGB((INT)(flashCount*1.5f) + 30, 255, 255, 255);	//カウンタを用いてアルファ値を増減させる

	CustomVertex waitInput[4];
	m_pGameManager->Create(waitInput, &data);									//頂点データのセット

	static bool canCountUp = false;												//アルファ値の折り返しを決定するフラグ
	if (flashCount == FLASH_COUNT_MAX)canCountUp = false;						//アルファ値の折り返し設定
	if (flashCount == 0)canCountUp = true;
	flashCount = (canCountUp) ? ++flashCount : --flashCount;					//canCountUpがtrueなら+ falseなら-

	m_pGameManager->Render(waitInput, m_pGameManager->GetTex(_T("WaitInput")));	//描画
}

TitleMenu::TitleMenu(Scene* pScene) :Object(pScene)
{
	Init();
}

VOID TitleMenu::Init()
{
	m_type = Type::TRANSPARENCY;
	m_z = 0.98f;

	static bool canInit = true;
	if (!canInit)return;
	canInit = false;

	m_pGameManager->CreateTex(_T("NewGame"), _T("2DTextures/Title/TitleMenuNewGame.png"));
	m_pGameManager->CreateTex(_T("LoadGame"), _T("2DTextures/Title/TitleMenuLoadGame.png"));
	m_pGameManager->CreateTex(_T("EndGame"), _T("2DTextures/Title/TitleMenuEndGame.png"));
}

BOOL TitleMenu::PreventDecideMenuUnintended()
{
	TitleScene* pTitleScene = dynamic_cast<TitleScene*>(m_pScene);

	static bool isChanging = false;																		//ボタンが押されメニューが表示された直後かフラグ
	if (!pTitleScene->GetCanSelectMenu())																//上のフラグがtrueならenterでメニュー表示がtrueになった場合,
	{																									//意図せずメニューを選んでしまうので一度return
		isChanging = false;

		return true;
	}

	if (pTitleScene->GetCanSelectMenu())
	{
		if (isChanging == false)
		{
			isChanging = true;

			return true;
		}
	}

	return false;
}

VOID TitleMenu::SelectMenu()
{
	TitleScene* pTitleScene = dynamic_cast<TitleScene*>(m_pScene);

	KeyBoardState& rKeyState = m_pInputData->m_keyBoardState;
	if (rKeyState.m_keyPush[DIK_W] || rKeyState.m_keyPush[DIK_NUMPAD8] || rKeyState.m_keyPush[DIK_UP])	//menuの切替
	{
		MenuID menuReelTmp[MENU_MAX] = { m_menuReel[1],m_menuReel[2],m_menuReel[0] };					//ボタンが押されるとmenuReelの中身がずれていく

		memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_S] || rKeyState.m_keyPush[DIK_NUMPAD2] || rKeyState.m_keyPush[DIK_DOWN])
	{
		MenuID menuReelTmp[MENU_MAX] = { m_menuReel[2],m_menuReel[0],m_menuReel[1] };

		memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_RETURN])																//menuの選択
	{
		switch (m_menuReel[M_SELECTING_MENU])
		{
		case NEW_GAME:
			//*m_pNextScene = SceneID::MAIN_SCENE;
			pTitleScene->SetCanSelectMenu(false);

			break;

		case LOAD_GAME:
			//*m_pNextScene = SceneID::MAIN_SCENE;
			pTitleScene->SetCanSelectMenu(false);

			break;

		case END_GAME:
			//*m_pNextScene = SceneID::MAIN_SCENE;
			pTitleScene->SetCanSelectMenu(false);

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
	TitleScene* pTitleScene = dynamic_cast<TitleScene*>(m_pScene);

	if (!pTitleScene->GetCanSelectMenu())
	{
		return;
	}

	D3DXVECTOR2 windowSize;										//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	ObjectData data;
	for (INT i = 0; i < MENU_MAX; ++i)
	{
		data.m_center = { windowSize.x*0.5f, windowSize.y*(0.65f + 0.07f*i), 0.98f };
		data.m_halfScale = { windowSize.x*0.055f, windowSize.y*0.029f ,0.0f };
		data.m_color = D3DCOLOR_ARGB(200, 255, 255, 255);

		CustomVertex menu[4];
		if (i != M_SELECTING_MENU)
		{
			m_pGameManager->Create(menu, &data);
		}

		if (i == M_SELECTING_MENU)								//選ばれているmenuは拡大する
		{
			const FLOAT SELECTING_MENU_SCALE_MULTIPLY = 1.5f;
			data.m_halfScale *= SELECTING_MENU_SCALE_MULTIPLY;	//拡大率				

			m_pGameManager->Create(menu, &data);				//頂点データのセット
		}

		switch (m_menuReel[i])									//描画
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

TitleStarEffect::TitleStarEffect(Scene* pScene) :Object(pScene)
{
	Init();
}

VOID TitleStarEffect::Init()
{
	m_type = Type::TRANSPARENCY;
	m_z = 0.99f;

	static bool canInit = true;
	if (!canInit)return;
	canInit = false;

	m_pGameManager->CreateTex(_T("StarEffect"), _T("2DTextures/Title/StarEffect.png"));
	m_pGameManager->CreateTex(_T("OverStarEffect"), _T("2DTextures/Title/OverStarEffect.png"));
}

VOID TitleStarEffect::Render()
{
	D3DXVECTOR2 windowSize;											//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	static const INT STAR_EFFECT_MAX = 15;							//星エフェクトの最大数
	static const INT STAR_EFFECT_COLORS_MAX = 11;
	static const DWORD STAR_EFFECT_COLORS[STAR_EFFECT_COLORS_MAX] =
	{
		D3DCOLOR_ARGB(190,63,255,20),
		D3DCOLOR_ARGB(190,20,255,95),
		D3DCOLOR_ARGB(190,20,255,212),
		D3DCOLOR_ARGB(190,20,181,255),
		D3DCOLOR_ARGB(190,20,63,255),
		D3DCOLOR_ARGB(190,95,20,255),
		D3DCOLOR_ARGB(190,212,20,255),
		D3DCOLOR_ARGB(190,255,20,181),
		D3DCOLOR_ARGB(190,255,20,63),
		D3DCOLOR_ARGB(190,255,95,20),
		D3DCOLOR_ARGB(190,255,212,20),
	};

	static starEffect starEffects[STAR_EFFECT_MAX];
	D3DXVECTOR3 halfstarEffectScale(windowSize.x*0.0025f, windowSize.y*0.6f, 0.0f);							//0.0027,0.6　デフォルトの大きさ
	D3DXVECTOR3 unitStarEffectMovement(0.0f, 30.0f, 0.0f);													//速度

	D3DXMATRIX matRotate;
	for (INT i = 0; i < STAR_EFFECT_MAX; ++i)
	{
		if (starEffects[i].m_canInit)
		{
			starEffects[i].m_canInit = false;

			starEffects[i].m_movement = unitStarEffectMovement;

			starEffects[i].m_data.m_center = { (FLOAT)(rand() % ((INT)(windowSize.x))) + windowSize.x*2.5f,-(FLOAT)(rand() % 5000),0.99f };
			starEffects[i].m_data.m_halfScale = halfstarEffectScale;
			starEffects[i].m_data.m_degree.z = (FLOAT)(rand() % 30 + 30);
			starEffects[i].m_data.m_color = STAR_EFFECT_COLORS[rand() % STAR_EFFECT_COLORS_MAX];

			D3DXMatrixRotationZ(&matRotate, D3DXToRadian(starEffects[i].m_data.m_degree.z));
			D3DXVec3TransformCoord(&starEffects[i].m_movement, &unitStarEffectMovement, &matRotate);
		}

		D3DXVec3Add(&starEffects[i].m_data.m_center, &starEffects[i].m_data.m_center, &starEffects[i].m_movement);

		m_pGameManager->Create(starEffects[i].m_vertices, &starEffects[i].m_data);

		D3DXVECTOR3 starEffectRerativeRotatePos(0.0f, 0.0f, 0.0f);
		m_pGameManager->RotateZ(starEffects[i].m_vertices, starEffects[i].m_data.m_degree.z, &starEffectRerativeRotatePos);

		if (starEffects[i].m_vertices[3].m_pos.y >= -100.0f)
		{
			m_pGameManager->Render(starEffects[i].m_vertices, m_pGameManager->GetTex(_T("StarEffect")));

			m_pGameManager->SetColor(starEffects[i].m_vertices, D3DCOLOR_ARGB(130, 255, 255, 255));
			m_pGameManager->Render(starEffects[i].m_vertices, m_pGameManager->GetTex(_T("OverStarEffect")));
		}

		if (starEffects[i].m_vertices[0].m_pos.y >= windowSize.y)
		{
			starEffects[i].m_canInit = true;
		}
	}
}
