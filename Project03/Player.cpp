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

}

void Player::Update()
{
	pieceTray->DrawTray();
}

void Player::SetTray(int boardsize)
{
	pieceTray->SetTray(boardsize, Player::playercnt);
}

int Player::GetNo()
{
	return playerNo;
}


PIECE_ST Player::GetType()
{
	return piecetype;
}
