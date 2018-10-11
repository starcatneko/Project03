#include "PieceBlack.h"
#include "DxLib.h"



PieceBlack::PieceBlack()
{
	OutputDebugString("Black\n");

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
