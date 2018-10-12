#include "PieceTray.h"
#include "Dxlib.h"

const int CHIPSIZE = 64;

PieceTray::PieceTray()
{
}

PieceTray::PieceTray(PIECE_ST st)
{
	// PieceTray::color = st;
	this->color = st;
	this->selectPiece = 0;
}

PieceTray::~PieceTray()
{
	this->color = PIECE_NON;
}

void PieceTray::SetTray(int boardsize,int plcnt)
{

	this->pos = { (color == PIECE_B ? 0 : 11) * CHIPSIZE,128 };
	for (int i = -2; i < boardsize / plcnt; i++)
	{
		AddPiece();
	}
}

void PieceTray::SelectTrayPiece(VECTOR2 pos)
{
	if (pos.x > this->pos.x &&
		pos.x < this->pos.x + CHIPSIZE &&
		pos.y > this->pos.y &&
		pos.y < this->pos.y + CHIPSIZE * 5)
	{
		selectPiece = (pos.y- this->pos.y) / CHIPSIZE;
	}
}

void PieceTray::DrawTray(VECTOR2 DrawOffset)
{
	int i = 0;		
	DrawBox(pos.x,pos.y,
		pos.x + CHIPSIZE,pos.y + CHIPSIZE * 5,
		0x008800, true);

	DrawBox(pos.x,
		pos.y + (CHIPSIZE* selectPiece),
		pos.x + CHIPSIZE,
		pos.y + (CHIPSIZE*selectPiece)+ CHIPSIZE,
		0x00FF00, true);


	for (auto itr : piecelist)
	{
		(*itr).SetPos({ 0, i });
		(*itr).Draw();
		i++;
		if (!(i < 5))
			break;
	}
}

void PieceTray::TrayUpdate()
{
	int i = 0;

	for (auto itr = piecelist.begin();itr != piecelist.end();itr++)
	{
		if (selectPiece == i)
		{
			itr = piecelist.erase(itr);
			break;
		}
		i++;
		if (i >= 5)
		{
			break;
		}
	}

}

bool PieceTray::AddPiece()
{
	piecelist.push_back(std::make_shared<GamePiece>
		(VECTOR2{ 0,0 }, this->pos, this->color));
	return true;
}
