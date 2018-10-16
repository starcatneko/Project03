#include "GameMain.h"
#include "GameTask.h"
#include "Dxlib.h"


GameMain::GameMain()
{
	Board = lpGameTask.SetBoard();
}


GameMain::~GameMain()
{
}


void GameMain::Draw()
{
}

void GameMain::Update() 
{

	DrawString(0, 0, "Main", 0xffffff, 0);
	Board->Update();
	//Mouse->GetPos().x;

	(*currentPlayer)->TurnAct();

	// ifTurnAct��true�̏ꍇ�A�v���C���[�`�F���W�������s��

	if ((Mouse->GetButton() & 0b0001) != 0)
	{
		Board.lock()->SetPiece(Mouse->GetPos());
	}
	if ((Mouse->GetButton() & 0b0010) != 0)
	{
		Board->Debug_SetPiece(Mouse->GetPos());
	}
}


void GameMain::CurrentPlayerChange()
{
	(*currentPlayer)->SetTunrFlg(false);
	if ((*lpGameTask.currentPlayer) == playerlist.back())
	{
		currentPlayer = playerlist.begin();
		(*currentPlayer)->SetTunrFlg(true);
		return;
	}

	(*lpGameTask.currentPlayer++);
	(*currentPlayer)->SetTunrFlg(true);

	// ���݂̏��Ԃ�\������֐����Ă��
}


VECTOR2 GameMain::GetBoardSize()
{
	return *lpGameTask.)GetBoardSize();
}