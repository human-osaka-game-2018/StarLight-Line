#pragma once
#include "BaseStat.h"
#include "../../../../FBX/FbxRelated.h"
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

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
	FbxRelated m_FbxRelated;
	LPDIRECT3DDEVICE9 m_pDirectX3DDevice;
	D3DLIGHT9 m_Light;
};