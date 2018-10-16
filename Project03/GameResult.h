#pragma once
#include "GameState.h"
class GameResult :
	public GameState
{
public:
	GameResult();
	~GameResult();

	void Update();
	void Draw();

private:
	std::weak_ptr<GameBoard> Board;

};

