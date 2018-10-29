#include <Windows.h>
#include <d3dx9.h>
#include <time.h>
#include <stdlib.h>
#include "../../../FBX/FbxRelated.h"
#include "../../../CustomVertices/CustomVertices.h"
#include "../../../Draw/Draw.h"
#include "../../SceneManager.h"
#include "../../../GameManager/GameManager.h"
#include "TitleScene.h"
#include "TitleObject\TitleObject.h"

class GameManager;

TitleScene::TitleScene()
{
	m_sceneObjectManager.Resist(new TitleBack((Scene*)this));
	m_sceneObjectManager.Resist(new TitleLogo((Scene*)this));
	m_sceneObjectManager.Resist(new TitleInputPrompt((Scene*)this));
	m_sceneObjectManager.Resist(new TitleMenu((Scene*)this));
	m_sceneObjectManager.Resist(new TitleStarEffect((Scene*)this));
}

TitleScene::~TitleScene()
{
}

VOID TitleScene::Update()
{
	m_sceneObjectManager.Control();
}

VOID TitleScene::Render()
{
	m_sceneObjectManager.Render();
}

BOOL TitleScene::GetCanSelectMenu()
{
	return m_canSelectMenu;
}

VOID TitleScene::SetCanSelectMenu(BOOL canSelectMenu)
{
	m_canSelectMenu = canSelectMenu;
}
