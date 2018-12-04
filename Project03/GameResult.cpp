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
	//Board->PieceResultSet();
	Board->ResultInit();
	for (auto itr : PIECE_ST())
	{

		//pieceCount[int(itr)] = Board->PieceCount(itr);
	}

	lpMouse.SetOprtType(OPRT_TYPE::MAN);

}


GameResult::~GameResult()
{
}


state_ptr GameResult::Update(state_ptr pt)
{
	Board->Update();

	if ((lpMouse.GetButton() & 0b0001) > 0)
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
	Board->Draw();
	Board->ResultDraw();
	for (auto itr : lpGameTask.playerlist)
	{
		//DrawFormatString(itr->GetNo() * 64, 440, 0xffff00, "%d", pieceCount[itr->GetNo()]);

	}
	//DrawFormatString(220,0,0xffffff,"%d:%d",
}
