#include "Player.h"
#include "GameBoard.h"
#include "PieceTray.h"
#include "GameTask.h"
#include "MouseCtr.h"

int Player::playercnt = 0;

Player::Player()
{
	Player::playerNo = playercnt++;
	Player::piecetype = PIECE_ST(this->playerNo + 1);
	Player::pieceTray = std::make_unique<PieceTray>(this->piecetype);
	Player::ChangeTimer = 0;
	Player::turnStartTimer = 0;

	//this->SetTray();
}



Player::~Player()
{
	playercnt--;
}

void Player::Update()
{
	pieceTray->DrawTray({ (playerNo != 1 ? 11 * 64 : 0), 0});
}

void Player::SetTray()
{
	this->pieceTray = std::make_unique<PieceTray>(this->piecetype);
}

int Player::GetNo()
{
	return playerNo;
}

void Player::SelectTray(VECTOR2 pos)
{
	pieceTray->SelectTrayPiece(pos);
}


PIECE_ST Player::GetType()
{
	return piecetype;
}

void Player::DeleteTrayPiece()
{
	pieceTray->TrayUpdate();
}

bool Player::CheckChangeTurn()
{
	return (ChangeTimer > 0);
}

void Player::TurnAct()
{
	//pieceTray->SetTurnFlg(true);
	//lpGameTask.Board->CurrentSetUpData();
	if (GetTunrFlg() == false)
	{
		ChangeTimer--;
		return;
	}	
	if (turnStartTimer > 0)
	{
		turnStartTimer--;
		if (turnStartTimer == 0)
		{
			lpMouse.SetOprtType(static_cast<int>(lpCurrentPlayer->GetType()));
		}
		return;
	}
	// TurnActのピースが設置のif内
	// ピースを設置したらプレイヤーが切り替わるから
	if ((lpMouse.GetButton() & 0b0001) != 0)
	{
		lpGameTask.Board->SetPiece(lpMouse.GetPos());
	}

}

bool Player::SetTunrFlg(bool flg)
{
	if (flg == true)
	{
		turnStartTimer = 30;
	}
	 return pieceTray->SetTurnFlg(flg);
}

bool Player::GetTunrFlg()
{
	return pieceTray->GetTurnFlg();

}

int Player::GetScore()
{
	return pieceTray->GetScore();
}

void Player::SetTurnTimer(int time)
{
	ChangeTimer = time + TURN_CHANGE_WAIT;
}
int Player::GetTurnTimer()
{
	return ChangeTimer;
}

/*Playerのpublicに
メンバ関数void型のSetTurnFlg
を作る
PlayerのSetTurnFlg内の処理が
pieceTray->SetTurnFlg(引数);*/


void Player::ChangePlSet()
{

}