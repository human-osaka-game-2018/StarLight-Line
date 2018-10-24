#include "FileManager.h"

LPDIRECT3DDEVICE9 FileManager::m_pDirectX3DDevice = NULL;

FileManager::~FileManager()
{
	DeleteTex();
}

VOID FileManager::SetLPDIRECT3DDEVICE9(LPDIRECT3DDEVICE9 pDirectX3DDevice)
{
	m_pDirectX3DDevice = pDirectX3DDevice;
}

VOID FileManager::CreateTex(TCHAR* pTexName, TCHAR* pTexturePath)
{
	D3DXCreateTextureFromFile(m_pDirectX3DDevice, pTexturePath, &m_pTextures[pTexName]);
}

void FileManager::DeleteTex()
{
	m_pTextures.clear();
}

LPDIRECT3DTEXTURE9 FileManager::GetTex(TCHAR* pTexName)
{
	return m_pTextures[pTexName];
}
