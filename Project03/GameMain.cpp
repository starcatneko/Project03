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
	DrawString(0, 0, "Main", 0xffffff, 0);
	MainBoard->Update();
	(*lpGameTask.currentPlayer)->TurnAct();
	// player全体のUpdateを回す
	for (auto itr : GameTask::GetInstance().playerlist)
	{
		(*itr).Update();
	}

	std::string p1OprtType,p2OprtType;


	if (Button({ 0+20,380 }, { 64,32 },"%s", 0xdddddd))
	{
		lpMouse.ChangeOprtTbl(PIECE_ST::B);
	}
	if (Button({ PLAYER2_TRAY_OFFSET+20,380 }, { 64,24 }, "CHANGE", 0x444444))
	{
		lpMouse.ChangeOprtTbl(PIECE_ST::W);
	}

	if (MainBoard->gameEndFlg)
	{
		// GameRessultでMainBoardの情報を引き続き使うので引数で渡す
		return std::make_unique<GameResult>(MainBoard);
	}
	setNextPlayer();
	return pt;
}

void GameMain::setNextPlayer() {
	// プレイヤーがターン終了 & ターン変更ウェイト終了
	if ((*lpGameTask.currentPlayer)->GetTunrFlg() == false && (*lpGameTask.currentPlayer)->GetTurnTimer() <= 0)
	{
		if ((*lpGameTask.currentPlayer) == lpGameTask.playerlist.back())
		{
			lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
		}
		else
		{
			(*lpGameTask.currentPlayer++);
		}
		(*lpGameTask.currentPlayer)->SetTunrFlg(true);
		MainBoard->SetlistUpdata();
		lpMouse.SetOprtType(static_cast<int>((*lpGameTask.currentPlayer)->GetType()));
	}
};

void GameMain::AddPlayer()
{
	lpGameTask.playerlist.push_back(std::make_shared<Player>());
}


bool GameMain::Button(VECTOR2 pos,VECTOR2 size,std::string text,int color)
{
	DrawBox(pos.x, pos.y,
		pos.x + size.x, pos.y + size.y,
		color, true);

	if ((color & 0xff0000) > 0x880000 &&
		(color & 0x00ff00) > 0x008800 &&
		(color & 0x0000ff) > 0x000088)
	{
		DrawString(pos.x, pos.y, text.c_str(), 0x000000);
	}
	else
	{
		DrawString(pos.x, pos.y, text.c_str(), 0xffffff);
	}
	if (lpMouse.GetButton() != 0
		&& lpMouse.GetPos().x > pos.x
		&&lpMouse.GetPos().y > pos.y
		&&lpMouse.GetPos().x <pos.x + size.x
		&&lpMouse.GetPos().y <pos.y + size.y)
	{
		return true;
	}
	return false;
}