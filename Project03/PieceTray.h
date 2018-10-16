#pragma once
#include "VECTOR2.h"

#include <vector>
#include <list>
#include <memory>

#include "GamePiece.h"
#include "PieceState.h"

//enum PIECE_ST;

class PieceTray
{
public:
	PieceTray();
	PieceTray(PIECE_ST st);
	~PieceTray();
	void SetTray(int boardsize, int plcnt);
	void SelectTrayPiece(VECTOR2 pos);
	void DrawTray(VECTOR2 DrawOffset);
	void TrayUpdate();
	bool SetTurnFlg(bool flg);
private:

	bool turnFlag;
	bool AddPiece();
	// 現在選択しているトレイ上のピースの位置
	int selectPiece;	

	// 表示用オフセット
	VECTOR2 pos;
	piece_list piecelist;
	PIECE_ST color;
};

