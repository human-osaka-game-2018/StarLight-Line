#pragma once
#include "BaseStat.h"
#include "../../../../FBX/FbxRelated.h"

class DamageStar :public BaseStar
{
public:
	DamageStar();
	~DamageStar();

	VOID Init();
	VOID Update();
	VOID Render();

private:
	int m_Damage;
	FbxRelated m_fbxRelated;
	LPDIRECT3DDEVICE9 m_pDirectX3DDevice;
	D3DLIGHT9 m_light;
};
