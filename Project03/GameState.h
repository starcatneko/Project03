#pragma once
class MouseCtl;

class GameState;

typedef std::unique_ptr<GameState> state_ptr;


class GameState
{
public:

	virtual ~GameState() = 0;
	//Const��Mouse�𗬂�
	//Board
	//Player(?)
	virtual state_ptr Update() = 0;
	virtual void Draw() = 0;
};

