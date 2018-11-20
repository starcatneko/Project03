#include "DxLib.h"
#include "MouseCtr.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "ImageMng.h"

// ゲームモードState三銃士を連れてきたよ！
#include "GameState.h"
#include "GameTitle.h"
#include "GameMain.h"
#include "GameResult.h"
#include "OPRT_State.h"


std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask()
{
	Init();
}


GameTask::~GameTask()
{

}

void GameTask::Init()
{
	CurrentScene = &GameTask::Init;

	state.reset();
	state = std::make_unique<GameTitle>();
	Mouse = std::make_shared<MouseCtr>();

	wait = 0;
}
void GameTask::Run()
{
	Mouse->Update();

	ScreenFlip();
	ClsDrawScreen();
	state = state->Update(std::move(state));
	if (wait > 0)
	{
		//wait--;
	}
	state->Draw();
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

VECTOR2 GameTask::GetBoardSize()
{
	return Board->GetBoardSize();
}

