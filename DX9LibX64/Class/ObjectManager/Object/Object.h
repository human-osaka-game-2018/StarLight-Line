#pragma once
#include <windows.h>
#include <vector>
#include "../../BaseWorking/BaseWorking.h"
#include "../../GameManager/GameManager.h"
#include "../../Draw/Draw.h"
#include "../../FileManager/FileManager.h"
#include "../../CustomVertices/CustomVertices.h"
#include "../../SceneManager/Scene/Scene.h"

enum class Type
{
	BACK,
	OPACTY,
	TRANSPARENCY,
	UI,
	TYPE_MAX
};

struct ObjectData
{
	D3DXVECTOR3 m_center = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_halfScale = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_degree = { 0.0f,0.0f,0.0f };
	DWORD m_color = 0xFFFFFFFF;
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
	Scene* m_pScene;
	Type m_type;
	GameManager* m_pGameManager;
	KeyBoardState* m_pKeyState;
	MouseState* m_pMouseState;
	D3DXVECTOR2 m_windowSize;
	FLOAT m_z;
};
