#include "GameResult.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "GameTitle.h"

#include "MouseCtr.h"
#include "DxLib.h"

GameResult::GameResult()
{

}

GameResult::GameResult(Board_ptr pt)
{
	Board = pt;
}


GameResult::~GameResult()
{
}


state_ptr  GameResult::Update(state_ptr  pt)
{
	lpGameTask.Board->Update();

	if ((lpGameTask.Mouse->GetButton() & 0b0001) != 0)
	{
		lpGameTask.state = std::make_unique<GameTitle>();

	}
	return pt;
}

void GameResult::Draw()
{
}
