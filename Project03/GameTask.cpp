#include "DxLib.h"
#include "MouseCtr.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "ImageMng.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask()
{
	CurrentScene = &GameTask::Init;
	wait = 0;
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
	Mouse->GetPos().x;

	if ((Mouse->GetButton() & 0b0001) != 0)
	{
		Board->SetPiece(Mouse->GetPos());
	}

	if ((Mouse->GetButton() & 0b0010) != 0)
	{
		Board->Debug_SetPiece(Mouse->GetPos());

	}
}

void GameTask::GameEnd()
{
	CurrentScene = &GameTask::Result;

}

void GameTask::Result()
{
	Board->Update();
	if ((Mouse->GetButton() & 0b0001) != 0)
	{
		CurrentScene = &GameTask::Title;
	}

}

void GameTask::CreateNewBoard()
{
	Board = std::make_unique<GameBoard>();
}


void GameTask::Run()
{

		ScreenFlip();
		ClsDrawScreen();
		(this->*CurrentScene)();

		if (wait > 0)
		{
			wait--;
		}
}

void GameTask::SetWait(int wait)
{
	this->wait = wait;
}
void GameTask::AddWait(int wait)
{
	this->wait += wait;
}

int GameTask::GetWait()
{
	return wait;
}