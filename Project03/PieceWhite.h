#pragma once
#include "PieceState.h"
class PieceWhite :
	public PieceState
{
public:
	PieceWhite();
	~PieceWhite();

	PIECE_ST GetState();
	unsigned int GetDrawColor();
};

