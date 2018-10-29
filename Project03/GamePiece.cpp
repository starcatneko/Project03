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
#define REVERSE_F 16


GamePiece::GamePiece()
{
}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset ,PIECE_ST st)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	SetState(st);
}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	rev_Num = 0;
	rev_F = 0;
	this->animF = GETWAIT()*GETWAIT()*4;


}


GamePiece::GamePiece(VECTOR2 pos,PIECE_ST st)
{
	this->pos = pos;
	rev_Num = 0;
	rev_F = 0;
	SetState(st);
}

GamePiece::~GamePiece()
{
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

void GamePiece::SetState(PIECE_ST st)
{
	// Šù‚Éƒs[ƒX‚Éstate‚ª“ü‚Á‚Ä‚¢‚éê‡
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
	rev_Num = num;
	rev_F = REVERSE_F;
}

void GamePiece::Draw()
{
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

	// ‹î”½“]‚Ì•`‰æ
	if (rev_Num > 0)
	{
		if (rev_F > 0)
		{
			rev_Num--;
		}
		rev_F--;
		return;
	}

	if (animF > 0)
	{
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE + (animF) , color, true, 1);
			
		if(wait <= 0)
			animF--;
	}
	else
	{
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE, color, true, 1);
	}
	wait--;
}

void GamePiece::SetWait(int i)
{
	this->wait = i;
}
void GamePiece::SetAnimF(int i)
{
	this->animF = i;
	
}