#include "GameResult.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "GameTitle.h"

#include "MouseCtr.h"
#include "DxLib.h"

GameResult::GameResult()
{
	Board = lpGameTask.SetBoard();
}


GameResult::~GameResult()
{
}

void GameResult::Update()
{
}



void GameResult::Update()
{
	Board.lock()->Update();

	if ((Mouse->GetButton() & 0b0001) != 0)
	{
		lpGameTask.state = std::make_unique<GameTitle>();

	}

}

void GameResult::Draw()
{
}
