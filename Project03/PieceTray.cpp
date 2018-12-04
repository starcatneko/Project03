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

	for (int j = 0; j < piecemax-2; j++)
	{
		pos = VECTOR2{ 0,j } +VECTOR2{ (this->color == PIECE_ST::B ? 0 : 11),0};
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
	this->color = PIECE_ST::NON;
}

void PieceTray::SetTray(int boardsize,int plcnt)
{

	this->pos = { (color == PIECE_ST::B ? 0 : 11) * CHIPSIZE,128 };
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
	VECTOR2 Offset = { 20,0 };

	if (turnFlag == true)
	{
		DrawBox(pos.x* CHIPSIZE - 5 + Offset.x,
			pos.y - 5 + Offset.y,
			pos.x * CHIPSIZE + CHIPSIZE + 5 + Offset.x,
			pos.y + CHIPSIZE * 5 + 5 + Offset.y,
			0xEEEEEE, true);
	}

	DrawBox(pos.x * CHIPSIZE + Offset.x,
		pos.y + Offset.y,
		pos.x * CHIPSIZE + CHIPSIZE + Offset.x,
		pos.y + CHIPSIZE * 5 + Offset.y,
		0x008800, true);

	// DrawBox (pos.x,pos.y,pos.x +70,pos.y +300
	DrawBox(pos.x * CHIPSIZE + Offset.x,
		pos.y + (CHIPSIZE* selectPiece) + Offset.y,
		pos.x * CHIPSIZE + CHIPSIZE + Offset.x,
		pos.y + (CHIPSIZE*selectPiece)+ CHIPSIZE + Offset.y,
		0x00FF00, true);

	DrawFormatString(pos.x*2 + Offset.x,
		pos.y + 128 + Offset.y,
		0xFFFF00, "%d", piecelist.size());

	for (auto itr : piecelist)
	{
		(*itr).SetPos({ pos.x,i });
		(*itr).SetDrawOffset({ Offset.x,pos.y + Offset.y });
		(*itr).Draw();
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
			turnFlag = false;
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
	return piecemax - int(piecelist.size());
}