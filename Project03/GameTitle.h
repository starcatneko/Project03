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
	//state_ptr Update();
	state_ptr Update(state_ptr pt);
	void CreateNewBoard();
	void AddPlayer();
	void Draw();
private:

};

