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


std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask()
{
	CurrentScene = &GameTask::Init;
	Mouse = std::make_unique<MouseCtr>();
	state.reset();
	state = std::make_unique<GameTitle>();
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

void GameTask::GameEnd()
{

}


void GameTask::CreateNewBoard()
{
}




void GameTask::Run()
{
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

void GameTask::CurrentPlayerChange()
{
	(*lpGameTask.currentPlayer)->SetTunrFlg(false);
	if ((*lpGameTask.currentPlayer) == lpGameTask.playerlist.back())
	{
		lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
		(*lpGameTask.currentPlayer)->SetTunrFlg(true);
		return;
	}

	(*lpGameTask.currentPlayer++);
	(*lpGameTask.currentPlayer)->SetTunrFlg(true);

	// 現在の順番を表示する関数を呼んで
}
