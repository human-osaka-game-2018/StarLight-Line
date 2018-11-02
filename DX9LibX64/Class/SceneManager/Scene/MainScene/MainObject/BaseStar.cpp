#include "BaseStat.h"
#include "../../../../GameManager/GameManager.h"

BaseStar::BaseStar(Scene* pScene):MainObject(pScene)
{
	Init();
}

VOID BaseStar::Init()
{
	m_FbxModel.LoadFbx("3DModels/EnemyStar/EnemyStar");
	PosOfStarYCoordinate();
	m_Timer = Timer::GetInstance();
	m_Timer->Start();

}

VOID BaseStar::PosOfStarYCoordinate()
{
	m_Time = (((m_Division * 4) + m_StarsNumInDivision) * 60.f) / m_DropPerMinute;
}

VOID BaseStar::FollingStarPosYTime(const LONGLONG& CurrentTime)
{
	m_pGameManager->GetDisplaySize(&m_windowSize);
	m_Pos.y = -(m_Time - CurrentTime / 1000.f) + m_windowSize.y;
}