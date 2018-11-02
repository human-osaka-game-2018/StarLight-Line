#pragma once
#include <windows.h>
#include <tchar.h>
#include "Window\Window.h"
#include "DirectX\DirectX.h"
#include "../CustomVertices/CustomVertices.h"
#include "../Draw/Draw.h"
#include "../FileManager/FileManager.h"
#include "Light\Light.h"

class Light;
class CustomVertices;
class Draw;

struct CustomVertex;
struct Custom3DVertex;
struct ObjectData;

class GameManager
{
public:
	static GameManager* GetInstance(HINSTANCE hInst, TCHAR* pAppName, VOID(*pMainFunc)(), D3DXVECTOR2 displaySize, BOOL canWindown);
	static GameManager* CopyInstance();

	VOID Create();
	VOID GetInputData(InputData** pPInputData);
	INT Release();
	LPDIRECT3DDEVICE9 GetDirectX3DDevice();
	VOID GetDisplaySize(D3DXVECTOR2* pDisplaySize);

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

	/**
	* @brief �e�N�X�`���̍쐬
	* @param (pTexName) �e�N�X�`���ɂ��閼�O
	* @param (pTexturePath) �쐬����e�N�X�`���̃p�X
	* @return �Ȃ�
	*/
	VOID CreateTex(TCHAR* pTexName, TCHAR* pTexturePath);

	/**
	* @brief �쐬�����S�e�N�X�`���̍폜
	* @return �Ȃ�
	*/
	VOID DeleteTex();

	/**
	* @brief �e�N�X�`���̎擾
	* @param (pTexName) �e�N�X�`���̖��O
	* @return LPDIRECT3DTEXTURE9 �e�N�X�`���̃|�C���^
	*/
	LPDIRECT3DTEXTURE9 GetTex(TCHAR* pTexName);

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

	VOID Create(CustomVertex *pCustomVertices, const ObjectData*pObjectData);
	
	/**
	* @brief ���_�f�[�^�̐F�ݒ�
	* @param (pCustomVertices) ���_�f�[�^�̐擪�|�C���^
	* @param (color) �ݒ肷��F�̃J���[�R�[�hARBG
	* @return �Ȃ�
	*/
	VOID SetColor(CustomVertex *pCustomVertices, DWORD color);

	VOID SetLight(D3DLIGHT9* pLight, INT lightIndex);

	VOID SetRenderState(D3DRENDERSTATETYPE renderStateType, DWORD value);

private:
	GameManager(HINSTANCE hInst, TCHAR* pAppName, BOOL canWindow);
	~GameManager();

	VOID InitializeWindow();
	VOID InitializeDirectX();
	VOID UpdateInput();
	VOID LoopMainFunc();

	static VOID(*m_pMainFunc)();
	static GameManager* m_pGameManager;
	static D3DXVECTOR2 m_displaySize;
	static InputData* m_pInputData;
	static Window* m_pWindow;
	static DirectX* m_pDirectX;
	static CustomVertices* m_pCustomVertices;
	static Draw* m_pDraw;
	static FileManager* m_pFileManager;
	Light m_light;
};
