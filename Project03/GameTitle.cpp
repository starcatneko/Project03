#include "GameTitle.h"
#include "GameTask.h"
#include "GamePiece.h"


#include "GameMain.h"

#include "DxLib.h"


GameTitle::GameTitle()
{
}


GameTitle::~GameTitle()
{
}
/*
void GameTitle::Update()
{

}*/
void GameTitle::Update(const MouseCtr & MouseCtr)
{
	ImageMng::GetInstance().DrawImg({ 120,240 }, "title", 0);
	DrawString(0, 0, "Title", 0xffffff, 0);

	if ((MouseCtr->GetButton() & 0b0001) > 0)
	{
		CreateNewBoard();
	}
}

void GameTitle::CreateNewBoard()
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



void GameTitle::AddPlayer()
{
	//std::make_shared<Player>();
	lpGameTask.playerlist.push_back(std::make_shared<Player>());

}

void GameTitle::Draw()
{

}
