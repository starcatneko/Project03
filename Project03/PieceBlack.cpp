#include "PieceBlack.h"



PieceBlack::PieceBlack()
{
}


PieceBlack::~PieceBlack()
{
}

PIECE_ST PieceBlack::GetState()
{
	return PIECE_B;
}

unsigned int PieceBlack::GetDrawColor()
{
	return 0x000000;
}
