#pragma once

enum class PIECE_ST
{
	PIECE_NON,
	PIECE_B,
	PIECE_W,
	PIECE_RED,
	PIECE_BLU,
	PIECE_GRN,
	PIECE_YLW,
	PIECE_PPL,
	PIECE_CYN,
	PIECE_MAX
};

PIECE_ST begin(PIECE_ST);
PIECE_ST end(PIECE_ST);
PIECE_ST operator* (PIECE_ST state);
PIECE_ST operator++ (PIECE_ST &state);
PIECE_ST operator-- (PIECE_ST &state);