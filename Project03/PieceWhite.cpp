#include "PieceWhite.h"



PieceWhite::PieceWhite()
{
	
}


PieceWhite::~PieceWhite()
{
		
}

PIECE_ST PieceWhite::GetState()
{
	return PIECE_W;
}

unsigned int PieceWhite::GetDrawColor()
{
	return 0xffffff;
}
