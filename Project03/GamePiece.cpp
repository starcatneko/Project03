#include "GamePiece.h"

GamePiece::GamePiece()
{

}


GamePiece::GamePiece(VECTOR2 pos,PIECE_ST st)
{
	this->pos = pos;
	state = st;
}

GamePiece::~GamePiece()
{
}

VECTOR2 GamePiece::GetPos()
{
	return pos;
}
