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

	for (int i = 0; i < DIK_MEDIASELECT + 1 && !m_canSelectMenu; ++i)
	{
		if (rKeyState.m_keyPush[i])
		{
			m_canSelectMenu = true;

			return;
		}
	}

	if (!m_canSelectMenu)return;														//入力待ちを状態でキーを入力していない場合menu選択はできない

	//メニューの選択 開始//

	if (rKeyState.m_keyPush[DIK_W] || rKeyState.m_keyPush[DIK_NUMPAD8])					//menuの切替
	{
		MenuID menuReelTmp[MENU_MAX] = { m_menuReel[1],m_menuReel[2],m_menuReel[0] };	//ボタンが押されるとmenuReelの中身がずれていく

		memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_S] || rKeyState.m_keyPush[DIK_NUMPAD2])
	{
		MenuID menuReelTmp[MENU_MAX] = { m_menuReel[2],m_menuReel[0],m_menuReel[1] };

		memcpy(&m_menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_RETURN])												//menuの選択
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
	//メニューの選択 終了//
}

VOID TitleScene::Render()
{
	//初期化 開始//
	if (m_frame == -1)
	{
		m_frame = 0;

		m_fileManager.CreateTex(_T("Back"), _T("2DTextures/Title/TitleBack.png"));	//画像読み込み
		m_fileManager.CreateTex(_T("Logo"), _T("2DTextures/Title/TitleLogo.png"));
		m_fileManager.CreateTex(_T("WaitInput"), _T("2DTextures/Title/TitleWaitInput.png"));
		m_fileManager.CreateTex(_T("NewGame"), _T("2DTextures/Title/TitleMenuNewGame.png"));
		m_fileManager.CreateTex(_T("LoadGame"), _T("2DTextures/Title/TitleMenuLoadGame.png"));
		m_fileManager.CreateTex(_T("EndGame"), _T("2DTextures/Title/TitleMenuEndGame.png"));
	}
	//初期化 終了//

	D3DXVECTOR2 windowSize;	//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	//背景の描画 開始//クラスにするかもしれない
	D3DXVECTOR3 backCenter(windowSize.x*0.5f, windowSize.y*0.5f, 1.0f);
	D3DXVECTOR2 halfBackScale = windowSize * 0.5f;
	CustomVertex back[4];

	m_pCustomVertices->Create(back, &backCenter, &halfBackScale);		//頂点データのセット

	m_pDraw->Render(back, m_fileManager.GetTex(_T("Back")));			//描画
	//背景の描画 終了//

	//ロゴの描画 開始//クラスにするかもしれない
	D3DXVECTOR3 logoCenter(windowSize.x*0.5f, windowSize.y*0.35f, 1.0f);
	D3DXVECTOR2 halflogoScale(windowSize.x * 0.29f, windowSize.y * 0.2f);
	CustomVertex logo[4];

	m_pCustomVertices->Create(logo, &logoCenter, &halflogoScale, D3DCOLOR_ARGB(230, 255, 255, 255));	//頂点データのセット

	m_pDraw->Render(logo, m_fileManager.GetTex(_T("Logo")));											//描画
	//ロゴの描画 終了//

	if (!m_canSelectMenu)
	{
		//入力待ちテキストの描画 開始//クラスにするかもしれない
		D3DXVECTOR3 waitInputCenter(windowSize.x*0.5f, windowSize.y*0.78f, 1.0f);
		D3DXVECTOR2 halfwaitInputScale(windowSize.x * 0.07f, windowSize.y * 0.035f);
		CustomVertex waitInput[4];

		const int FLASH_COUNT_MAX = 127;																											//flashCountの最大値
		static unsigned char flashCount = FLASH_COUNT_MAX;																							//テキストの点滅に用いるカウンタ

		static bool canCountUp = false;																												//アルファ値の折り返しを決定するフラグ

		m_pCustomVertices->Create(waitInput, &waitInputCenter, &halfwaitInputScale, D3DCOLOR_ARGB((int)(flashCount*1.5f) + 30, 255, 255, 255));		//頂点データのセット

		if (flashCount == FLASH_COUNT_MAX)canCountUp = false;																						//アルファ値の折り返し設定
		if (flashCount == 0)canCountUp = true;

		flashCount = (canCountUp) ? ++flashCount : --flashCount;																					//canCountUpがtrueなら+ falseなら-

		m_pDraw->Render(waitInput, m_fileManager.GetTex(_T("WaitInput")));																			//描画
		//入力待ちテキストの描画 終了//
	}

	if (m_canSelectMenu)
	{
		//menuテキストの描画 開始//クラスにするかもしれない
		for (int i = 0; i < MENU_MAX; ++i)
		{
			D3DXVECTOR3 menuCenter(windowSize.x*0.5f, windowSize.y*(0.65f + 0.07f*i), 1.0f);

			D3DXVECTOR2 halfMenuScale(windowSize.x*0.055f, windowSize.y*0.029f);

			CustomVertex menu[4];

			m_pCustomVertices->Create(menu, &menuCenter, &halfMenuScale, D3DCOLOR_ARGB(200, 255, 255, 255));

			if (i == M_SELECTING_MENU)
			{
				const float SELECTING_MENU_SCALE_MULTIPLY = 1.5f;
				halfMenuScale.x *= SELECTING_MENU_SCALE_MULTIPLY;
				halfMenuScale.y *= SELECTING_MENU_SCALE_MULTIPLY;

				m_pCustomVertices->Create(menu, &menuCenter, &halfMenuScale, D3DCOLOR_ARGB(230, 255, 255, 255));
			}

			switch (m_menuReel[i])
			{
			case NEW_GAME:
				m_pDraw->Render(menu, m_fileManager.GetTex(_T("NewGame")));

				break;

			case LOAD_GAME:
				m_pDraw->Render(menu, m_fileManager.GetTex(_T("LoadGame")));

				break;

			case END_GAME:
				m_pDraw->Render(menu, m_fileManager.GetTex(_T("EndGame")));

				break;

			default:
				break;
			}
		}
		//menuテキストの描画 終了//
	}


	++m_frame;						//初めから何フレームたったか

	if (m_frame < 0)m_frame = 0;	//オーバーフローしたら0代入
}
