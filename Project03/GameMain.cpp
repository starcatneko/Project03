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
		// ŠÖ”‚Épl_cnt‚ğ‰ÁZ‚³‚¹‚éˆ—‚ğ‘g‚İ‚ñ‚¾‚ç’Zk‰Â”\
		AddPlayer();
		pl_cnt++;
	}
	lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
	(*lpGameTask.currentPlayer)->SetTunrFlg(true);
	
	lpMouse.SetOprtType(static_cast<int>((*lpGameTask.currentPlayer)->GetType()));
	MainBoard->SetlistUpdata();
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
				MainBoard->SetlistUpdata();
				lpMouse.SetOprtType(static_cast<int>((*lpGameTask.currentPlayer)->GetType()));
				return;
			}
			(*lpGameTask.currentPlayer++);
			(*lpGameTask.currentPlayer)->SetTunrFlg(true);
			MainBoard->SetlistUpdata();
			lpMouse.SetOprtType(static_cast<int>((*lpGameTask.currentPlayer)->GetType()));
		}
	};


	DrawString(0, 0, "Main", 0xffffff, 0);
	MainBoard->Update();
	(*lpGameTask.currentPlayer)->TurnAct();

	for (auto itr : GameTask::GetInstance().playerlist)
	{
		(*itr).Update();
	}

	VECTOR2 tmp = VECTOR2{ 0,380 };
	VECTOR2 tmp2 = VECTOR2{ 64,24 };
	if (lpMouse.GetOprtType() != OPRT_TYPE::CPU)
	{
		DrawBox(tmp.x, tmp.y,
			tmp.x + tmp2.x, tmp.y + tmp2.y,
			0xDD00ee, true);
		if (lpMouse.GetButton() != 0 
			&&lpMouse.GetPos().x > tmp.x
			&&lpMouse.GetPos().y > tmp.y
			&&lpMouse.GetPos().x <tmp.x + tmp2.x
			&&lpMouse.GetPos().y <tmp.y + tmp2.y)
		{
			lpMouse.SetOprtType(OPRT_TYPE::MAN);
		}

	}
	if (MainBoard->gameEndFlg)
	{
		// GameRessult‚ÅMainBoard‚Ìî•ñ‚ğˆø‚«‘±‚«g‚¤‚Ì‚Åˆø”‚Å“n‚·
		return std::make_unique<GameResult>(MainBoard);

	}
	setNextPlayer();
	return pt;
}


void GameMain::CurrentPlayerChange()
{
	
	// Œ»İ‚Ì‡”Ô‚ğ•\¦‚·‚éŠÖ”‚ğŒÄ‚ñ‚Å
}
void GameMain::AddPlayer()
{
	//std::make_shared<Player>();
	lpGameTask.playerlist.push_back(std::make_shared<Player>());

}
