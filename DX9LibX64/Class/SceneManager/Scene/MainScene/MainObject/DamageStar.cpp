#include"DamageStar.h"
#include "../../../../GameManager/GameManager.h"

VOID DamageStar::Update()
{
	FollingStarPosYTime(m_Timer->GetMilliSecond());
}

VOID DamageStar::Render()
{
	
}

VOID DamageStar::Init()
{
	m_Color = 0xFFFFFFFF;	//���F
}

DamageStar::DamageStar(Scene* pScene):BaseStar(pScene)
{	
	Init();
}

DamageStar::~DamageStar()
{
}