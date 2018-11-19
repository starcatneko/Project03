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
	CurrentScene = &GameTask::Init;

	state.reset();
	state = std::make_unique<GameTitle>();
	Mouse.resize(static_cast<int>(PIECE_ST::MAX));
	oprt_tbl.resize(static_cast<int>(PIECE_ST::MAX));
	oprt_tbl_s.resize(static_cast<int>(PIECE_ST::MAX));
	for (auto unit : PIECE_ST())
	{
		Mouse[unit] = std::make_shared<MouseCtr>();
		Mouse[unit]->SetOprtType(OPRT_TYPE::CPU);
		oprt_tbl[unit] = OPRT_TYPE::CPU;
		oprt_tbl_s[unit] = ;
	}
	Mouse[0]->SetOprtType(OPRT_TYPE::MAN);
	oprt_tbl[0] = OPRT_TYPE::MAN;
	//oprt_tbl[1] = OPRT_TYPE::MAN;

	wait = 0;
}


GameTask::~GameTask()
{

}

void GameTask::Init()
{
	//CurrentScene = &GameTask::Title;
	//currentPlayer = lpGameTask.playerlist.begin();
}
void GameTask::Run()
{
	for (auto unit : PIECE_ST())
	{
		// 引数で操作種別を渡す
		// 
		Mouse[unit]->Update(oprt_tbl[unit]);
	}
	ScreenFlip();
	ClsDrawScreen();
	state = state->Update(std::move(state));
	if (wait > 0)
	{
		wait--;
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

