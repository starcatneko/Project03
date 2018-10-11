#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <array>
#include <memory>


#include "GamePiece.h"
//class GamePiece;
class Player;
class MouseCtr;

enum PIECE_ST;


typedef std::shared_ptr<Player> player_ptr;

typedef std::list<player_ptr> player_list;

typedef std::weak_ptr<GamePiece> piece_ptr_w;



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
	void Draw();
	// flgがtrueの方向に石を置く
	bool Reverse(VECTOR2 pos, VECTOR2 vec);

	// vec:正規化された方向ベクトル
	bool SarchReverse(VECTOR2 pos, VECTOR2 vec, PIECE_ST st);

	void AddPlayer();
	// プレイターンのプレイヤーを更新
	void CurrentPlayerChange();
	player_ptr GetCurrentPlayer();


	// マウス座標→ボード座標返還
	VECTOR2 Pos_MouseToBoard(VECTOR2 mousePos);
	// ボード座標→マウス座標返還
	VECTOR2 Pos_BoardToMouse(VECTOR2 BoardPos);
	//

	//------デバッグ用関数-----
	void Debug_SetPiece(VECTOR2 pos);

	bool gameEndFlg;

private:
	piece_ptr AddObjList(piece_ptr&& objPtr);
	void CurrentSetUpData();
	//auto AddObjList(piece_ptr&& objPtr);
	//
	// 盤面のサイズを設定する関数
	bool Resize(VECTOR2 size);
	// 駒を置いた場所を軸に白黒を反転させる処理
	void ChangeStone(VECTOR2 pos);



	VECTOR2 boardSize;
	std::vector<std::vector<PIECE_ST>> board;
	std::vector<int> vect;
	//std::list<Player> playerList;

	// 二次円配列用のポインタ
	std::vector <piece_ptr_w*> data;
	std::vector <piece_ptr_w> BaseData;

	// 現在のプレイヤー表示用
	std::unique_ptr <GamePiece> CurrentPlPiece;
	
	//
	player_list playerlist;
	// iterator 現在行動中のプレイヤー
	player_list::iterator currentPlayer;
	// 現在選択しているプレイヤーのアドレスを格納する
	
	//player_ptr currentPlayer;
		
	// 最後に駒を置いたプレイヤー
	int lastset;		
	// 勝利したプレイヤー
	int winplayer;

	piece_list piecelist;
	VECTOR2 size;

	std::array <int,0b1111 + 1> hitDir;

};

