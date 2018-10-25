#pragma once
#pragma once
#include <windows.h>
#include <vector>
#include "../../BaseWorking/BaseWorking.h"
#include "../../CustomVertices/CustomVertices.h"
#include "../../GameManager/GameManager.h"
#include "../../Draw/Draw.h"
#include "../../FileManager/FileManager.h"

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

class Object2D :public BaseWorking
{
public:
	Object2D() {};
	~Object2D();

	Type GetType();
	FLOAT GetZ();
	VOID syncLibInstance(GameManager* pGameManager, CustomVertices* pCustomVertices,
		Draw* pDraw, InputData inputData, FileManager* pFileManager);

protected:
	virtual VOID Init() = 0;
	Type m_type;
	std::vector<Object2DData> m_object2DDatas;
	GameManager* m_pGameManager;
	CustomVertices* m_pCustomVertices;
	Draw* m_pDraw;
	FileManager* m_pFileManager;
	InputData m_inputData;
};
