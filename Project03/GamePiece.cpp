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

GamePiece::GamePiece()
{
}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset ,PIECE_ST st)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	Init();
	SetState(st);
	SetOldState(PIECE_NON);
}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	Init();
	SetOldState(PIECE_NON);
}


GamePiece::GamePiece(VECTOR2 pos,PIECE_ST st)
{
	this->pos = pos;
	Init();
	SetState(st);
	SetOldState(PIECE_NON);
	
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
VECTOR2 GamePiece::GetPos()
{
	return pos;
}

bool GamePiece::SetPos(VECTOR2 pos)
{
	this->pos = pos;
	return true;
}

VECTOR2 GamePiece::GetDrawOffset()
{
	return drawOffset;
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

	if (st == PIECE_W)
	{
		//GamePiece::state = std::make_unique<PieceWhite>();
		old_state.push_front(std::make_unique<PieceWhite>());
	}
	else
	{
		old_state.push_front(std::make_unique<PieceBlack>());
	}

	if (st == PIECE_NON)
	{
		/*
		if (state.front()->GetState() == PIECE_W)
		{
			old_state.push_front(std::make_unique<PieceBlack>());
		}
		else
		{
			old_state.push_front(std::make_unique<PieceWhite>());
		}
		*/

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

	if (st == PIECE_W)
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
	return PIECE_NON;
}

void GamePiece::SetReverse(int num)
{
	rev_F = REVERSE_F * num;
}
bool GamePiece::Update()
{
	// 駒反転時の描画

	Draw();
	/*
	if (clearTimer > 0)
	{
		clearTimer--;
		if (clearTimer == 0)
		{
			//return false;
		}
	}*/
	return true;
}
bool GamePiece::ReverseStandby()
{
	clearTimer = ANIM_FRAME;
	return true;
}

void GamePiece::Draw()
{
	DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
		pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
		PIECESIZE,
		(*old_state.begin())->GetDrawColor()
		, true, 1);


	if (rev_F > 0)
	{
		rev_F--;
		//if (rev_F == 0) animF = ANIM_FRAME;
		return;
	}

	int color = GetRand(0xffffff);

	if ((*state.begin()))
	{
		color = (*state.begin())->GetDrawColor();
	}
#ifdef _DEBUG
	else
	{
		std::string txt = ("text\n");
		OutputDebugString(txt.c_str());
	}

#endif // DEBUG


	if (animF > 0)
	{

		DrawOval(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2) - (animF),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			(PIECESIZE)-(animF), PIECESIZE,
			color, true, 1);

/*
		DrawOval(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			(PIECESIZE)-(ANIM_FRAME - animF), PIECESIZE,
			(*old_state.begin())->GetDrawColor()
			, true, 1);
*/
			animF--;
	}
	else
	{
		wait--;
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2)-3,
			PIECESIZE, color, true, 1);
	}

}

void GamePiece::SetWait(int i)
{
	this->wait = i;
}
void GamePiece::SetAnimF(int i)
{
	this->animF = i;
	
}