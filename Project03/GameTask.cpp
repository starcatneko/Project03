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
	state.reset();
	state = std::make_unique<GameResult>();

}


void GameTask::CreateNewBoard()
{
	/*
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
	
	Board->SetPiece({ 1,0 }, PIECE_B);
	Board->SetPiece({ 2,0 }, PIECE_B);
	Board->SetPiece({ 3,0 }, PIECE_B);
	Board->SetPiece({ 4,0 }, PIECE_W);
	Board->SetPiece({ 4,1 }, PIECE_W);
	
	currentPlayer = playerlist.begin();
	(*currentPlayer)->SetTunrFlg(true);
	*/
}




void GameTask::Run()
{
	ScreenFlip();
	ClsDrawScreen();
	state->Update();
	//(this->*CurrentScene)();
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

	// Œ»İ‚Ì‡”Ô‚ğ•\¦‚·‚éŠÖ”‚ğŒÄ‚ñ‚Å
}
