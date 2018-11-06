#pragma once
#include <windows.h>
#include <d3dx9.h>
#include "../GameManager.h"

class GameManager;

class Window
{
public:
	static Window* GetInstance(const HINSTANCE hInst, TCHAR* pAppName);
	VOID SetSizeDisplay(D3DXVECTOR2 displaySize);
	VOID SetWindowMode(BOOL canWindow);
	VOID MakeWindow();
	HWND* GetHWNDPtr();
	MSG GetMSG();
	BOOL ConfirmMessage();
	BOOL GetWindowMode();
	VOID Release();

private:
	Window(const HINSTANCE hInst, TCHAR* pAppName);
	~Window();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	static Window* m_pWindow;
	static GameManager* m_pGameManager;
	static D3DPRESENT_PARAMETERS* m_pDirectXPresentParam;
	TCHAR* m_pAppName;
	HINSTANCE m_hInst;
	HWND m_hWnd;
	MSG m_msg;
	D3DXVECTOR2 m_displaySize;
	BOOL m_canWindow;
};
