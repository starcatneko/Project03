#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <memory>

#include "PieceState.h"

class GameBoard;
class Player;
class GamePiece;
//enum PIECE_ST;

typedef std::weak_ptr<GamePiece> piece_shared_w;

typedef std::shared_ptr<GamePiece> piece_shared;

typedef std::list<piece_shared> piece_list;

using piece_unique = std::unique_ptr <PieceState>;

using state_list = std::list<piece_unique>;

class GamePiece
{
public:
	GamePiece();
	GamePiece(VECTOR2 pos , PIECE_ST st);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset, PIECE_ST st);
	~GamePiece();

	void SetOldState(PIECE_ST st, int cnt);


	VECTOR2 GetPos() { return pos;}
	void SetPos(VECTOR2 pos){ this->pos = pos;}

	VECTOR2 GetDrawOffset(){ return drawOffset;}
	bool SetDrawOffset(VECTOR2 pos);
	void SetOldState(PIECE_ST st);
	// stateをセットする
	void SetState(PIECE_ST st);
	// 現在のstateを返す
	PIECE_ST GetState();
	void SetReverse(int num);
	// falseが返ったらピースを削除する
	bool Update();
	// タイマーが0になった時にpiece_listからこのピースを削除する
	bool ReverseStandby();


	// 駒を裏返す
	void SetWait(int i) { this->wait = i;}
	void SetAnimF(int i) { this->animF = i;}
	void Draw();
private:
	void Init();

	state_list state;
	// 盤面上の座標
	state_list old_state;
	// 反転前のピース情報
	VECTOR2 pos;
	// 描画用のずらす値
	VECTOR2 drawOffset;


	// アニメーション制御フレーム用
	int animF;
	int wait;
	// 反転する順番
	int rev_Num;
	// 反転時間フレーム用
	int rev_F;
	// ピースを削除する為のタイマー
	int clearTimer;
};

