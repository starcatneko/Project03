#pragma once
#include "GameState.h"

class GameMouse;


class GameTitle :
	public GameState
{
public:
	GameTitle();
	~GameTitle();

	//void Update();
	//state_ptr Update();
	state_ptr Update(state_ptr pt);
	void Draw();
private:

};

