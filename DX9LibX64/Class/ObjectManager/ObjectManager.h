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
#include "Object\Object.h"

class Object;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	virtual VOID Resist(Object* pObject);
	virtual VOID Control();
	virtual VOID Render();
private:
	static bool cmpLarge(Object* p1, Object* p2);

	std::vector<Object*>m_VPObjects;
};
