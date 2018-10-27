#pragma once
#include <windows.h>
#include "../Scene.h"

class MainScene :public Scene
{
public:
	MainScene();
	~MainScene();

	VOID Update();
	VOID Render();
};