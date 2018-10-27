#include "MainScene.h"
#include "../../../CustomVertices/CustomVertices.h"
#include "../../../Draw/Draw.h"

VOID MainScene::Update()
{
}

VOID MainScene::Render()
{
	D3DXVECTOR2 BackGroundHalfScale;
	m_pGameManager->GetDisplaySize(&BackGroundHalfScale);
	BackGroundHalfScale /= 2;

	D3DXVECTOR3 BackGroundCenterPos(BackGroundHalfScale.x, BackGroundHalfScale.y, 1.0f);
	CustomVertex BackGround[4];

	m_pGameManager->Create(BackGround, &BackGroundCenterPos, &BackGroundHalfScale);
	m_pGameManager->Render(BackGround, m_pGameManager->GetTex(_T("BackGround")));
}

MainScene::MainScene()
{
	m_pGameManager->CreateTex(_T("BackGround"), _T("2DTextures/reticle_line.png"));
}
