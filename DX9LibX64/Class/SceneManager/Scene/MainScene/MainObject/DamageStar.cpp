#include"DamageStar.h"
#include "../../../../GameManager/GameManager.h"

VOID DamageStar::Update()
{
	m_pGameManager->CopyInstance();
	m_g
	D3DXMATRIX MatWorld;
	m_pDraw->Render(&m_FbxRelated, &MatWorld);
}

DamageStar::DamageStar()
{
	m_Color = 0xFFFFFFFF;	//”’F
	m_FbxRelated.LoadFbx("3DModels/EnemyStar/star 3Dmodel.fbx");
}