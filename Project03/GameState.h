#pragma once
class MouseCtl;
#include <memory>

#define state_ptr std::unique_ptr<GameState>

struct GameState
{
	virtual ~GameState() = 0;
	//Const‚ÅMouse‚ð—¬‚·
	//Board
	//Player(?)
	virtual state_ptr Update(state_ptr pt) = 0;
	virtual void Draw() = 0;
};

