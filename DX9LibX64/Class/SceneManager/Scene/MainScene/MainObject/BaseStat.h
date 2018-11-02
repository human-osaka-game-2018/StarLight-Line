#pragma once
#include "MainObject.h"
#include "../../../../FBX/FbxRelated.h"
#include "../../../../Timer/Timer.h"
#include <d3dx9.h>

/*
*ベーススタークラス
*/
class BaseStar :public MainObject
{
public:
	BaseStar(Scene* pScene);
	~BaseStar() {};

	virtual VOID Init();
	virtual VOID Update() = 0;
	virtual VOID Render();

protected:
	VOID PosOfStarYCoordinate();								//落ちてくる時間設定関数
	VOID FollingStarPosYTime(const LONGLONG& CurrentTime);		//y座標を移動させる関数

	FbxRelated m_FbxModel;			//星型のモデル(落ちる星モデル)
	Timer* m_Timer;					//タイマー
	D3DXVECTOR3	m_Pos;				//x,y,z座標
	DWORD m_Color;					//星の色
	float m_DropPerMinute;			//1分間にどれだけ落ちてくるか
	float m_Time;					//落ちTてくる時間
	int m_Division;					//区分け数
	int m_StarsNumInDivision;		//区分けの中の星の数
};
