#pragma once
#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>

//���̓f�o�C�X�񋓑�
enum class INPUT_DEVICES
{
	//�L�[�{�[�h
	KEYBOARD,

	//�}�E�X
	MOUSE,

	//���̓f�o�C�X�̎�ނ̍ő吔
	MAX_INPUT_DEVICES
};

//�L�[�{�[�h�̓��͏�ԍ\����
struct KeyBoardState
{
public:

	//���݂Ńt���[���̃L�[�{�[�h�̃L�[��������Ă����ꍇ��ʃr�b�g������
	BYTE m_diks[256];

	//�O��̂Ńt���[���̃L�[�{�[�h�̃L�[��������Ă����ꍇ��ʃr�b�g������
	BYTE m_diksPrev[256];

	//�L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ̃t���[������TRUE
	BOOL m_keyPush[256];

	//�L�[�{�[�h�̃L�[�������ꑱ�����Ă����TRUE
	BOOL m_keyHold[256];

	//�L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ̃t���[������TRUE
	BOOL m_keyRelease[256];

	//�L�[�{�[�h�̃L�[���O��ƌ��݂̃t���[���ŉ�����Ă��Ȃ���TRUE
	BOOL m_keyUninput[256];
};

//�}�E�X�̃J�[�\���̈ʒu�{�^���̓��͏�ԍ\����
struct MouseState
{
public:

	//���݂̃t���[���ł̑O��̃J�[�\���ʒu����̑��Έʒu�ƃ{�^���̓��͏��
	DIMOUSESTATE m_mouseState;

	//�O��̃t���[���ł̑O��̃J�[�\���ʒu����̑��Έʒu�ƃ{�^���̓��͏��
	DIMOUSESTATE m_mouseStatePrev;

	//�J�[�\���̐�΍��W
	POINT m_absolutePos;

	//�}�E�X�̃{�^���������ꂽ�u�Ԃ̃t���[������TRUE
	BOOL m_buttonPush[4];

	//�}�E�X�̃{�^���������ꑱ�����Ă����TRUE
	BOOL m_buttonHold[4];

	//�}�E�X�̃{�^���������ꂽ�u�Ԃ̃t���[������TRUE
	BOOL m_buttonRelease[4];

	//�}�E�X�̃{�^�����O��ƌ��݂̃t���[���ŉ�����Ă��Ȃ���TRUE
	BOOL m_buttonUninput[4];
};

//�C���^�[�t�F�C�X��p���邱�Ƃɂ���ċ@�\���������Ƌ@�\�ǉ������Ő؂藣�����Ƃ��ł���
//����ɂ��V�����@�\���g������ꍇ�ɏC�����y�ɂȂ�

//DirectX�̃I�u�W�F�N�g�������C���^�[�t�F�C�X
class IDirectXObjectInitializer
{
public:
	IDirectXObjectInitializer() {};
	~IDirectXObjectInitializer() {};

	virtual HRESULT Initialize(BOOL canWindow) = 0;
};

//DirectX�̃I�u�W�F�N�g�������N���X
class DirectXObjectInitializer :public IDirectXObjectInitializer
{
	friend class DirectXObject;

public:
	HRESULT Initialize(BOOL canWindow);

private:
	DirectXObjectInitializer() {};
	~DirectXObjectInitializer() {};

	VOID SetBuckBuffer(BOOL canWindow);
};

//DirectX�̃I�u�W�F�N�g�N���X
class DirectXObject
{
	friend class DirectX;

public:
	HRESULT Initialize();
	VOID SetWindowMode(BOOL canWindow);

private:
	DirectXObject() :m_canWindow(TRUE) {};
	~DirectXObject() {};

	BOOL m_canWindow;
	IDirectXObjectInitializer* m_pDirectXObjectInitializer;
};

//�|���S���̒��_�f�[�^
typedef DWORD t_VERTEX_FORMAT;

//DirectX��3D�f�o�C�X�������C���^�[�t�F�C�X
class IDirectX3DDeviceInitializer
{
public:
	IDirectX3DDeviceInitializer() {};
	~IDirectX3DDeviceInitializer() {};

	virtual HRESULT Initialize(t_VERTEX_FORMAT d3DFVF, BOOL canCullPolygon) = 0;

private:
};

//DirectX��3D�f�o�C�X�������N���X
class DirectX3DDeviceInitializer :public IDirectX3DDeviceInitializer
{
	friend class DirectX3DDevice;

public:
	HRESULT Initialize(t_VERTEX_FORMAT d3DFVF, BOOL canCullPolygon);

private:
	DirectX3DDeviceInitializer() {};
	~DirectX3DDeviceInitializer() {};

	VOID SetRenderState(BOOL canCullPolygon);
	VOID SetTextureStageState();
	VOID SetViewPort();
};

class Camera
{
	friend class DirectX3DDevice;

public:
	VOID SetTransform();
	VOID SetCameraPos(FLOAT x, FLOAT y, FLOAT z);
	VOID GetCameraPos(D3DXVECTOR3* pCameraPos);
	VOID SetEyePoint(FLOAT x, FLOAT y, FLOAT z);
	VOID GetEyePoint(D3DXVECTOR3* pEyePoint);
	VOID NegateView(D3DXMATRIX* pMatRotate);

protected:
	Camera();
	~Camera() {};

	D3DXVECTOR3 m_cameraPos;
	D3DXVECTOR3 m_eyePoint;
	D3DXVECTOR3 m_cameraOverhead;
	D3DXMATRIX m_view;
};

//class FPSCamera :public Camera
//{
//public:
//	VOID Move();
//	VOID Jump();
//	VOID LockOn();
//
//private:
//	FLOAT m_dashSpeedMultiply;
//	FLOAT m_defaultSpeedMultiply;
//	FLOAT m_sneakSpeedMultiply;
//
//}

//DirectX��3D�f�o�C�X�N���X
class DirectX3DDevice
{
	friend class DirectX;

public:
	HRESULT Initialize();
	VOID SetCullPolygon(BOOL canCullPolygon);
	VOID SetVertexFormat(t_VERTEX_FORMAT d3DFVF);
	VOID PrepareRender();
	VOID CleanUpRender();

	template<typename T>
	VOID DrawVertex(const T* pVertex, const LPDIRECT3DTEXTURE9* pTexture, DWORD fVF, size_t size)
	{
		DirectX* pDirectX = DirectX::GetInstance();
		DirectXInstances& rDirectXInstances = pDirectX->GetDirectXInstances();
		LPDIRECT3DDEVICE9& rpDirectX3DDevice = rDirectXInstances.m_pDirectX3DDevice;

		LPDIRECT3DVERTEXBUFFER9 vertexBuffer = NULL;

		rpDirectX3DDevice->CreateVertexBuffer(
			(UINT)size,
			D3DUSAGE_WRITEONLY,
			fVF,
			D3DPOOL_MANAGED,
			&vertexBuffer,
			NULL);

		T* pVertexTmp;

		vertexBuffer->Lock(0, 0, (VOID**)&pVertexTmp, 0);

		memcpy(pVertexTmp, pVertex, size);

		vertexBuffer->Unlock();

		rpDirectX3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(T));

		rpDirectX3DDevice->SetTexture(0, *pTexture);

		const INT TRIANGLE_VERTICES_NUM = 3;
		const UINT TRIANGLE_NUM = (UINT)size / sizeof(T) - (TRIANGLE_VERTICES_NUM - 1);

		HRESULT hr = rpDirectX3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, TRIANGLE_NUM);

		vertexBuffer->Release();
	}

	VOID SetFont(INT scaleX, UINT scaleY, const TCHAR *pFontType, LPD3DXFONT *pFontId, UINT thickness = 0, INT charSet = SHIFTJIS_CHARSET);

	VOID WriteText(INT posX, INT posY, const TCHAR *pText, UINT format, LPD3DXFONT pFontId, DWORD color);

	Camera m_camera;

private:
	DirectX3DDevice() :m_canCullPolygon(TRUE), m_d3DFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE) {};
	~DirectX3DDevice() {};

	BOOL m_canCullPolygon;
	t_VERTEX_FORMAT m_d3DFVF;
	IDirectX3DDeviceInitializer* m_pDirectX3DDeviceInitializer;
};

//DirectX��XInput�������C���^�[�t�F�C�X
class IDirectXInputDevicesInitializer
{
public:
	IDirectXInputDevicesInitializer() {};
	~IDirectXInputDevicesInitializer() {};

	virtual HRESULT Initialize() = 0;
};

//DirectXInput�������N���X
class DirectXInputDevicesInitializer :public IDirectXInputDevicesInitializer
{
	friend class DirectXInputDevices;

public:
	DirectXInputDevicesInitializer() {};
	~DirectXInputDevicesInitializer() {};

	HRESULT Initialize();
};

//���̓f�o�C�X�̃f�[�^�\����
struct InputData
{
public:
	KeyBoardState m_keyBoardState;
	MouseState m_mouseState;
};

//���̓f�o�C�X�f�[�^�ۑ��C���^�[�t�F�C�X
class IInputStatesStorage
{
public:
	IInputStatesStorage() {};
	~IInputStatesStorage() {};

	virtual VOID Store(InputData& rInputData) = 0;
};

//�}�E�X�L�[�{�[�h �̓��̓f�[�^�ۑ��N���X
class MouseAndKeyboardStatesStorage :public IInputStatesStorage
{
	friend class DirectXInputDevices;

public:
	MouseAndKeyboardStatesStorage() {};
	~MouseAndKeyboardStatesStorage() {};

	VOID Store(InputData& rInputData);
};

//���̓f�o�C�X�f�[�^�擾�C���^�[�t�F�C�X
class IInputStatesGetter
{
public:
	IInputStatesGetter() {};
	~IInputStatesGetter() {};

	virtual VOID Get(InputData& rInputData) = 0;
};

//�}�E�X�L�[�{�[�h �̓��̓f�[�^�擾�N���X
class MouseAndKeyboardStatesGetter :public IInputStatesGetter
{
	friend class DirectXInputDevices;

public:
	MouseAndKeyboardStatesGetter() {};
	~MouseAndKeyboardStatesGetter() {};

	VOID Get(InputData& rInputData);
};

//DirectXInput�N���X
class DirectXInputDevices
{
	friend class DirectX;

public:
	HRESULT Initialize();
	VOID StoreInputStates();
	VOID GetInputStates();
	VOID GetInputData(InputData* pInputData);

private:
	DirectXInputDevices();
	~DirectXInputDevices() {};

	InputData m_InputData;
	IDirectXInputDevicesInitializer * m_pDirectXInputDevicesInitializer;
	IInputStatesStorage* m_pInputStatesStoreter;
	IInputStatesGetter* m_pInputStatesGetter;
};

class DirectX;

//DirectX�֌W�̃C���X�^���X�\����
struct DirectXInstances
{
public:
	HWND * m_pHWnd = NULL;
	LPDIRECT3D9 m_pDirectX;
	LPDIRECT3DDEVICE9 m_pDirectX3DDevice;
	LPDIRECTINPUT8 m_pDirectXInput;
	LPDIRECTINPUTDEVICE8 m_pDirectXInputDevices[(ULONGLONG)INPUT_DEVICES::MAX_INPUT_DEVICES];
	LPD3DXFONT m_pDirectXFont;
	D3DPRESENT_PARAMETERS m_DirectXPresentParam;
	DirectX* m_pDirectXClass = NULL;
};

//DirectX�N���X
class DirectX
{
public:
	static DirectX* GetInstance();
	VOID DeleteInstance();
	VOID SetHWND(HWND* pHWnd);
	DirectXInstances& GetDirectXInstances();

	DirectXObject m_DirectXObject;
	DirectX3DDevice m_DirectX3DDevice;
	DirectXInputDevices m_DirectXInputDevices;

private:
	DirectX() {};
	~DirectX();

	static DirectXInstances m_directXInstances;
};
