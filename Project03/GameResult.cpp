#include "GameResult.h"
#include "GameTask.h"

#include "DxLib.h"

GameResult::GameResult()
{
}


GameResult::~GameResult()
{
}

void GameResult::Update()
{
}



void GameResult::Update()
{
	Board->Update();

	if ((Mouse->GetButton() & 0b0001) != 0)
	{
		lpGameTask.ChangeScene();
	}

}

void GameResult::Draw()
{
}
