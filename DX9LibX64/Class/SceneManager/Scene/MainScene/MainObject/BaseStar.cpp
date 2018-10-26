#include "BaseStat.h"
#include "../../../../GameManager/GameManager.h"

VOID BaseStar::PosOfStarYCoordinate()
{
	m_Time = ((m_Division * 4 + m_StarsNumInDivision) * 60.f) / m_DropPerMinute;
}

VOID BaseStar::FollingStarPosYTime(const LONGLONG& CurrentTime)
{
	static GameManager* pGameManager = GameManager::CopyInstance();
	D3DXVECTOR2 DisplaySize;
	pGameManager->GetDisplaySize(&DisplaySize);
	m_Pos.y = -(m_Time - CurrentTime / 1000.f) + DisplaySize.y;
}