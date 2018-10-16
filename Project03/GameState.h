#pragma once
class MouseCtl;

class GameState
{
public:
	virtual ~GameState() = 0;
	//Const‚ÅMouse‚ð—¬‚·
	//Board
	//Player(?)
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

