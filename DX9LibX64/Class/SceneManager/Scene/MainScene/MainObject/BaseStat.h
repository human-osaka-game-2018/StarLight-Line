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
	VOID PosOfStarYCoordinate();								//�����Ă��鎞�Ԑݒ�֐�
	VOID FollingStarPosYTime(const LONGLONG& CurrentTime);		//y���W���ړ�������֐�

	D3DXVECTOR3	m_Pos;				//x,y,z���W
	DWORD m_Color;					//���̐F
	float m_DropPerMinute;			//1���Ԃɂǂꂾ�������Ă��邩
	float m_Time;					//����T�Ă��鎞��
	int m_Division;					//�敪����
	int m_StarsNumInDivision;		//�敪���̒��̐��̐�
};
