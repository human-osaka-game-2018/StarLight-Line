#pragma once
#include <windows.h>
#include "../Scene.h"
#include "MainObject\DamageStar.h"

#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

class MainScene :public Scene
{
public:
	MainScene();
	~MainScene();

	VOID Update();
	VOID Render();

private:
	DamageStar m_DamageStar;
};