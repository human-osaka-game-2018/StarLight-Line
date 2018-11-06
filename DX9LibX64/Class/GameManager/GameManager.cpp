#include <windows.h>
#include <tchar.h>
#include <d3dx9.h>
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#include "GameManager.h"
#include "Window\Window.h"
#include "DirectX\DirectX.h"
#include "../FPS/FPS.h"
#include "../CustomVertices/CustomVertices.h"
#include "../Draw/Draw.h"
#include "../FileManager/FileManager.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

VOID(*GameManager::m_pMainFunc)();
GameManager* GameManager::m_pGameManager;
D3DXVECTOR2 GameManager::m_displaySize;
InputData* GameManager::m_pInputData;
Window* GameManager::m_pWindow;
DirectX* GameManager::m_pDirectX;
CustomVertices* GameManager::m_pCustomVertices;
Draw* GameManager::m_pDraw;
FileManager* GameManager::m_pFileManager;

class CustomVertices;

GameManager* GameManager::GetInstance(HINSTANCE hInst, TCHAR* pAppName, VOID(*pMainFunc)(), D3DXVECTOR2 displaySize, BOOL canWindow)
{
	if (!m_pGameManager)
	{
		if (canWindow)
		{
			m_displaySize = displaySize;
		}

		if (!canWindow)
		{
			m_displaySize = { 1280.0f,720.0f };
		}

		m_pMainFunc = pMainFunc;
		m_pGameManager = new GameManager(hInst, pAppName, canWindow);
	}

	return m_pGameManager;
}

GameManager* GameManager::CopyInstance()
{
	return m_pGameManager;
}

GameManager::GameManager(HINSTANCE hInst, TCHAR* pAppName, BOOL canWindow)
{
	m_pWindow = Window::GetInstance(hInst, pAppName);
	m_pWindow->SetSizeDisplay(m_displaySize);
	m_pWindow->SetWindowMode(canWindow);

	m_pDirectX = DirectX::GetInstance();
	m_pDirectX->m_DirectXObject.SetWindowMode(canWindow);
}

GameManager::~GameManager()
{
}

D3DPRESENT_PARAMETERS* GameManager::GetD3DPRESENT_PARAMETERS()
{
	return m_pDirectX->GetDirectXInstances().m_pDirectXPresentParam;
}

VOID GameManager::SetBackBufferSize(INT width, INT height)
{
	D3DPRESENT_PARAMETERS* pDirectXPresentParam = m_pDirectX->GetDirectXInstances().m_pDirectXPresentParam;

	pDirectXPresentParam->BackBufferWidth = width;
	pDirectXPresentParam->BackBufferHeight = height;
}

VOID GameManager::Create()
{
	InitializeWindow();
	InitializeDirectX();

	m_pCustomVertices = CustomVertices::GetInstance();
	m_pDraw = Draw::GetInstance(GetDirectX3DDevice());
	m_pFileManager = FileManager::GetInstace(GetDirectX3DDevice());
	Light::SetLPDIRECT3DDEVICE9(GetDirectX3DDevice());

	LoopMainFunc();
}

VOID GameManager::InitializeDirectX()
{
	m_pDirectX->SetHWND(m_pWindow->GetHWNDPtr());

	m_pDirectX->m_DirectXObject.Initialize();
	m_pDirectX->m_DirectX3DDevice.Initialize();
	m_pDirectX->m_DirectXInputDevices.Initialize();
}

VOID GameManager::InitializeWindow()
{
	m_pWindow->MakeWindow();
}

VOID GameManager::UpdateInput()
{
	DirectXInputDevices& rDirectXInputDevices = m_pDirectX->m_DirectXInputDevices;
	rDirectXInputDevices.StoreInputStates();
	rDirectXInputDevices.GetInputStates();
	rDirectXInputDevices.GetInputData(&m_pInputData);
}

VOID GameManager::GetInputData(InputData** pPInputData)
{
	*pPInputData = m_pInputData;
}

VOID GameManager::LoopMainFunc()
{
	DirectX3DDevice& rDirectX3DDevice = m_pDirectX->m_DirectX3DDevice;

	FPS* pFPS = FPS::GetInstance();


	while (m_pWindow->GetMSG().message != WM_QUIT)
	{
		if (!m_pWindow->ConfirmMessage())
		{
			continue;
		}

		pFPS->UpdateTime();

		if (pFPS->CoordinateFrame())
		{
			UpdateInput();
			rDirectX3DDevice.PrepareRender();
			m_pDirectX->m_DirectX3DDevice.m_camera.SetTransform();
			m_pMainFunc();
			rDirectX3DDevice.CleanUpRender();
		}
	}

	pFPS->Release();
}

LPDIRECT3DDEVICE9 GameManager::GetDirectX3DDevice()
{
	DirectXInstances& DirectXInstances = m_pDirectX->GetDirectXInstances();

	return DirectXInstances.m_pDirectX3DDevice;
}

INT GameManager::Release()
{
	INT returnValue = (INT)m_pWindow->GetMSG().wParam;

	m_pWindow->Release();
	m_pWindow = NULL;

	m_pDirectX->Release();
	m_pDirectX = NULL;

	m_pCustomVertices->Release();
	m_pCustomVertices = NULL;

	m_pDraw->Release();
	m_pDraw = NULL;

	m_pFileManager->Release();
	m_pFileManager = NULL;

	delete m_pGameManager;
	m_pGameManager = NULL;

	return returnValue;
}

VOID GameManager::GetDisplaySize(D3DXVECTOR2* pDisplaySize)
{
	*pDisplaySize = m_displaySize;
}

VOID GameManager::Render(const FbxRelated* pFBXModel,
	const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pDraw->Render(pFBXModel, pMatWorld, pTexture);
}

VOID GameManager::Render(const CustomVertex* pCustomVertices,
	const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pDraw->Render(pCustomVertices, pTexture);
}

VOID GameManager::Render(const Custom3DVertex* pCustom3DVertices,
	const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pDraw->Render(pCustom3DVertices, pMatWorld, pTexture);
}

VOID GameManager::CreateTex(TCHAR* pTexName, TCHAR* pTexturePath)
{
	m_pFileManager->CreateTex(pTexName, pTexturePath);
}

VOID GameManager::DeleteTex()
{
	m_pFileManager->DeleteTex();
}

LPDIRECT3DTEXTURE9 GameManager::GetTex(TCHAR* pTexName)
{
	return m_pFileManager->GetTex(pTexName);
}

VOID GameManager::RotateXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateXYZ(pCustomVertices, pDegree, pRelativeRotateCenter);
}

VOID GameManager::RotateX(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateX(pCustomVertices, degree, pRelativeRotateCenter);
}

VOID GameManager::RotateY(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateY(pCustomVertices, degree, pRelativeRotateCenter);
}

VOID GameManager::RotateZ(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateZ(pCustomVertices, degree, pRelativeRotateCenter);
}

VOID GameManager::RotateXYZ(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateXYZ(pCustom3DVertices, pDegree, pRelativeRotateCenter);
}

VOID GameManager::RotateX(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateX(pCustom3DVertices, degree, pRelativeRotateCenter);
}

VOID GameManager::RotateY(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateY(pCustom3DVertices, degree, pRelativeRotateCenter);
}

VOID GameManager::RotateZ(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter)
{
	m_pCustomVertices->RotateZ(pCustom3DVertices, degree, pRelativeRotateCenter);
}

VOID GameManager::Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2* pScaleRate)
{
	m_pCustomVertices->Rescale(pCustomVertices, pScaleRate);
}

VOID GameManager::Rescale(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR2* pScaleRate)
{
	m_pCustomVertices->Rescale(pCustom3DVertices, pScaleRate);
}

VOID GameManager::Move(CustomVertex* pCustomVertices, const D3DXVECTOR3* pMovement)
{
	m_pCustomVertices->Move(pCustomVertices, pMovement);
}

VOID GameManager::Move(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pMovement)
{
	m_pCustomVertices->Move(pCustom3DVertices, pMovement);
}

VOID GameManager::Locale(CustomVertex* pCustomVertices, const D3DXVECTOR3* pPos)
{
	m_pCustomVertices->Locale(pCustomVertices, pPos);
}

VOID GameManager::Locale(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pPos)
{
	m_pCustomVertices->Locale(pCustom3DVertices, pPos);
}

VOID GameManager::SetTexUV(CustomVertex* pCustomVertices, FLOAT startTU, FLOAT startTV, FLOAT endTU, FLOAT endTV)
{
	m_pCustomVertices->SetTexUV(pCustomVertices, startTU, startTV, endTU, endTV);
}

VOID GameManager::SetTexUV(Custom3DVertex* pCustom3DVertices, FLOAT startTU, FLOAT startTV, FLOAT endTU, FLOAT endTV)
{
	m_pCustomVertices->SetTexUV(pCustom3DVertices, startTU, startTV, endTU, endTV);
}

VOID GameManager::Create(CustomVertex* pCustomVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale, DWORD color, FLOAT startTU, FLOAT startTV, FLOAT endTU, FLOAT endTV)
{
	m_pCustomVertices->Create(pCustomVertices, pCenter, pHalfScale, color, startTU, startTV, endTU, endTV);
}

VOID GameManager::Create(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale, DWORD color, FLOAT startTU, FLOAT startTV, FLOAT endTU, FLOAT endTV)
{
	m_pCustomVertices->Create(pCustom3DVertices, pCenter, pHalfScale, color, startTU, startTV, endTU, endTV);
}

VOID GameManager::Create(CustomVertex* pCustomVertices, const ObjectData* pObjectData)
{
	m_pCustomVertices->Create(pCustomVertices, pObjectData);
}

VOID GameManager::SetColor(CustomVertex* pCustomVertices, DWORD color)
{
	m_pCustomVertices->SetColor(pCustomVertices, color);
}

VOID GameManager::SetLight(D3DLIGHT9* pLight, INT lightIndex)
{
	m_light.SetLight(pLight, lightIndex);
}

VOID GameManager::SetRenderState(D3DRENDERSTATETYPE renderStateType, DWORD value)
{
	m_pDirectX->SetRenderState(renderStateType, value);
}

VOID GameManager::SetEnable3DDevice(BOOL enable3DDevice)
{
	m_enable3DDevice = enable3DDevice;
}

BOOL GameManager::GetEnable3DDevice()
{
	return m_enable3DDevice;
}

VOID GameManager::ChangeDisplayMode()
{
	m_pDirectX->ChangeDisplayMode();
}

HRESULT GameManager::ChangeWindowSize()
{
	return m_pDirectX->ChangeWindowSize();
}
