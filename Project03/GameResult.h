#pragma once
#include "GameState.h"

class Board;

class GameResult:
	public GameState
{
public:
	GameResult();
	GameResult(Board_ptr pt);
	~GameResult();

	state_ptr Update(state_ptr pt);
	void Draw();

private:

	int pieceCount[int(PIECE_ST::MAX)];
	Board_ptr Board;

};

