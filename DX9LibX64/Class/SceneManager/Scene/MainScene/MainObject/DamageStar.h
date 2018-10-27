#pragma once
#include "BaseStat.h"

class DamageStar :public BaseStar
{
public:
	VOID Update();
	VOID Render();

private:
	int m_Damage;
};