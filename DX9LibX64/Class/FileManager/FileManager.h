#pragma once
#include <tchar.h>
#include <windows.h>
#include <d3dx9.h>
#include <map>

class FileManager
{
public:
	FileManager() {};
	~FileManager();

	TCHAR* CreateTex(TCHAR* pTexName,TCHAR* pTexturePath);
	void DeleteTex();
	LPDIRECT3DTEXTURE9 GetTex(TCHAR* pTexName);

protected:
	std::map<TCHAR, LPDIRECT3DTEXTURE9> pTextures;
};