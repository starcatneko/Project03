#include "DxLib.h"
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

	CurrentScene = &GameTask::Title;

}

void GameTask::Title()
{
	ImageMng::GetInstance()->DrawImg({ 120,240 }, "title", 0);
	DrawString(0, 0, "Title", 0xffffff, 0);

	if ((GetMouse() & 0b0001) > 0 && (mouseOld & 0b0001) == 0)
	{
		CreateNewBoard();
		CurrentScene = &GameTask::GameMain;
	}

}

void GameTask::GameMain()
{
	DrawString(0, 0, "Main", 0xffffff, 0);
	Board->Update();
	if ((GetMouse() & 0b0001) != 0 && (mouseOld & 0b0001) == 0)
	{
		CurrentScene = &GameTask::Title;
	}


}

void GameTask::CreateNewBoard()
{
	if (Board != nullptr)
	{
		delete Board;
		Board = nullptr;
	}
	Board = new GameBoard(8);
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

int GameTask::GetMouse()
{
	mouseOld = mouseFlg;

	int flg = 0;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 )
	{
		flg += 0b0001;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		flg += 0b0010;
	}
	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
	{
		flg += 0b0100;
	}
	mouseFlg = flg;

	return flg;
}
