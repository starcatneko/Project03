#pragma once
// Stateデザイン
// 実体化はさせない
//　マスに置かれている石

#include "PIECE_ST.h"

class PieceState
{
public:
	virtual ~PieceState();
	virtual PIECE_ST GetState() = 0;
	virtual unsigned int GetDrawColor() = 0;

protected:
};

