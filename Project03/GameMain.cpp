#include "GameMain.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "GameResult.h"
#include "MouseCtr.h"
#include "Dxlib.h"

//		#define X_DIS (int)((SCREEN_SIZE_X / 2) - (MainBoard->GetBoardSize().x / 2)*CHIPSIZE)
//		#define Y_DIS (int)((SCREEN_SIZE_Y / 2) - (MainBoard->GetBoardSize().y / 2)*CHIPSIZE)

#define TESTMODE 0

GameMain::GameMain()
{
	auto CreateNewBoard = [&](){
		MainBoard = std::make_unique<GameBoard>();

		if (TESTMODE == 0)
		{
			MainBoard->SetPiece({ 3,3 }, PIECE_ST::W);
			MainBoard->SetPiece({ 4,4 }, PIECE_ST::W);
			MainBoard->SetPiece({ 4,3 }, PIECE_ST::B);
			MainBoard->SetPiece({ 3,4 }, PIECE_ST::B);
		}
		else
		{

			MainBoard->SetPiece({ 1,0 }, PIECE_ST::B);
			MainBoard->SetPiece({ 2,0 }, PIECE_ST::B);
			MainBoard->SetPiece({ 3,0 }, PIECE_ST::B);
			MainBoard->SetPiece({ 4,0 }, PIECE_ST::W);
			MainBoard->SetPiece({ 4,1 }, PIECE_ST::W);

		}
	};

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
	MainBoard->CurrentSetUpData();
}


GameMain::~GameMain()
{
}


void GameMain::Draw()
{
	MainBoard->Draw();
}

state_ptr GameMain::Update(state_ptr pt)
{


	auto setNextPlayer = [&](){
		//(*lpGameTask.currentPlayer)->SetTunrFlg(false);
		if ((*lpGameTask.currentPlayer)->GetTunrFlg()== false && (*lpGameTask.currentPlayer)->GetTurnTimer() <= 0)
		{
			if ((*lpGameTask.currentPlayer) == lpGameTask.playerlist.back())
			{
				lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
				(*lpGameTask.currentPlayer)->SetTunrFlg(true);
				MainBoard->CurrentSetUpData();
				return;
			}
			(*lpGameTask.currentPlayer++);
			(*lpGameTask.currentPlayer)->SetTunrFlg(true);
			MainBoard->CurrentSetUpData();
		}
	};


	DrawString(0, 0, "Main", 0xffffff, 0);
	MainBoard->Update();
	(*lpGameTask.currentPlayer)->TurnAct();
	for (auto itr : GameTask::GetInstance().playerlist)
	{
		(*itr).Update();
	}
	// ifTurnActがtrueの場合、プレイヤーチェンジ処理を行う

	if (MainBoard->gameEndFlg)
	{
		// GameRessultでMainBoardの情報を引き続き使うので引数で渡す
		return std::make_unique<GameResult>(MainBoard);

	}
	setNextPlayer();
	return pt;
}


void GameMain::CurrentPlayerChange()
{
	
	// 現在の順番を表示する関数を呼んで
}
void GameMain::AddPlayer()
{
	//std::make_shared<Player>();
	lpGameTask.playerlist.push_back(std::make_shared<Player>());

}
