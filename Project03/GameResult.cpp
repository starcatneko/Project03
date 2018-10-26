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
		// リストを消去
		lpGameTask.playerlist.erase(lpGameTask.playerlist.begin(), lpGameTask.playerlist.end());
		
		Board->PieceResultSet();
		return std::make_unique<GameTitle>();
	}
	return pt;
}

void GameResult::Draw()
{
	Board->Draw();
	
	for (auto itr : lpGameTask.playerlist)
	{
		DrawFormatString(itr->GetNo() * 64, 440, 0xffff00, "%d", itr->GetScore());

	}
	//DrawFormatString(220,0,0xffffff,"%d:%d",
}
