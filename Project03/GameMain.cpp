#include "GameMain.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "GameResult.h"
#include "MouseCtr.h"
#include "Dxlib.h"

#define X_DIS (int)((SCREEN_SIZE_X / 2) - (MainBoard->GetBoardSize().x / 2)*CHIPSIZE)
#define Y_DIS (int)((SCREEN_SIZE_Y / 2) - (MainBoard->GetBoardSize().y / 2)*CHIPSIZE)


GameMain::GameMain()
{
	CreateNewBoard();

	lpGameTask.Board = MainBoard;
	int pl_cnt = 0;
	while (pl_cnt < PL_MAX)
	{
		// 関数にpl_cntを加算させる処理を組み込んだら短縮可能
		AddPlayer();
		pl_cnt++;
	}
	lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
	(*lpGameTask.currentPlayer)->SetTunrFlg(true);


}


GameMain::~GameMain()
{
}


void GameMain::Draw()
{
	MainBoard->Draw();
}

void GameMain::CreateNewBoard()
{
	MainBoard = std::make_unique<GameBoard>();
	/*
	MainBoard->SetPiece({ 3,3 }, PIECE_W);
	MainBoard->SetPiece({ 4,4 }, PIECE_W);
	MainBoard->SetPiece({ 4,3 }, PIECE_B);
	MainBoard->SetPiece({ 3,4 }, PIECE_B);
	*/
	MainBoard->SetPiece({ 1,0 }, PIECE_B);
	MainBoard->SetPiece({ 2,0 }, PIECE_B);
	MainBoard->SetPiece({ 3,0 }, PIECE_B);
	MainBoard->SetPiece({ 4,0 }, PIECE_W);
	MainBoard->SetPiece({ 4,1 }, PIECE_W);
	
}


state_ptr GameMain::Update(state_ptr pt)
{

	DrawString(0, 0, "Main", 0xffffff, 0);
	MainBoard->Update();
	(*lpGameTask.currentPlayer)->TurnAct();
	for (auto itr : GameTask::GetInstance().playerlist)
	{
		(*itr).Update();
	}
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
		// GameRessultでMainBoardの情報を引き続き使うので引数で渡す
		return std::make_unique<GameResult>(MainBoard);

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
void GameMain::AddPlayer()
{
	//std::make_shared<Player>();
	lpGameTask.playerlist.push_back(std::make_shared<Player>());

}
