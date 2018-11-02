#pragma once
#include "MainObject.h"
#include "../../../../FBX/FbxRelated.h"
#include "../../../../Timer/Timer.h"
#include <d3dx9.h>

/*
*�x�[�X�X�^�[�N���X
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
	VOID PosOfStarYCoordinate();								//�����Ă��鎞�Ԑݒ�֐�
	VOID FollingStarPosYTime(const LONGLONG& CurrentTime);		//y���W���ړ�������֐�

	FbxRelated m_FbxModel;			//���^�̃��f��(�����鐯���f��)
	Timer* m_Timer;					//�^�C�}�[
	D3DXVECTOR3	m_Pos;				//x,y,z���W
	DWORD m_Color;					//���̐F
	float m_DropPerMinute;			//1���Ԃɂǂꂾ�������Ă��邩
	float m_Time;					//����T�Ă��鎞��
	int m_Division;					//�敪����
	int m_StarsNumInDivision;		//�敪���̒��̐��̐�
};
