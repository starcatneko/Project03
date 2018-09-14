#include "DxLib.h"
#include "MouseCtr.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "ImageMng.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask()
{
	CurrentScene = &GameTask::Init;
}


GameTask::~GameTask()
{

}

void GameTask::Init()
{
	ImageMng::GetInstance().LoadImg("image/title.jpg", "title");
	Mouse = std::make_unique<MouseCtr>();

	CurrentScene = &GameTask::Title;

}

void GameTask::Title()
{
	ImageMng::GetInstance().DrawImg({ 120,240 }, "title", 0);
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
		Board->SetPiece(Mouse->GetPos());
	}
}

void GameTask::CreateNewBoard()
{
	Board = std::make_unique<GameBoard>();
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
