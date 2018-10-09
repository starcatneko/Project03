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
	this->animF = GETWAIT()*GETWAIT()*4;


}


GamePiece::GamePiece(VECTOR2 pos,PIECE_ST st)
{
	this->pos = pos;
	SetState(st);
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
/*
int GamePiece::ColorSet()
{
	int color;
	switch (state->GetState())
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
*/
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