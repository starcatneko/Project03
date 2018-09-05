#pragma once
#include "GameMain.h"
class Run
{
public:
	Run();
	~Run();
private:
	void SceneCCtr();
	int GameMain::*CurrentScene;
};

