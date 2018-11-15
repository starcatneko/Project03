#pragma once

enum class PIECE_ST
{
	NON,		
	B,
	W,
	RED,
	BLU,
	GRN,
	YLW,
	PPL,
	CYN,
	MAX
};

PIECE_ST begin(PIECE_ST);
PIECE_ST end(PIECE_ST);
int operator* (PIECE_ST state);
PIECE_ST operator++ (PIECE_ST &state);
PIECE_ST operator-- (PIECE_ST &state);