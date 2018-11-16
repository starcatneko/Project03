#include "GameMain.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "GameResult.h"
#include "MouseCtr.h"
#include "Dxlib.h"

#define X_DIS (int)((SCREEN_SIZE_X / 2) - (MainBoard->GetBoardSize().x / 2)*CHIPSIZE)
#define Y_DIS (int)((SCREEN_SIZE_Y / 2) - (MainBoard->GetBoardSize().y / 2)*CHIPSIZE)

#define TESTMODE 0

GameMain::GameMain()
{
	Init();
}
GameMain::~GameMain()
{
}

void GameMain::Init()
{

	for (auto unit : PIECE_ST())
	{
		Mouse[unit] = std::make_shared<MouseCtr>();
		oprt_tbl[unit] = OPRT_TYPE::CPU;
		printf("w");

	}
	oprt_tbl[static_cast<int>(PIECE_ST::B)] = OPRT_TYPE::MAN;

	printf("w");

	auto CreateNewBoard = [&]() {
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
		// �֐���pl_cnt�����Z�����鏈����g�ݍ��񂾂�Z�k�\
		AddPlayer();
		pl_cnt++;
	}
	lpGameTask.currentPlayer = lpGameTask.playerlist.begin();
	(*lpGameTask.currentPlayer)->SetTunrFlg(true);


}


void GameMain::Draw()
{
	MainBoard->Draw();
}

state_ptr GameMain::Update(state_ptr pt)
{
	auto nowPlayer = lpGameTask.currentPlayer;
	// ���݂̃v���C���[�̐F
	auto playerID = static_cast<int>((*nowPlayer)->GetType());
	
	for (auto unit : PIECE_ST())
	{
		if ((*nowPlayer)->GetTunrFlg() == true)
		{
			Mouse[playerID]->Update(oprt_tbl[playerID]);
		}
	}
	auto setNextPlayer = [&](){
		if ((*nowPlayer)->GetTunrFlg()== false)
		{
			if ((*nowPlayer) == lpGameTask.playerlist.back())
			{
				nowPlayer = lpGameTask.playerlist.begin();
				(*nowPlayer)->SetTunrFlg(true);
				return;
			}
			(*nowPlayer++);
			(*nowPlayer)->SetTunrFlg(true);
		}
	};

	DrawString(0, 0, "Main", 0xffffff, 0);
	MainBoard->Update();
	(*lpGameTask.currentPlayer)->TurnAct(Mouse[playerID]);
	for (auto itr : GameTask::GetInstance().playerlist)
	{
		(*itr).Update();
	}
	// ifTurnAct��true�̏ꍇ�A�v���C���[�`�F���W�������s��
	

	if (MainBoard->gameEndFlg)
	{
		// GameRessult��MainBoard�̏������������g���̂ň����œn��
		return std::make_unique<GameResult>(MainBoard);

	}
	setNextPlayer();
	return pt;
}


void GameMain::CurrentPlayerChange()
{
	
	// ���݂̏��Ԃ�\������֐����Ă��
}
void GameMain::AddPlayer()
{
	//std::make_shared<Player>();
	lpGameTask.playerlist.push_back(std::make_shared<Player>());

}

