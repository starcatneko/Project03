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
	void Update();
	void CreateNewBoard();
	void AddPlayer();
	void Draw();
private:

};

