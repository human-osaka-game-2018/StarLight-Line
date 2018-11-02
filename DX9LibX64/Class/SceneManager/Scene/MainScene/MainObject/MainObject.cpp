#include "MainObject.h"

MainObject::MainObject(Scene* pScene) :Object(pScene)
{
	m_pMainScene = dynamic_cast<MainScene*>(pScene);
}