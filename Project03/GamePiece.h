#pragma once
#include "VECTOR2.h"

enum PIECE_ST;

class GamePiece
{
public:
	GamePiece();
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset, PIECE_ST st);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset);
	GamePiece(VECTOR2 pos , PIECE_ST st);
	~GamePiece();
	VECTOR2 GetPos();
	// stateをセットする
	void SetState(PIECE_ST st);
	// 現在のstateを返す
	PIECE_ST GetState();
	// 駒を裏返す
	void Revarse();
	void Draw();
private:

	VECTOR2 pos;
	// 描画用のずらす値
	VECTOR2 drawOffset;
	PIECE_ST state;

};

