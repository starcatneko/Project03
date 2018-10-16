#pragma once
#include "GameState.h"
class GameMain :
	public GameState
{
public:
	GameMain();
	~GameMain();

	void Update();
	void Draw();
};

