#include <windows.h>
#include "Light.h"

LPDIRECT3DDEVICE9 Light::m_pDirectX3DDevice;

VOID Light::SetLPDIRECT3DDEVICE9(LPDIRECT3DDEVICE9 pDirectX3DDevice)
{
	m_pDirectX3DDevice = pDirectX3DDevice;
}

VOID Light::SetLight(D3DLIGHT9* pLight,INT lightIndex)
{
	D3DLIGHT9 light;

	m_pDirectX3DDevice->SetLight(lightIndex, &light);
}
