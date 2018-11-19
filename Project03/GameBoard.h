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

//class Player;

//enum PIECE_ST;

typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_list;
typedef std::shared_ptr<GameBoard> Board_ptr;

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
	void SetPiece(VECTOR2 pos);
	void SetPiece(VECTOR2 pos, PIECE_ST st);

	void DB_TouchBoad();
	void Update();
	// ゲームセット時処理
	void GameEnd();

	// 基本的に駒の描画
	void DrawPiece();
	// 纏めて描画
	void Draw();
	// flgがtrueの方向に石を置く
	// Result用描画 とりあえず
	void ResultDraw(); 
	bool Reverse(VECTOR2 pos, VECTOR2 vec);

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
	int PieceCount(PIECE_ST olor);
	VECTOR2 SetListSerch(PIECE_ST type);
private:
	piece_shared AddObjList(piece_shared&& objPtr);
	void CurrentSetUpData();

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
	// 勝利したプレイヤー
	int winplayer;

	// 設置座標可能リスト
	std::array<std::list<VECTOR2>,static_cast<int>(PIECE_ST::MAX)> setlist;

	piece_list piecelist;
	VECTOR2 size;
	std::array<int, PL_MAX> TotalPiece;



	int timer;

};


