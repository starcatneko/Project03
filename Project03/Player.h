#pragma once

#include "VECTOR2.h"

#include <vector>
#include <list>
#include <memory>
#include "PieceState.h"

class PieceTray;
class Player
{
public:
	Player();
	~Player();
	void Update();
	void SetTray();
	int GetNo();
	bool Draw();
	void SelectTray(VECTOR2 pos);
	PIECE_ST GetType();
	void DeleteTrayPiece();

	// プレイヤーのターン処理
	void TurnAct();
	bool SetTunrFlg(bool flg);
	//現在プレイヤーのターンか
	bool GetTunrFlg();
	int GetScore();	
	
	void SetTurnTimer(int time);
	int GetTurnTimer();
private:
	int playerNo;
	static int playercnt;
	std::unique_ptr <PieceTray> pieceTray;
	
	// 置ける場所リスト
	std::list<VECTOR2> itr;

	PIECE_ST piecetype;
	bool turnFlg;

	// プレイヤーを切り替えるフラグタイマー
	int ChangeTimer;
};

