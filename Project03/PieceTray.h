#pragma once
#include "VECTOR2.h"

#include <vector>
#include <list>
#include <memory>

#include "GamePiece.h"

enum PIECE_ST;

class PieceTray
{
public:
	PieceTray();
	PieceTray(PIECE_ST st);
	~PieceTray();

	void SetTray();
	void DrawTray();
private:
	piece_list piecelist;
	PIECE_ST color;
};

