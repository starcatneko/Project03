#include "PieceTray.h"
#include "GameTask.h"
#include "Dxlib.h"

const int CURRENTBOXSIZE = 5;
const int CHIPSIZE = 64;

#define piecemax (lpGameTask.GetBoardSize().x*lpGameTask.GetBoardSize().y) / 2


PieceTray::PieceTray()
{
}

PieceTray::PieceTray(PIECE_ST st)
{
	// PieceTray::color = st;
	this->color = st;
	this->selectPiece = 0;
	this->turnFlag = false;
	//int piecemax = (lpGameTask.GetBoardSize().x*lpGameTask.GetBoardSize().y) / 2;

	for (int j = 0; j < piecemax; j++)
	{
		pos = VECTOR2{ 0,j } +VECTOR2{ (this->color == PIECE_B ? 0 : 11),0};
		AddPiece();
	}

}


bool PieceTray::AddPiece()
{
	piecelist.push_back(std::make_shared<GamePiece>
		(this->pos, VECTOR2{0,31}, this->color));
	return true;
}


PieceTray::~PieceTray()
{
	this->color = PIECE_NON;
}

void PieceTray::SetTray(int boardsize,int plcnt)
{

	this->pos = { (color == PIECE_B ? 0 : 11) * CHIPSIZE,128 };
}

void PieceTray::SelectTrayPiece(VECTOR2 pos)
{
	if (pos.x > this->pos.x * CHIPSIZE&&
		pos.x < this->pos.x* CHIPSIZE + CHIPSIZE &&
		pos.y > this->pos.y &&
		pos.y < this->pos.y + CHIPSIZE * 5)
	{
		selectPiece = (pos.y- this->pos.y) / CHIPSIZE;
	}
}

void PieceTray::DrawTray(VECTOR2 DrawOffset)
{
	int i = 0;	


	if (turnFlag == true)
	{
		DrawBox(pos.x* CHIPSIZE - 5,
			pos.y - 5,
			pos.x * CHIPSIZE + CHIPSIZE + 5,
			pos.y + CHIPSIZE * 5 + 5,
			0xEEEEEE, true);
	}

	DrawBox(pos.x * CHIPSIZE,
		pos.y,
		pos.x * CHIPSIZE + CHIPSIZE,
		pos.y + CHIPSIZE * 5,
		0x008800, true);

	// DrawBox (pos.x,pos.y,pos.x +70,pos.y +300
	DrawBox(pos.x * CHIPSIZE,
		pos.y + (CHIPSIZE* selectPiece),
		pos.x * CHIPSIZE + CHIPSIZE,
		pos.y + (CHIPSIZE*selectPiece)+ CHIPSIZE,
		0x00FF00, true);

	DrawFormatString(pos.x*2, pos.y + 128, 0xFFFF00, "%d", piecelist.size());

	for (auto itr : piecelist)
	{
		(*itr).SetPos({ pos.x,i });
		(*itr).Update();
		if (!(++i < 5))
			break;
	}
}

void PieceTray::TrayUpdate()
{
	int i = 0;
	
	for (auto itr = piecelist.begin();
		itr != piecelist.end();itr++)
	{
		if (selectPiece == i)
		{
			itr = piecelist.erase(itr);
			return;
		}
		i++;
		if (i >= 5)
		{
			break;
		}
	}
}

bool PieceTray::SetTurnFlg(bool flg)
{
		turnFlag = flg;
		if(!flg)TrayUpdate();
		return turnFlag;
}

bool PieceTray::GetTurnFlg()
{
	return turnFlag;
}

int PieceTray::GetScore()
{
	return piecemax - piecelist.size();
}