#pragma once
#include "VECTOR2.h"

enum PIECE_ST
{
	PIECE_NON,
	PIECE_W,
	PIECE_B,
	PIECE_MAX
};

class GamePiece
{
public:
	GamePiece();
	GamePiece(VECTOR2 pos , PIECE_ST st);
	~GamePiece();
	VECTOR2 GetPos();

	/*
	// ‹î‚ð— •Ô‚· ”½“]:true ”½“]‚µ‚È‚©‚Á‚½:false
	bool Change();*/

private:
	VECTOR2 pos;
	PIECE_ST state;
};

