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
	// ���ݑI�����Ă���g���C��̃s�[�X�̈ʒu
	int selectPiece;	

	// �\���p�I�t�Z�b�g
	VECTOR2 pos;
	piece_list piecelist;
	PIECE_ST color;
};

