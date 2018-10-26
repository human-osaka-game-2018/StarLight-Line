#pragma once
#include "../../../../BaseWorking/BaseWorking.h"
#include "../../../../Object2DManager/Object2D/Object2D.h"

class TitleBack :public Object2D
{
public:
	VOID Init();
	VOID Update() {};
	VOID Render();
};

class TitleLogo :public Object2D
{
public:
	VOID Init();
	VOID Update() {};
	VOID Render();
};
 
class TitleInputPrompt :public Object2D
{
public:
	VOID Init();
	VOID Update();
	VOID Render();
};
