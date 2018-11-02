#pragma once
#include "../../../../ObjectManager/Object/Object.h"
#include "../MainScene.h"

class MainObject :public Object
{
public:
	MainObject(Scene* pScene);
	~MainObject() {};

protected:
	MainScene * m_pMainScene;
};