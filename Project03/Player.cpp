#include "Player.h"
#include "GameBoard.h"


Player::Player()
{
}

Player::Player(int number)
{
	playerNo = number;
	piecetype = PIECE_ST(number+1);
}


Player::~Player()
{

}

void Player::Init()
{
}

void Player::Update()
{
	
}

void Player::SetPiece()
{


}

int Player::GetNo()
{
	return playerNo;
}


PIECE_ST Player::GetType()
{
	return piecetype;
}
