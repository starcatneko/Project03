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
	VECTOR2 GetBoardSize();
	void CurrentPlayerChange();
private:
	std::weak_ptr<GameBoard> Board;

};

