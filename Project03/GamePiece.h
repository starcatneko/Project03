#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <memory>

#include "PieceState.h";
class GameBoard;
class Player;

class GamePiece
{
public:
	GamePiece();
	GamePiece(VECTOR2 pos , PIECE_ST st);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset, PIECE_ST st);
	~GamePiece();
	VECTOR2 GetPos();
	// stateをセットする
	void SetState(PIECE_ST st);
	// 現在のstateを返す
	PIECE_ST GetState();
	// 駒を裏返す
	void Revarse(PIECE_ST st);
	int ColorSet();
	void Draw();
	void SetWait(int i);
	void SetAnimF(int i);
private:
	std::unique_ptr <PieceState> state;
	// 盤面上の座標
	VECTOR2 pos;
	// 描画用のずらす値
	VECTOR2 drawOffset;
	// アニメーション制御フレーム用
	int animF;
	int wait;
};

