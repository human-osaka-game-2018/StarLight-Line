#include <windows.h>
#include "TitleObject.h"
#include "../../../../Object2DManager/Object2D/Object2D.h"

VOID TitleBack::Init()
{
	static bool canInit = true;

	if (!canInit)return;

	canInit = false;

	m_pFileManager->CreateTex(_T("Back"), _T("2DTextures/Title/TitleBack.png"));	//‰æ‘œ“Ç‚İ‚İ
}

VOID TitleBack::Render()
{

}
