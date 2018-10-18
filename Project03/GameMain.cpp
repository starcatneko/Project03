#include "GameMain.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "MouseCtr.h"
#include "Dxlib.h"


GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}


void GameMain::Draw()
{
}

state_ptr GameMain::Update(state_ptr pt)
{

	DrawString(0, 0, "Main", 0xffffff, 0);
	lpGameTask.Board->Update();

	(*lpGameTask.currentPlayer)->TurnAct();

	// ifTurnAct��true�̏ꍇ�A�v���C���[�`�F���W�������s��

	if ((lpGameTask.Mouse->GetButton() & 0b0001) != 0)
	{
		lpGameTask.Board->SetPiece(lpGameTask.Mouse->GetPos());
	}
	if ((lpGameTask.Mouse->GetButton() & 0b0010) != 0)
	{
		lpGameTask.Board->Debug_SetPiece(lpGameTask.Mouse->GetPos());
	}

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

	// ���݂̏��Ԃ�\������֐����Ă��
}
