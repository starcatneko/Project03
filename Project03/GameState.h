#pragma once
class MouseCtl;

#define state_ptr std::unique_ptr<GameState>

class GameState
{
public:

	virtual ~GameState() = 0;
	//Const‚ÅMouse‚ð—¬‚·
	//Board
	//Player(?)
	virtual state_ptr Update() = 0;
	virtual void Draw() = 0;
};

