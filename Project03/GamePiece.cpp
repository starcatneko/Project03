#include "GamePiece.h"
#include "GameBoard.h"
#include "GameTask.h"
#include "DxLib.h"

#define PIECESIZE 25
#define CHIPSIZE 64


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
	this->animF = GETWAIT()*GETWAIT()*4;

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

void GamePiece::Revarse(PIECE_ST st)
{
	state = st;
}

int GamePiece::ColorSet()
{
	int color;
	switch (state)
	{
	case PIECE_B:
		color = 0x000000;
		break;
	case PIECE_W:
		color = 0xffffff;
		break;
	case PIECE_RED:
		color = 0xDD0000;
		break;
	case PIECE_BLU:
		color = 0x0000DD;
		break;
	case PIECE_GRN:
		color = 0x00DD00;
		break;
	case PIECE_YLW:
		color = 0xEEEE00;
		break;
	case PIECE_PPL:
		color = 0xEE00EE;
		break;
	case PIECE_CYN:
		color = 0x00EEEE;
		break;
	default:

		break;
	}
	return color;
}

void GamePiece::Draw()
{
	int pieceColor = ColorSet();
	
	
	if (animF > 0)
	{
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE + (animF) , pieceColor, true, 1);
		
			animF/=1.18;
	}
	else
	{
		DrawCircle(pos.x*CHIPSIZE + drawOffset.x + (CHIPSIZE / 2),
			pos.y*CHIPSIZE + drawOffset.y + (CHIPSIZE / 2),
			PIECESIZE, pieceColor, true, 1);
	}
}
