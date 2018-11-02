#include "BaseStat.h"
#include "../../../../GameManager/GameManager.h"

VOID BaseStar::PosOfStarYCoordinate()
{
	m_Time = (((m_Division * 4) + m_StarsNumInDivision) * 60.f) / m_DropPerMinute;
}

VOID BaseStar::FollingStarPosYTime(const LONGLONG& CurrentTime)
{
	m_pGameManager->CopyInstance();
	m_pGameManager->GetDisplaySize(&m_windowSize);
	m_Pos.y = -(m_Time - CurrentTime / 1000.f) + m_windowSize.y;
}