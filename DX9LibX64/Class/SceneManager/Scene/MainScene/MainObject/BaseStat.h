#pragma once
#include "../../../../Object2DManager/Object2D/Object2D.h"
#include <d3dx9.h>

/*
*/
class BaseStar :public Object
{
public:
	BaseStar() {};
	~BaseStar() {};

	virtual VOID Init() = 0;
	virtual VOID Update() = 0;
	virtual VOID Render() = 0;

protected:
	VOID PosOfStarYCoordinate();								//—‚¿‚Ä‚­‚éŠÔİ’èŠÖ”
	VOID FollingStarPosYTime(const LONGLONG& CurrentTime);		//yÀ•W‚ğˆÚ“®‚³‚¹‚éŠÖ”

	D3DXVECTOR3	m_Pos;				//x,y,zÀ•W
	DWORD m_Color;					//¯‚ÌF
	float m_DropPerMinute;			//1•ªŠÔ‚É‚Ç‚ê‚¾‚¯—‚¿‚Ä‚­‚é‚©
	float m_Time;					//—‚¿T‚Ä‚­‚éŠÔ
	int m_Division;					//‹æ•ª‚¯”
	int m_StarsNumInDivision;		//‹æ•ª‚¯‚Ì’†‚Ì¯‚Ì”
};
