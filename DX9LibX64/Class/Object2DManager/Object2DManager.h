#pragma once
#include <windows.h>
#include <vector>
#include <algorithm>
#include <functional>
#include "../GameManager/GameManager.h"
#include "../CustomVertices/CustomVertices.h"
#include "../Draw/Draw.h"
#include "../FileManager/FileManager.h"
#include "../BaseWorking/BaseWorkingManager/BaseWorkingManager.h"
#include "Object2D\Object2D.h"

class Object2DManager:public BaseWorkingManager
{
public:
	Object2DManager();
	~Object2DManager() {};

	virtual VOID Control();
	virtual VOID Render();
private:
	static bool cmpLarge(Object2D* p1, Object2D* p2);

	GameManager* m_pGameManager;
	CustomVertices* m_pCustomVertices;
	Draw* m_pDraw;
	FileManager* m_pFileManager;
	InputData m_inputData;
};
