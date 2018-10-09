#pragma once
#include "PieceState.h"

class PieceKing :
	public PieceState
{
public:
	PieceKing();
	~PieceKing();
	PIECE_ST GetState();
	unsigned int GetDrawColor();
};

