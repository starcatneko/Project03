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

}
void GameTask::Run()
{
	lpMouse.Update();

	ScreenFlip();
	ClsDrawScreen();
	state = state->Update(std::move(state));
	state->Draw();

}

VECTOR2 GameTask::GetBoardSize()
{
	return Board->GetBoardSize();
}