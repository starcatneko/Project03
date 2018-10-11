#include "PieceTray.h"
#include "Dxlib.h"


PieceTray::PieceTray()
{
}

PieceTray::PieceTray(PIECE_ST st)
{
	this->color = st;
}

PieceTray::~PieceTray()
{
}

void PieceTray::SetTray(int boardsize,int plcnt)
{
	for (int i = 0; i < boardsize / plcnt; i++)
	{
		piecelist.push_back(std::make_shared<GamePiece>
			(VECTOR2{ 0,i }, VECTOR2{ 0,0 }, this->color));
	}
}

void PieceTray::DrawTray()
{
	int i = 0;
	for (auto itr : piecelist)
	{
		DrawBox((*itr).GetPos().x , (*itr).GetPos().y * 64,
			(*itr).GetPos().x + 64 , (*itr).GetPos().y *64 + 64,
			0x005500, true);
		(*itr).Draw();
		i++;
		if (!(i < 5))
			break;
	}
}
