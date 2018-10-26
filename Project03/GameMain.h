#pragma once
#include "GameState.h"
#include <memory>
#include <vector>
#include <list>

class GameBoard;
class MouseCtr;
class GamePiece;
#include "Player.h"
typedef std::shared_ptr<GameBoard> Board_ptr;


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
	void AddPlayer();
	Board_ptr MainBoard;
};

