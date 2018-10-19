#include "GameMain.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "MouseCtr.h"
#include "Dxlib.h"


GameMain::GameMain()
{
	CreateNewBoard();

}


GameMain::~GameMain()
{
}


void GameMain::Draw()
{
}

void GameMain::CreateNewBoard()
{
	MainBoard = std::make_unique<GameBoard>();

	MainBoard->SetPiece({ 3,3 }, PIECE_W);
	MainBoard->SetPiece({ 4,4 }, PIECE_W);
	MainBoard->SetPiece({ 4,3 }, PIECE_B);
	MainBoard->SetPiece({ 3,4 }, PIECE_B);
	/*
	Board->SetPiece({ 1,0 }, PIECE_B);
	Board->SetPiece({ 2,0 }, PIECE_B);
	Board->SetPiece({ 3,0 }, PIECE_B);
	Board->SetPiece({ 4,0 }, PIECE_W);
	Board->SetPiece({ 4,1 }, PIECE_W);
	*/
	lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
	(*lpGameTask.currentPlayer)->SetTunrFlg(true);
}


state_ptr GameMain::Update(state_ptr pt)
{

	DrawString(0, 0, "Main", 0xffffff, 0);
	MainBoard->Update();
	(*lpGameTask.currentPlayer)->TurnAct();
	// ifTurnActがtrueの場合、プレイヤーチェンジ処理を行う
	if ((lpGameTask.Mouse->GetButton() & 0b0001) != 0)
	{
		MainBoard->SetPiece(lpGameTask.Mouse->GetPos());
	}
	if ((lpGameTask.Mouse->GetButton() & 0b0010) != 0)
	{
		MainBoard->Debug_SetPiece(lpGameTask.Mouse->GetPos());
	}

	if (MainBoard->gameEndFlg)
	{

	}

	return pt;
}


void GameMain::CurrentPlayerChange()
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
