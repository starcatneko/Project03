#include "GameResult.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "GameTitle.h"

#include "MouseCtr.h"
#include "DxLib.h"

GameResult::GameResult()
{
	
}


GameResult::~GameResult()
{
}


void GameResult::Update()
{
	lpGameTask.Board->Update();

	if ((lpGameTask.Mouse->GetButton() & 0b0001) != 0)
	{
		lpGameTask.state = std::make_unique<GameTitle>();

	}

}

void GameResult::Draw()
{
}
