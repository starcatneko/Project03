#pragma once
#include "GameState.h"

class GameMouse;

enum PIECE_ST;

class GameTitle :
	public GameState
{
public:
	GameTitle();
	~GameTitle();

	//void Update();
	void Update(const MouseCtr & mouse);
	void CreateNewBoard();
	void AddPlayer();
	void Draw();
};

