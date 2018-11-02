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
	Scene* pThisScene = (Scene*)this;

	m_sceneObjectManager.Resist(new TitleBack(pThisScene));
	m_sceneObjectManager.Resist(new TitleLogo(pThisScene));
	m_sceneObjectManager.Resist(new TitleInputPrompt(pThisScene));
	m_sceneObjectManager.Resist(new TitleMenu(pThisScene));
	m_sceneObjectManager.Resist(new TitleStarEffect(pThisScene));
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

VOID TitleScene::ChangeNextScene(SceneID sceneID)
{
	*m_pNextScene = sceneID;
}
