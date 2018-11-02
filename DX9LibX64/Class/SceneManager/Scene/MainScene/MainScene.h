#pragma once
#include <windows.h>
#include "../Scene.h"
#include "MainObject\DamageStar.h"

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