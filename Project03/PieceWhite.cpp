#include "PieceWhite.h"
#include "DxLib.h"


PieceWhite::PieceWhite()
{
	OutputDebugString("White\n");

}


PieceWhite::~PieceWhite()
{
		
}

PIECE_ST PieceWhite::GetState()
{
	return PIECE_ST::W;
}

unsigned int PieceWhite::GetDrawColor()
{
	return 0xffffff;
}
