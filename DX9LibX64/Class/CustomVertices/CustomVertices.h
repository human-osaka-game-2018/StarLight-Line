#pragma once
#include <windows.h>
#include <d3dx9.h>

/**
* @struct CustomVertex
* @brief ���_�f�[�^
*/
struct CustomVertex
{
public:
	D3DXVECTOR3 m_pos;		//! ���W

	FLOAT m_rHW = 1.0f;		//! �d�݂̋t�� ��{1

	DWORD m_aRGB;			//! �F�J���[�R�[�hARGB

	D3DXVECTOR2 m_TexUV;	//! �e�N�X�`���̍��W
};

/**
* @struct CustomVertex
* @brief 3D���_�f�[�^
*/
struct Custom3DVertex
{
public:
	D3DXVECTOR3 m_pos;		//! ���W

	DWORD m_aRGB;			//! �F�J���[�R�[�hARGB

	D3DXVECTOR2 m_TexUV;	//! �e�N�X�`���̍��W
};

/**
* @class CustomVertices
* @brief ���_���̑�����s��
*/
class CustomVertices
{
public:
	/**
	* @fnstatic CustomVertices* GetInstance()
	* @brief singleton�p�̃C���X�^���X�𐶐����A
	*	���̃C���X�^���X�̃|�C���^��Ԃ��֐��A
	*	���łɐ�������Ă����ꍇ���̃C���X�^���X�̃|�C���^��Ԃ�
	* @return �C���X�^���X�̃|�C���^
	* @detail ���̃N���X�̃����om_pCustomVertices��NULL�Ȃ�new���s���A
	*	m_pCustomVertices�ɑ�����߂�l�ŕς����A
	*	���̃N���X��j������ꍇ��VOID DeleteInstance()���g�p����
	*/
	static CustomVertices* GetInstance();

	/**
	* @fnstatic  VOID DeleteInstance()
	* @brief ���̃N���X��j������
	* @return �Ȃ�
	* @detail ���̃N���X�̃����om_pCustomVertices��Delete���Ă��̃N���X��j�����ANULL��������
	*/
	VOID DeleteInstance();

	/**
	* @fn static VOID RotateXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter)
	* @brief XYZ���ɉ�]���s��
	* @param (pCustomVertices) ���_�f�[�^�z��̐擪�A�h���X
	* @param (pDegree) ��]��������x���@�ł̊p�x�̃|�C���^
	* @param (pRelativeRotateCenter) �ǂ�قǉ�]�̒��S����`�̒��S��肸��Ă��邩�̃|�C���^
	* @return �Ȃ�
	* @detail ��]�s����쐬���A��`�̒��S�����߉�]�̒��S�����_�Ɉړ������A��]�s���p���ĉ�]���s�����_�ֈړ������������ɖ߂�
	*/
	VOID RotateXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateX(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateY(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateZ(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateXYZ(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateX(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateY(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateZ(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	/**
	* @fn VOID Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2* pScaleRate)
	* @brief ��`���g�k������
	* @param (pCustomVertices) ���_�f�[�^�z��̐擪�A�h���X
	* @param (pScaleRate) �g�k���̃|�C���^
	* @return �Ȃ�
	* @detail ��`�̒��S�����ߕ��ƍ���������o���A�g�k���𕝂ƍ����Ɋ|�����킹�A��`�̒��S�_����č\��������
	*/
	VOID Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2* pScaleRate);

	VOID Rescale(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR2* pScaleRate);

	/**
	* @fn Move(CustomVertex* pCustomVertices, const D3DXVECTOR3* pMovement)
	* @brief ��`���ړ�������
	* @param (pCustomVertices) ���_�f�[�^�z��̐擪�A�h���X
	* @param (pMovement) �ړ��ʂ̃|�C���^
	* @return �Ȃ�
	*/
	VOID Move(CustomVertex* pCustomVertices, const D3DXVECTOR3* pMovement);

	VOID Move(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pMovement);

	/**
	* @fn Move(CustomVertex* pCustomVertices, const D3DXVECTOR3* pMovement)
	* @brief ��`�������̈ʒu�ɍĔz�u������
	* @param (pCustomVertices) ���_�f�[�^�z��̐擪�A�h���X
	* @param (pCenter) ��`���ړ���������W�̃|�C���^
	* @return �Ȃ�
	*/
	VOID Locale(CustomVertex* pCustomVertices, const D3DXVECTOR3* pPos);

	VOID Locale(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pPos);

	/**
	* @fn VOID SetTexUV(CustomVertex* pCustomVertices, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f)
	* @brief �e�N�X�`�����W�������̍��W�ɕύX������
	* @param (pCustomVertices) ���_�f�[�^�z��̐擪�A�h���X
	* @param (startTU) x�����̃e�N�X�`�����W�̎n�܂�̒l
	* @param (startTV) y�����̃e�N�X�`�����W�̎n�܂�̒l
	* @param (endTU) x�����̃e�N�X�`�����W�̏I���̒l
	* @param (endTV) y�����̃e�N�X�`�����W�̏I���̒l
	* @return �Ȃ�
	*/
	VOID SetTexUV(CustomVertex* pCustomVertices, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	VOID SetTexUV(Custom3DVertex* pCustom3DVertices, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	/**
	* @fn VOID Create(CustomVertex *pCustomVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale,
	*	DWORD color = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f)
	* @brief ���_�f�[�^�\���̂Ɉ����̒l����������
	* @param (pCustomVertices) ���_�f�[�^�z��̐擪�A�h���X
	* @param (pCenter) ��`�̒��S�̃|�C���^
	* @param (pHalfScale) ��`�̍������̔����̃|�C���^
	* @param (color) ���_�̐F�J���[�R�[�hARGB
	* @param (startTU) x�����̃e�N�X�`�����W�̎n�܂�̒l
	* @param (startTV) y�����̃e�N�X�`�����W�̎n�܂�̒l
	* @param (endTU) x�����̃e�N�X�`�����W�̏I���̒l
	* @param (endTV) y�����̃e�N�X�`�����W�̏I���̒l
	* @return �Ȃ�
	*/
	VOID Create(CustomVertex *pCustomVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale,
		DWORD color = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	VOID Create(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale,
		DWORD color = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

private:
	CustomVertices() {};
	~CustomVertices() {};

	static CustomVertices* m_pCustomVertices;		//! singleton�p�̂��̃N���X�̃|�C���^

	static const INT M_RECT_VERTICES_NUM = 4;		//! ��`���\�����钸�_�̐�

	VOID Rotate(CustomVertex* pCustomVertices, const D3DXVECTOR3* pRelativeRotateCenter, const D3DXMATRIX* pMatRotate);

	VOID Rotate(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pRelativeRotateCenter, const D3DXMATRIX* pMatRotate);
};
