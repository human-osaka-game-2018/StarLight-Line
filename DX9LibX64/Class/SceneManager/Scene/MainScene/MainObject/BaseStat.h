#pragma once
#include "../../../../Object2DManager/Object2D/Object2D.h"
#include <d3dx9.h>
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

/*
*ベーススタークラス(基底クラス)
*/
class BaseStar :public Object2D
{
public:
	BaseStar() {};
	~BaseStar() {};

	virtual VOID Update() = 0;
	virtual VOID Render() = 0;

protected:
	VOID PosOfStarYCoordinate();								//落ちてくる時間設定関数
	VOID FollingStarPosYTime(const LONGLONG& CurrentTime);		//y座標を移動させる関数

	D3DXVECTOR3	m_Pos;				//x,y,z座標
	DWORD m_Color;					//星の色
	float m_DropPerMinute;			//1分間にどれだけ落ちてくるか
	float m_Time;					//落ちTてくる時間
	int m_Division;					//区分け数
	int m_StarsNumInDivision;		//区分けの中の星の数
};