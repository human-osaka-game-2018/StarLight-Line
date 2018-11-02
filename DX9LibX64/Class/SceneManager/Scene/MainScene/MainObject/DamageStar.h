#pragma once
#include "BaseStat.h"
#include "../../../../FBX/FbxRelated.h"

class DamageStar :public BaseStar
{
public:
	DamageStar(Scene* pScene);
	~DamageStar();

	VOID Init();
	VOID Update();
	VOID Render();

};
