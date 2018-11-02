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
	m_Color = 0xFFFFFFFF;	//îíêF
}

DamageStar::DamageStar(Scene* pScene):BaseStar(pScene)
{	
	Init();
}

DamageStar::~DamageStar()
{
}