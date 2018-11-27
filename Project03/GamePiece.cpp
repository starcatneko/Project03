#include "GamePiece.h"
#include "GameBoard.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "DxLib.h"
#include "PieceState.h"

#include "PieceWhite.h"
#include "PieceBlack.h"

#define PIECESIZE 25
#define CHIPSIZE 64
#define REVERSE_F 4
#define ANIM_FRAME 10

//using namespace PIECE_ST;

GamePiece::GamePiece()
{
}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset ,PIECE_ST st)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	Init();
	SetState(st);
	SetOldState(PIECE_ST::NON);
}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	Init();
	SetState(PIECE_ST::NON);
	SetOldState(PIECE_ST::NON);
}


GamePiece::GamePiece(VECTOR2 pos,PIECE_ST st)
{
	this->pos = pos;
	Init();
	SetState(st);
	SetOldState(PIECE_ST::NON);
	
}

GamePiece::~GamePiece()
{
}


void GamePiece::Init()
{
	rev_Num = 0;
	rev_F = 0;
	animF = 0;
	clearTimer = 0;
}

void GamePiece::SetOldState(PIECE_ST st,int cnt)
{
	return;
}
bool GamePiece::SetDrawOffset(VECTOR2 pos)
{
	this->drawOffset = pos;
	return true;
}

void GamePiece::SetOldState(PIECE_ST st)
{
	// 既にピースにstateが入っている場合
	if (GamePiece::old_state.size())
	{
		// GamePiece::state.erase(GamePiece::state.begin);
		GamePiece::old_state.pop_front();
	}

	if (st == PIECE_ST::W)
	{
		//GamePiece::state = std::make_unique<PieceWhite>();
		old_state.push_front(std::make_unique<PieceWhite>());
	}
	else
	{
		old_state.push_front(std::make_unique<PieceBlack>());
	}

	if (st == PIECE_ST::NON)
	{
		if (state.front()->GetState() == PIECE_ST::W)
		{
			old_state.push_front(std::make_unique<PieceWhite>());
		}
		else
		{
			old_state.push_front(std::make_unique<PieceBlack>());
		}
	}
}

void GamePiece::SetState(PIECE_ST st)
{
	// 既にピースにstateが入っている場合
	if (GamePiece::state.size())
	{
		// GamePiece::state.erase(GamePiece::state.begin);
		GamePiece::state.pop_front();
	}

	if (st == PIECE_ST::W)
	{
		//GamePiece::state = std::make_unique<PieceWhite>();
		state.push_front(std::make_unique<PieceWhite>());
	}
	else
	{
		state.push_front(std::make_unique<PieceBlack>());
	}
}

PIECE_ST GamePiece::GetState()
{
	if ((*state.begin()))
	{
		return (*state.begin())->GetState();
	}
	return PIECE_ST::NON;
}

void GamePiece::SetReverse(int num)
{
	rev_F = REVERSE_TIME * num;
}
bool GamePiece::Update()
{
	return true;
}
bool GamePiece::ReverseStandby()
{
	clearTimer = REVERSE_TIME;
	return true;
}

void GamePiece::Draw()
{
	int oldcolor = GetRand(0xffffff);
	int color = GetRand(0xffffff);
	int SetF = PIECESIZE - (PIECESIZE / abs(animF - REVERSE_TIME));//(PIECESIZE / abs(animF - REVERSE_TIME));
	if ((*old_state.begin()))
	{
		oldcolor = (*old_state.begin())->GetDrawColor();
		if ((*old_state.begin())->GetState() == PIECE_ST::NON)
		{
			oldcolor = 0xFFFFFF;
		}
	}
	if ((*state.begin()))
	{
		color = (*state.begin())->GetDrawColor();
	}

	if (rev_F != 0)
	{

		if (rev_F < PIECESIZE)
		{
			DrawOval(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
				pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
				rev_F*2 - PIECESIZE , PIECESIZE, oldcolor, true, 1);
		}
		else
		{
			DrawOval(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
				pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
				PIECESIZE, PIECESIZE, oldcolor, true, 1);
		}

		rev_F--;
		return;
	}


	if (animF > 0)
	{
		DrawOval(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			SetF, PIECESIZE, color, true, 1);
		animF--;
	}
	else
	{
		wait--;
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE, color, true, 1);
	}

}
