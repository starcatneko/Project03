#pragma once
#include "PieceState.h"

class PieceBlack :
	public PieceState
{
public:
	PieceBlack();
	~PieceBlack();
	PIECE_ST GetState();
	unsigned int GetDrawColor();
};

