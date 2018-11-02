#include"DamageStar.h"
#include "../../../../GameManager/GameManager.h"

VOID DamageStar::Update()
{

}

VOID DamageStar::Render()
{
	m_pGameManager->CopyInstance();
	D3DXVECTOR3 vec3(1.f, 1.f, 1.f);
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Diffuse.r = 1.0f;
	m_Light.Diffuse.g = 1.0f;
	m_Light.Diffuse.b = 1.0f;
	m_Light.Specular.r = 1.0f;
	m_Light.Specular.g = 1.0f;
	m_Light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vec3);
	m_Light.Range = 200.f;

	m_pDirectX3DDevice->SetLight(0, &m_Light);
	m_pDirectX3DDevice->LightEnable(0, TRUE);
	m_pDirectX3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDirectX3DDevice->SetRenderState(D3DRS_AMBIENT, m_Color);

	D3DXMATRIX MatWorld;
	m_pDraw->Render(&m_FbxRelated, &MatWorld);
}

VOID DamageStar::Init()
{
	m_Color = 0xFFFFFFFF;	//îíêF
	m_FbxRelated.LoadFbx("3DModels/EnemyStar/star 3Dmodel.fbx");
}

DamageStar::DamageStar()
{	
}

DamageStar::~DamageStar()
{
}