#pragma once
#include <tchar.h>
#include <windows.h>
#include <d3dx9.h>
#include <map>

class FileManager
{
public:
	static FileManager* GetInstace(LPDIRECT3DDEVICE9 pDirectX3DDevice);
	VOID Release();
	static VOID SetLPDIRECT3DDEVICE9(LPDIRECT3DDEVICE9 pDirectX3DDevice);
	VOID CreateTex(TCHAR* pTexName,TCHAR* pTexturePath);
	VOID DeleteTex();
	LPDIRECT3DTEXTURE9 GetTex(TCHAR* pTexName);

protected:
	FileManager() {};
	~FileManager();

	static FileManager* m_pFileManager;
	std::map<TCHAR*, LPDIRECT3DTEXTURE9> m_pTextures;
	static LPDIRECT3DDEVICE9 m_pDirectX3DDevice;
};
