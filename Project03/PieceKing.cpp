#include "PieceKing.h"
#include "ImageMng.h"



PieceKing::PieceKing()
{
}


PieceKing::~PieceKing()
{
}

PIECE_ST PieceKing::GetState()
{
	return PIECE_KING;
}

unsigned int PieceKing::GetDrawColor()
{
	ImageMng::GetInstance().LoadImg("image/test.jpg");
	ImageMng::GetInstance().DrawImg({0,0},"image/test.jpg",true);
	return 0;
}
