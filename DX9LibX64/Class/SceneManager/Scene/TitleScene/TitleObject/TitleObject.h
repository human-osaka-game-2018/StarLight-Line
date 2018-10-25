#pragma once
#include "../../../../BaseWorking/BaseWorking.h"
#include "../../../../Object2DManager/Object2D/Object2D.h"

class TitleBack :public Object2D
{
public:
	VOID Update() {};
	VOID Render();

private:
	VOID Init();
};