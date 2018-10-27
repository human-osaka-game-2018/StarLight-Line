#pragma once
#include <d3dx9.h>
#include "../../../../BaseWorking/BaseWorking.h"

class  BaseWorking;

/*
*�x�[�X�X�^�[�N���X(���N���X)
*/
class BaseStar:public BaseWorking
{
public:
	BaseStar() {};
	~BaseStar() {};

protected:
	VOID PosOfStarYCoordinate();
	VOID FollingStarPosYTime(const LONGLONG& CurrentTime);

	D3DXVECTOR3	m_Pos;				//x,y,z���W
	DWORD m_Color;					//���̐F
	float m_DropPerMinute;			//1���Ԃɂǂꂾ�������Ă��邩
	float m_Time;					//����T�Ă��鎞��
	int m_Division;					//�敪����
	int m_StarsNumInDivision;		//�敪���̒��̐��̐�
};
