#include "DxLib.h"
#include "MouseCtr.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "ImageMng.h"

// ƒQ[ƒ€ƒ‚[ƒhStateOem‚ğ˜A‚ê‚Ä‚«‚½‚æI

#include "GameTitle.h"
#include "GameMain.h"
#include "GameResult.h"


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

void GameTask::GameEnd()
{
	state = std::make_unique<GameResult>();

}

std::shared_ptr<GameBoard> GameTask::SetBoard()
{
	return this->Board;
}


void GameTask::CreateNewBoard()
{
	Board = std::make_unique<GameBoard>();
	int pl_cnt = 0;
	while (pl_cnt < PL_MAX)
	{
		// ŠÖ”‚Épl_cnt‚ğ‰ÁZ‚³‚¹‚éˆ—‚ğ‘g‚İ‚ñ‚¾‚ç’Zk‰Â”\
		AddPlayer();
		pl_cnt++;
	}
	
	Board->SetPiece({ 3,3 }, PIECE_W);
	Board->SetPiece({ 4,4 }, PIECE_W);
	Board->SetPiece({ 4,3 }, PIECE_B);
	Board->SetPiece({ 3,4 }, PIECE_B);	
	/*
	Board->SetPiece({ 1,0 }, PIECE_B);
	Board->SetPiece({ 2,0 }, PIECE_B);
	Board->SetPiece({ 3,0 }, PIECE_B);
	Board->SetPiece({ 4,0 }, PIECE_W);
	Board->SetPiece({ 4,1 }, PIECE_W);
	*/
	currentPlayer = playerlist.begin();
	(*currentPlayer)->SetTunrFlg(true);
}




void GameTask::Run()
{
	ScreenFlip();
	ClsDrawScreen();
	state->Update();
	(this->*CurrentScene)();
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