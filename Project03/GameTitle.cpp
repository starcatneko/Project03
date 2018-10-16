#include "GameTitle.h"
#include "GameTask.h"
#include "GamePiece.h"
#include "GameBoard.h"


#include "GameMain.h"
#include "Player.h"

#include "DxLib.h"


GameTitle::GameTitle()
{
	Board = lpGameTask.SetBoard();

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
	Board.lock() = std::make_unique<GameBoard>();
	int pl_cnt = 0;
	while (pl_cnt < PL_MAX)
	{
		// ŠÖ”‚Épl_cnt‚ð‰ÁŽZ‚³‚¹‚éˆ—‚ð‘g‚Ýž‚ñ‚¾‚ç’Zk‰Â”\
		AddPlayer();
		pl_cnt++;
	}

	Board.lock()->SetPiece({ 3,3 }, PIECE_W);
	Board.lock()->SetPiece({ 4,4 }, PIECE_W);
	Board.lock()->SetPiece({ 4,3 }, PIECE_B);
	Board.lock()->SetPiece({ 3,4 }, PIECE_B);
	/*
	Board->SetPiece({ 1,0 }, PIECE_B);
	Board->SetPiece({ 2,0 }, PIECE_B);
	Board->SetPiece({ 3,0 }, PIECE_B);
	Board->SetPiece({ 4,0 }, PIECE_W);
	Board->SetPiece({ 4,1 }, PIECE_W);
	*/
	lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
	(*lpGameTask.currentPlayer)->SetTunrFlg(true);

	lpGameTask.state.reset;
	lpGameTask.state = std::make_unique<GameMain>();
}



void GameTitle::AddPlayer()
{
	//std::make_shared<Player>();
	lpGameTask.playerlist.push_back(std::make_shared<Player>());

}

void GameTitle::Draw()
{

}
