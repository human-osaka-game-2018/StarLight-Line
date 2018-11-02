#include <windows.h>
#include <tchar.h>
#include <d3dx9.h>
#include <dinput.h>
#include <crtdbg.h>
#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include "Main.h"
#include "../Class/GameManager/GameManager.h"
#include "../Class/SceneManager/SceneManager.h"
#include "../Class/FBX/FbxRelated.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#pragma comment(lib,"d3dx9d.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")

VOID MainFunc()
{
	SceneManager* pSceneManager = SceneManager::GetInstance();

	pSceneManager->Update();
	pSceneManager->Render();
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	D3DXVECTOR2 displaySize(1280.0f, 720.0f);

	GameManager* pGameManager = GameManager::GetInstance(hInst, _T("TEST_TEST_TEST"), MainFunc, displaySize, TRUE);

	SceneManager* pSceneManager = SceneManager::GetInstance();

	pGameManager->Create();

	pSceneManager->Release();

	return pGameManager->Release();
}
