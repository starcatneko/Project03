#include "Player.h"
#include "GameBoard.h"
#include "PieceTray.h"
#include "GameTask.h"

#define lpGameTask GameTask::GetInstance()



int Player::playercnt = 0;

Player::Player()
{
	this->playerNo = playercnt++;
	this->piecetype = PIECE_ST(this->playerNo + 1);
	this->pieceTray = std::make_unique<PieceTray>(this->piecetype);
}



Player::~Player()
{

}

void Player::Update()
{
	pieceTray->DrawTray({ (playerNo != 1 ? 11 * 64 : 0), 0});
}

void Player::SetTray()
{
	pieceTray->SetTray({ lpGameTask.GetBoardSize().x*lpGameTask.GetBoardSize().y }, Player::playercnt);
}

int Player::GetNo()
{
	return playerNo;
}



bool Player::Draw()
{
	if (pieceTray)
	{
		//pieceTray->DrawTray();
		return true;
	}

	return false;
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

void Player::TurnAct()
{
	//pieceTray->SetTurnFlg(true);
	// TurnActのピースが設置のif内
	// ピースを設置したらプレイヤーが切り替わるから
	/*
	if ((Mouse->GetButton() & 0b0001) != 0)
	{
		Board->SetPiece(Mouse->GetPos());
	}*/
	//ピースの数をチェック
	//マウス取得{
	//設置可能なら設置
	//	{
	//
	//	}
	//}
}

bool Player::SetTunrFlg(bool flg)
{
	 return pieceTray->SetTurnFlg(flg);

}


/*Playerのpublicに
メンバ関数void型のSetTurnFlg
を作る

PlayerのSetTurnFlg内の処理が
pieceTray->SetTurnFlg(引数);


*/