#pragma once
#include "GameState.h"
class GameTitle :
	public GameState
{
public:
	GameTitle();
	~GameTitle();

	void Update();
	void Draw();
};

