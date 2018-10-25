#pragma once
#include "../../../../BaseWorking/BaseWorking.h"
#include <d3dx9.h>
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

/*
*�x�[�X�X�^�[�N���X(���N���X)
*/
class BaseStar:public BaseWorking
{
protected:
	D3DXVECTOR3	m_Pos;				//x,y,z���W
	DWORD m_Color;					//���̐F
	float m_DropPerMinute;			//1���Ԃɂǂꂾ�������Ă��邩
	float m_Time;					//����T�Ă��鎞��
	int m_Division;					//�敪����
	int m_StarsNumInDivision;		//�敪���̒��̐��̐�
};