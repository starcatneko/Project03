#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <array>
#include <memory>
#include "GamePiece.h"
#include "Player.h"

class GamePiece;
class MouseCtr;

#define PL_MAX (2)
#define REVERSE_TIME (8)		// 駒反転のフレーム数
#define TURN_CHANGE_WAIT (24)	// ターン更新時ウェイト

//class Player;

//enum PIECE_ST;

typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_list;
typedef std::shared_ptr<GameBoard> Board_ptr;
typedef std::shared_ptr<std::list<VECTOR2>> VECTOR2_list;


#define BoardSize int(8)

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600
#define SCREEN_HALF_X SCREEN_SIZE_X/2
#define SCREEN_HALF_Y SCREEN_SIZE_Y/2
#define X_DIS (int)((SCREEN_SIZE_X / 2) - (boardSize.x / 2)*CHIPSIZE)
#define Y_DIS (int)((SCREEN_SIZE_Y / 2) - (boardSize.y / 2)*CHIPSIZE)


class GameBoard
{
public:
	GameBoard();
	GameBoard(int size);
	GameBoard(VECTOR2 size);
	~GameBoard();
	bool Init();
	// 指定した位置に石を配置
	bool SetPiece(VECTOR2 pos);
	void SetPiece(VECTOR2 pos, PIECE_ST st);

	// data[pos.y][pos.x].expiredをする。範囲外参照を回避する。
	bool CheckExpired(VECTOR2 pos);

	void DB_TouchBoad();
	void Update();
	// ゲームセット時処理
	void GameEnd();

	// 基本的に駒の描画
	void DrawPiece();
	void DrawBoard();

	// 纏めて描画
	void Draw();
	// Result用描画 とりあえず
	void ResultDraw(); 
	bool Reverse(VECTOR2 pos, VECTOR2 vec);

	// checkPosがBoardのサイズをはみ出していなければtrueを返す
	bool CheckOverBoard(VECTOR2 checkPos);

	// vec:正規化された方向ベクトル
	bool SarchReverse(VECTOR2 pos, VECTOR2 vec, PIECE_ST st);


	// マウス座標→ボード座標返還
	VECTOR2 Pos_MouseToBoard(VECTOR2 mousePos);
	// ボード座標→マウス座標返還
	VECTOR2 Pos_BoardToMouse(VECTOR2 BoardPos);
	//

	//------デバッグ用関数-----
	void Debug_SetPiece(VECTOR2 pos);

	bool gameEndFlg;

	VECTOR2 GetBoardSize();

	// Result表示用にピースを配置する
	void PieceResultSet();
	// 指定された色のピースの数を返す
	int PieceCount(PIECE_ST color);
	// リザルト開始時に呼び出す
	void ResultInit();
	// setlist(置けるマスのリスト)からランダムで座標を抽出する
	// 検索に失敗した場合 {-1,-1}を返す
	VECTOR2 SetlistSerch();	

	// 置ける場所リストを更新する
	// ターンにつき一回の呼び出し
	void SetlistUpdata();

private:
	piece_shared AddObjList(piece_shared&& objPtr);

	//auto AddObjList(piece_shared&& objPtr);
	//
	// 盤面のサイズを設定する関数
	bool Resize(VECTOR2 size);

	VECTOR2 boardSize;
	std::vector<std::vector<PIECE_ST>> board;
	std::vector<int> vect;
	//std::list<Player> playerList;

	// 二次円配列用のポインタ
	std::vector <piece_shared_w*> data;
	std::vector <piece_shared_w> BaseData;

	// 現在のプレイヤー表示用
	std::unique_ptr <GamePiece> CurrentPlPiece;
	
	//player_ptr 
	
	;
		
	// 最後に駒を置いたプレイヤー
	int lastset;
	// 最後に駒が置かれた位置
	VECTOR2 lastsetPos;
	// 勝利したプレイヤー
	int winplayer;

	// 設置可能座標リスト
	std::list<VECTOR2> setlist;
	piece_list piecelist;
	VECTOR2 size;
	std::array<int, PL_MAX> TotalPiece;

	//std::array<VECTOR2_list, static_cast<int>(PIECE_ST::MAX)>itr;
	//std::array<std::list<VECTOR2>,static_cast<int>(PIECE_ST::MAX)> itr;

	int timer;

};


