#include "GamePiece.h"
#include "DxLib.h"

#define PIECESIZE 25
#define CHIPSIZE 64

enum PIECE_ST
{
	PIECE_NON,
	PIECE_W,
	PIECE_B,
	PIECE_MAX
};


GamePiece::GamePiece()
{

}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset ,PIECE_ST st)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	this->state = st;
}

GamePiece::GamePiece(VECTOR2 pos, VECTOR2 drawOffset)
{
	this->pos = pos;
	this->drawOffset = drawOffset;
	this->state = PIECE_NON;
}


GamePiece::GamePiece(VECTOR2 pos,PIECE_ST st)
{
	this->pos = pos;
	state = st;
}

GamePiece::~GamePiece()
{
}

VECTOR2 GamePiece::GetPos()
{
	return pos;
}

void GamePiece::SetState(PIECE_ST st)
{
	state = st;
}

PIECE_ST GamePiece::GetState()
{
	return state;
}

void GamePiece::Revarse()
{
	if (state == PIECE_W)
	{
		state = PIECE_B;
	}

	if (state == PIECE_B)
	{
		state = PIECE_W;
	}
}

void GamePiece::Draw()
{
	if (state == PIECE_NON)
	{
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE, 0xAAAAAA, true, 1);
	}

	if (state == PIECE_W)
	{
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE, 0xeeeeee, true, 1);
	}
	if (state == PIECE_B)
	{
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE, 0x111111, true, 1);
	}

}
