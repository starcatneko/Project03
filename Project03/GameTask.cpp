#include "DxLib.h"
#include "MouseCtr.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "ImageMng.h"

// プレイヤー人数
#define PL_MAX 2


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
	//currentPlayer = lpGameTask.playerlist.begin();


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

VECTOR2 GameTask::GetBoardSize()
{
	return this->Board->GetBoardSize();
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
	int pl_cnt = 0;
	while (pl_cnt < PL_MAX)
	{
		// 関数にpl_cntを加算させる処理を組み込んだら短縮可能
		AddPlayer();
		pl_cnt++;
	}
	Board->SetPiece({ 3,3 }, PIECE_W);
	Board->SetPiece({ 4,4 }, PIECE_W);
	Board->SetPiece({ 4,3 }, PIECE_B);
	Board->SetPiece({ 3,4 }, PIECE_B);

	currentPlayer = playerlist.begin();



}


void GameTask::AddPlayer()
{
	//std::make_shared<Player>();
	playerlist.push_back(std::make_shared<Player>());

}
void GameTask::CurrentPlayerChange()
{
	auto itrrrr = lpGameTask.currentPlayer;

	if ((*lpGameTask.currentPlayer) == playerlist.back())
	{
		(*lpGameTask.currentPlayer) = (*lpGameTask.playerlist.begin());
		itrrrr = lpGameTask.currentPlayer;
		return;
	}
	(*lpGameTask.currentPlayer++);


	// 現在の順番を表示する関数を呼んで
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