/**
* @file Draw.h
* @brief �`��N���X
* @author Harutaka Tsujino
* @date 18-10-2018
*/

#pragma once
#include <windows.h>
#include <map>
#include "../FBX/FbxRelated.h"
#include "../CustomVertices/CustomVertices.h"

struct CustomVertex;

/**
* @class Draw
* @brief �I�u�W�F�N�g�̕`����s��
*/
class Draw
{
public:
	/**
	* @fnstatic Draw* GetInstance()
	* @brief singleton�p�̃C���X�^���X�𐶐����A
	*	���̃C���X�^���X�̃|�C���^��Ԃ��֐��A
	*	���łɐ�������Ă����ꍇ���̃C���X�^���X�̃|�C���^��Ԃ�
	* @return �C���X�^���X�̃|�C���^
	* @detail ���̃N���X�̃����om_pDraw��NULL�Ȃ�new���s���A
	*	m_pDraw�ɑ�����߂�l�ŕς����A
	*	���̃N���X��j������ꍇ��VOID DeleteInstance()���g�p����
	*/
	static Draw* GetInstance();

	/**
	* @fnstatic  VOID DeleteInstance()
	* @brief ���̃N���X��j������
	* @return �Ȃ�
	* @detail ���̃N���X�̃����om_pDraw��Delete���Ă��̃N���X��j�����ANULL��������
	*/
	VOID DeleteInstance();

	/**
	* @fn static VOID SetLPDIRECT3DDEVICE9(LPDIRECT3DDEVICE9 pDirectX3DDevice)
	* @brief �`��ɗp����DirectX��3D�f�o�C�X���󂯎��֐�
	* @param (pDirectX3DDevice)�@�󂯓n��DirectX��3D�f�o�C�X
	* @return �Ȃ�
	* @detail Draw�N���X�̃����o�Ɉ����œn���ꂽDirectX��3D�f�o�C�X��n��
	*/
	static VOID SetLPDIRECT3DDEVICE9(LPDIRECT3DDEVICE9 pDirectX3DDevice);

	/** 
	* @fn virtual VOID Render(const FbxRelated* pFBXModel,
	*	const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 texture = NULL)
	* @brief FBX�̕`����s��
	* @param (pFBXModel) FBX�̃N���X ���f����ǂݍ��񂾌�łȂ��Ƃ����Ȃ�
	* @param (pMatWorld) �g���]�ړ��s����܂Ƃ߂��s��̃|�C���^
	* @param (pTexture) ���f���ɒ���t����e�N�X�`�� �f�t�H���g�ő��݂��Ă���ꍇ��NULL
	* @return �Ȃ�
	* @detail pMatWorld��SetTransform���s��,�����̃e�N�X�`����ݒ肵����
	*	pFBXModel�̃����o�֐���p���`�悷��
	*/
	virtual VOID Render(const FbxRelated* pFBXModel,
		const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = NULL);

	/**
	* @fn virtual VOID Render(const CustomVertex* pCustomVertices,
	*	const LPDIRECT3DTEXTURE9 pTexture = NULL)
	* @brief 2D�̕`����s��
	* @param (pCustomVertices) ���_�f�[�^�̐擪�|�C���^
	* @param (pTexture) �|���S���ɒ���t����e�N�X�`��
	* @return �Ȃ�
	* @detail �����̃e�N�X�`����ݒ肵����ADrawPrimitiveUp��p���`�悷��
	*/
	virtual VOID Render(const CustomVertex* pCustomVertices,
		const LPDIRECT3DTEXTURE9 pTexture = NULL);

	/**
	* @fn virtual VOID Render(const CustomVertex* pCustomVertices,
	*	const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = NULL)
	* @brief 3D�̕`��
	* @param (Custom3DVertex) 3D���_�f�[�^�̐擪�|�C���^
	* @param (pMatWorld) �g���]�ړ��s����܂Ƃ߂��s��̃|�C���^
	* @return �Ȃ�
	* @detail pMatWorld��SetTransform���s���Avirtual VOID Render(const CustomVertex* pCustomVertices,
	*�@	const LPDIRECT3DTEXTURE9 pTexture = NULL)
	*/
	virtual VOID Render(const Custom3DVertex* pCustom3DVertices,
		const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = NULL);

protected:
	static LPDIRECT3DDEVICE9 m_pDirectX3DDevice;		//! DirectX��3D�f�o�C�X

private:
	Draw() {};
	~Draw() {};

	static Draw* m_pDraw;		//! singleton�p�̂��̃N���X�̃|�C���^
};
