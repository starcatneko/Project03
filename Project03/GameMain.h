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

	void Update();
	void Draw();
	void CurrentPlayerChange();
private:

};

