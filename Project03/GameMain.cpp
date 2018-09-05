#include "Dxlib.h"
#include "GameMain.h"

GameMain *GameMain::s_Instance = nullptr;

void GameMain::Create()
{
	if (!s_Instance)
		s_Instance = new GameMain();
}

void GameMain::Destroy()
{
	if (s_Instance)
		delete s_Instance;
	s_Instance = nullptr;
}


GameMain::GameMain()
{

}

GameMain::~GameMain()
{

}

void GameMain::Update()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//ŠÖ”ƒ|ƒCƒ“ƒ^Ø‚è‘Ö‚¦
	}

}