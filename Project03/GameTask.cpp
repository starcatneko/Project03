#include "DxLib.h"

#include "GameTask.h"

GameTask *s_Instance = nullptr;
std::once_flag initFlag;

GameTask::GameTask()
{
	CurrentScene = &GameTask::Run;
}


GameTask::~GameTask()
{
}


GameTask *GameTask::s_Instance = nullptr;
void GameTask::Create()
{
	s_Instance = new GameTask();
}

void GameTask::Destroy()
{
	if (s_Instance)
		delete s_Instance;
	s_Instance = nullptr;
}

void GameTask::Run()
{

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == false)
	{
	/*
	‰æ–ÊƒNƒŠƒbƒN
	CurrentSceneØ‚è‘Ö‚¦
	*/
	//this->*(CurrentScene)() = GameMain::GetInstance()->GetInstance;
	//this->*(CurrentScene)();

	}
}