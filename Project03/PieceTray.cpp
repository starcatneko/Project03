#include "PieceTray.h"
#include "Dxlib.h"


PieceTray::PieceTray()
{
}

PieceTray::PieceTray(PIECE_ST st)
{
	this->color = st;
	for (int i = 0; i < ”Õ–Ê/ƒvƒŒƒCƒ„[”; i++)
	{
		piecelist.push_back(std::make_shared<GamePiece>
			(VECTOR2{ 0,i*64 }, VECTOR2{ 0,0 }, this->color));
	}
}

PieceTray::~PieceTray()
{
}

void PieceTray::SetTray()
{
}

void PieceTray::DrawTray()
{
	for (auto itr : piecelist)
	{
		DrawBox((*itr).GetPos().x, (*itr).GetPos().y,
			(*itr).GetPos().x + 64, (*itr).GetPos().y + 64,
			0x005500, true);
		(*itr).Draw();
	}
}
