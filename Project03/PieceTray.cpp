#include "PieceTray.h"
#include "GameTask.h"
#include "Dxlib.h"

#define lpGameTask GameTask::GetInstance()

const int CHIPSIZE = 64;

PieceTray::PieceTray()
{
}

PieceTray::PieceTray(PIECE_ST st)
{
	// PieceTray::color = st;
	int piecemax = (lpGameTask.GetBoardSize().x*lpGameTask.GetBoardSize().y)/2;
	this->color = st;
	this->selectPiece = 0;


	// ä˘Ç…ÉsÅ[ÉXÇ…stateÇ™ì¸Ç¡ÇƒÇ¢ÇÈèÍçá
	if (PieceTray::piecelist.size())
	{
		for (int j = 0; j < piecelist.size(); j++)
		{
			piecelist.push_back(std::make_shared<GamePiece>
				(VECTOR2{ 0,0 }, this->pos, this->color));
		}
	}

	for (int j = 0; j < piecemax; j++)
	{
		AddPiece();
	}

}


bool PieceTray::AddPiece()
{
	piecelist.push_back(std::make_shared<GamePiece>
		(VECTOR2{ 0,0 }, this->pos, this->color));
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