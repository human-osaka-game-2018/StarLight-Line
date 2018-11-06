#include <windows.h>
#include <tchar.h>
#include "Window.h"
#include "../GameManager.h"
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

Window* Window::m_pWindow = NULL;
GameManager* Window::m_pGameManager = NULL;
D3DPRESENT_PARAMETERS* Window::m_pDirectXPresentParam;

Window* Window::GetInstance(const HINSTANCE hInst, TCHAR* pAppName)
{
	if (!m_pWindow)m_pWindow = new Window(hInst, pAppName);

	return m_pWindow;
}

Window::Window(const HINSTANCE hInst, TCHAR* pAppName) :m_displaySize(1920.0f,1080.0f), 
m_canWindow(TRUE), m_hWnd(NULL)
{
	m_pAppName = pAppName;
	m_hInst = hInst;
	ZeroMemory(&m_msg, sizeof(m_msg));
}

Window::~Window()
{
	m_pWindow = NULL;
}

VOID Window::SetSizeDisplay(D3DXVECTOR2 displaySize)
{
	m_displaySize = displaySize;
}

VOID Window::SetWindowMode(BOOL canWindow)
{
	m_canWindow = canWindow;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	m_pDirectXPresentParam;

	switch (iMsg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	case WM_SIZE:
	{
		m_pGameManager = GameManager::CopyInstance();

		m_pDirectXPresentParam = m_pGameManager->GetD3DPRESENT_PARAMETERS();

		if (!m_pDirectXPresentParam->Windowed)break;

		if (m_pGameManager->GetDirectX3DDevice() || wParam == SIZE_MINIMIZED)break;

		m_pGameManager->SetBackBufferSize(LOWORD(lParam), HIWORD(lParam));

		if (!m_pGameManager->GetEnable3DDevice())break;

		if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)m_pGameManager->ChangeWindowSize();
	}

		break;

	case WM_SETCURSOR:
	{
		m_pGameManager = GameManager::CopyInstance();

		*m_pDirectXPresentParam = *m_pGameManager->GetD3DPRESENT_PARAMETERS();

		if (m_pDirectXPresentParam->Windowed != TRUE)
		{
			SetCursor(NULL);
			return 1;
		}
	}

		break;

	case WM_KEYDOWN:
		// キー入力の処理
		switch (wParam)
		{
		case VK_ESCAPE: // [ESCAPE]キーでウインドウを閉じる

			PostMessage(hWnd, WM_CLOSE, 0, 0);

			break;
		}
		
		break;

	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch (wParam)
		{
		case VK_RETURN:     // Alt + Enterを押すと切り替え
			m_pGameManager->ChangeDisplayMode();

			break;

		default:
			break;
		}

		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

VOID Window::MakeWindow()
{
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = m_hInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = m_pAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	const D3DXVECTOR2 FULLSCREEN_SIZE(1920.0f,1080.0f);

	if (m_canWindow)
	{
		m_hWnd = CreateWindow(m_pAppName, m_pAppName, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, (INT)m_displaySize.x, (INT)m_displaySize.y, NULL, NULL, m_hInst, NULL);
	}

	else
	{
		m_hWnd = CreateWindow(m_pAppName,m_pAppName, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, (INT)FULLSCREEN_SIZE.x, (INT)FULLSCREEN_SIZE.y, NULL, NULL, m_hInst, NULL);
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	ZeroMemory(&m_msg, sizeof(m_msg));

	return;
}

BOOL Window::ConfirmMessage()
{
	if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&m_msg);

		DispatchMessage(&m_msg);

		return FALSE;
	}

	return TRUE;
}

HWND* Window::GetHWNDPtr()
{
	return &m_hWnd;
}

MSG Window::GetMSG()
{
	return m_msg;
}

BOOL Window::GetWindowMode()
{
	return m_canWindow;
}

VOID Window::Release()
{
	delete m_pWindow;
}
