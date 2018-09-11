#include "DxLib.h"
#include "MouseCtr.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "ImageMng.h"

GameTask *GameTask::s_Instance = nullptr;
std::once_flag GameTask::initFlag;

GameTask::GameTask()
{
	CurrentScene = &GameTask::Init;
}


GameTask::~GameTask()
{

}

void GameTask::Init()
{
	ImageMng::GetInstance()->LoadImg("image/title.jpg", "title");
	Mouse = std::make_unique<MouseCtr>();

	CurrentScene = &GameTask::Title;

}

void GameTask::Title()
{
	ImageMng::GetInstance()->DrawImg({ 120,240 }, "title", 0);
	DrawString(0, 0, "Title", 0xffffff, 0);

	if ((Mouse->GetButton() & 0b0001) > 0)
	{
		CreateNewBoard();
		CurrentScene = &GameTask::GameMain;
	}

}

void GameTask::GameMain()
{

	DrawString(0, 0, "Main", 0xffffff, 0);
	Board->Update();
	if ((Mouse->GetButton() & 0b0001) != 0)
	{
		Board->SetStone(Mouse->GetPos());
	}
}

void GameTask::CreateNewBoard()
{
	Board = std::make_unique<GameBoard>();
}


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
		ScreenFlip();
		ClsDrawScreen();

		(this->*CurrentScene)();

	}
}


void GameTask::UpDate(const MouseCtr & mouseCtr)
{

}
