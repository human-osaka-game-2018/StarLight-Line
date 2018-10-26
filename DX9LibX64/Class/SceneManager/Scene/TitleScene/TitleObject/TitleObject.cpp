#include <windows.h>
#include "TitleObject.h"
#include "../../../../Object2DManager/Object2D/Object2D.h"

VOID TitleBack::Init()
{
	static bool canInit = true;

	if (!canInit)return;

	canInit = false;

	m_pFileManager->CreateTex(_T("Back"), _T("2DTextures/Title/TitleBack.png"));	//画像読み込み
}

VOID TitleBack::Render()
{
	D3DXVECTOR2 windowSize;	//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	Object2DData data;
	data.m_center = { windowSize.x*0.5f,windowSize.y*0.5f,1.0f };
	data.m_degree = { 0.0f,0.0f,0.0f };
	data.m_color = 0xFFFFFFFF;
	data.m_scale = { windowSize.x * 0.5f ,windowSize.y * 0.5f };

	m_pObject2DDatas.push_back(&data);

	CustomVertex back[4];
	m_pCustomVertices->Create(back, &data);						//頂点データのセット

	m_pDraw->Render(back, m_pFileManager->GetTex(_T("Back")));	//描画
}

VOID TitleLogo::Init()
{
	static bool canInit = true;

	if (!canInit)return;

	canInit = false;

	m_pFileManager->CreateTex(_T("Back"), _T("2DTextures/Title/TitleBack.png"));	//画像読み込み
}

VOID TitleLogo::Render()
{
	D3DXVECTOR2 windowSize;	//windowのサイズ
	m_pGameManager->GetDisplaySize(&windowSize);

	Object2DData data;
	data.m_center = { windowSize.x*0.5f,windowSize.y*0.35f,0.98f };
	data.m_degree = { 0.0f,0.0f,0.0f };
	data.m_color = D3DCOLOR_ARGB(230, 255, 255, 255);
	data.m_scale = { windowSize.x * 0.29f ,windowSize.y * 0.2f };

	CustomVertex logo[4];

	m_pCustomVertices->Create(logo, &data);						//頂点データのセット

	m_pDraw->Render(logo, m_pFileManager->GetTex(_T("Logo")));	//描画
}

VOID TitleInputPrompt::Init()
{


}
