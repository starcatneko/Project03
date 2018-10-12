#include "Player.h"
#include "GameBoard.h"
#include "PieceTray.h"

int Player::playercnt = 0;
Player::Player()
{
	this->playerNo = playercnt++;
	this->piecetype = PIECE_ST(this->playerNo + 1);
	this->pieceTray = std::make_unique<PieceTray>(this->piecetype);
}



Player::~Player()
{
	Player::playercnt = 0;
}

void Player::Update()
{
	pieceTray->DrawTray({ (playerNo != 1 ? 11 * 64 : 0), 0});
}

void Player::SetTray(int boardsize)
{
	pieceTray->SetTray(boardsize, Player::playercnt);
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
