#pragma once
#include <tchar.h>
#include <windows.h>
#include <d3dx9.h>
#include <map>

class Light
{
public:
	Light() {};
	~Light() {};

	static VOID SetLPDIRECT3DDEVICE9(LPDIRECT3DDEVICE9 pDirectX3DDevice);
	VOID SetLight(D3DLIGHT9* pLight, INT lightIndex);
private:
	static LPDIRECT3DDEVICE9 m_pDirectX3DDevice;
};