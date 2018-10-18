#pragma once
#include "GameState.h"
#include <memory>

class GameBoard;
class MouseCtr;
class GamePiece;
class Player;

class GameMain :
	public GameState
{
public:
	GameMain();
	~GameMain();

	state_ptr Update(state_ptr pt);
	void Draw();
	void CurrentPlayerChange();
private:

};

