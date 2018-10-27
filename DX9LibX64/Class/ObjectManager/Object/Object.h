#pragma once
#include <windows.h>
#include <vector>
#include "../../BaseWorking/BaseWorking.h"
#include "../../GameManager/GameManager.h"
#include "../../Draw/Draw.h"
#include "../../FileManager/FileManager.h"
#include "../../CustomVertices/CustomVertices.h"
#include "../../SceneManager/Scene/Scene.h"

enum Type
{
	BACK,
	OPACTY,
	TRANSPARENCY,
	UI,
	TYPE_MAX
};

struct ObjectData
{
	D3DXVECTOR3 m_center;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_degree;
	DWORD m_color;
};

class CustomVertices;
class Draw;
class GameManager;
class Scene;

class Object :public BaseWorking
{
public:
	Object(Scene* pScene);
	~Object();

	virtual VOID Init() {};
	Type GetType();
	FLOAT GetZ();

protected:
	Type m_type;
	std::vector<ObjectData*> m_pObjectDatas;
	GameManager* m_pGameManager;
	InputData* m_pInputData;
	Scene* m_pScene;
};
