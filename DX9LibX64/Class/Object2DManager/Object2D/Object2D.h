#pragma once
#include <windows.h>
#include <vector>
#include "../../BaseWorking/BaseWorking.h"
#include "../../GameManager/GameManager.h"
#include "../../Draw/Draw.h"
#include "../../FileManager/FileManager.h"
#include "../../CustomVertices/CustomVertices.h"

enum Type
{
	BACK,
	OPACTY,
	TRANSPARENCY,
	UI,
	TYPE_MAX
};

struct Object2DData
{
	D3DXVECTOR3 m_center;
	D3DXVECTOR2 m_scale;
	D3DXVECTOR3 m_degree;
	DWORD m_color;
};

class CustomVertices;
class Draw;

class Object2D :public BaseWorking
{
public:
	Object2D() {};
	~Object2D();

	virtual VOID Init() = 0;
	Type GetType();
	FLOAT GetZ();
	VOID syncLibInstance(GameManager* pGameManager, CustomVertices* pCustomVertices,
		Draw* pDraw, InputData inputData, FileManager* pFileManager);

protected:
	Type m_type;
	std::vector<Object2DData*> m_pObject2DDatas;
	GameManager* m_pGameManager;
	CustomVertices* m_pCustomVertices;
	Draw* m_pDraw;
	FileManager* m_pFileManager;
	InputData m_inputData;
};
