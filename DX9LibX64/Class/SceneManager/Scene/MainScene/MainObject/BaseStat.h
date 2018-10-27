#pragma once
#include <d3dx9.h>
#include "../../../../BaseWorking/BaseWorking.h"

class  BaseWorking;

/*
*ベーススタークラス(基底クラス)
*/
class BaseStar:public BaseWorking
{
public:
	BaseStar() {};
	~BaseStar() {};

protected:
	VOID PosOfStarYCoordinate();
	VOID FollingStarPosYTime(const LONGLONG& CurrentTime);

	D3DXVECTOR3	m_Pos;				//x,y,z座標
	DWORD m_Color;					//星の色
	float m_DropPerMinute;			//1分間にどれだけ落ちてくるか
	float m_Time;					//落ちTてくる時間
	int m_Division;					//区分け数
	int m_StarsNumInDivision;		//区分けの中の星の数
};
