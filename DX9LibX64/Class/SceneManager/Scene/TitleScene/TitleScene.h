#pragma once
#include <windows.h>
#include "../Scene.h"

#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

class TitleScene :public Scene
{
public:
	VOID Update();
	VOID Render();
};
