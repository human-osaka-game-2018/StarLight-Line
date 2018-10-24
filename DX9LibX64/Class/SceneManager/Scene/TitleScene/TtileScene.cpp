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

	//メニューの選択 開始//
	static MenuID menuReel[MENU_MAX] = { END_GAME,NEW_GAME,LOAD_GAME };

	const int SelectingMenu = 1;												//現在選ばれているmenuが入っているmenuReelの要素番号

	if (rKeyState.m_keyPush[DIK_W] || rKeyState.m_keyPush[DIK_UP])				//menuの切替
	{
		MenuID menuReelTmp[MENU_MAX] = { menuReel[1],menuReel[2],menuReel[0] };	//ボタンが押されるとmenuReelの中身がずれていく

		memcpy(&menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_S] || rKeyState.m_keyPush[DIK_DOWN])
	{
		MenuID menuReelTmp[MENU_MAX] = { menuReel[2],menuReel[0],menuReel[1] };

		memcpy(&menuReel, &menuReelTmp, sizeof(MenuID)*MENU_MAX);
	}

	if (rKeyState.m_keyPush[DIK_RETURN])										//menuの選択
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
	//メニューの選択 終了//
}

VOID TitleScene::Render()
{
	//ライトの設定　開始//クラスにする予定
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	D3DXVECTOR3 vecDirection(-0.5f, -1.0f, 1.0f);	//ライトの方向
	light.Direction = vecDirection;

	light.Type = D3DLIGHT_DIRECTIONAL;	//ライトの種類 今回は直線ライト

	light.Diffuse.r = 1.5f;	//ライトの色の設定
	light.Diffuse.g = 1.5f;
	light.Diffuse.b = 1.5f;

	light.Specular.r = 10.0f;
	light.Specular.b = 10.0f;
	light.Specular.g = 10.0f;

	light.Ambient.r = 10.f;
	light.Ambient.b = 10.f;
	light.Ambient.g = 10.f;

	light.Range = 0.f;	//ライトの範囲　直線ライトの場合は必要ない

	LPDIRECT3DDEVICE9 pDirectX3DDevice = m_pGameManager->GetDirectX3DDevice();	//3Dデバイスの取得
	pDirectX3DDevice->SetLight(0, &light);	//0番目のカメラに設定
	pDirectX3DDevice->LightEnable(0, TRUE);	//ライトを有効化
	//ライトの設定　終了//
}
