#include "GameTask.h"
#include "GameBoard.h"
#include "GameTitle.h"
#include "Player.h"
#include "MouseCtr.h"
#include "DxLib.h"
#include "GameResult.h"

GameResult::GameResult()
{
}

GameResult::GameResult(Board_ptr pt)
{
	this->Board = pt;
	Board->PieceResultSet();

}


GameResult::~GameResult()
{
}


state_ptr GameResult::Update(state_ptr pt)
{
	lpGameTask.Board->Update();

	if ((lpGameTask.Mouse->GetButton() & 0b0001) != 0)
	{
		// ƒŠƒXƒg‚ðÁ‹Ž
		lpGameTask.playerlist.erase(lpGameTask.playerlist.begin(), lpGameTask.playerlist.end());
		
		Board->PieceResultSet();
		return std::make_unique<GameTitle>();
	}
	return pt;
}

void GameResult::Draw()
{
	Board->DrawBoard();
	Board->DrawPiece();
	//DrawFormatString(220,0,0xffffff,"%d:%d",
}
