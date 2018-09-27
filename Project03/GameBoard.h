#pragma once
#include "Geometry.h"
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <array>
#include <memory>

class GamePiece;
class Player;


typedef std::shared_ptr<GamePiece> piece_ptr;
typedef std::shared_ptr<Player> player_ptr;

typedef std::list<piece_ptr> piece_list;
typedef std::list<player_ptr> player_list;

typedef std::weak_ptr<GamePiece> piece_ptr_w;


//　マスに置かれている石
enum PIECE_ST
{
	PIECE_NON,
	PIECE_W,
	PIECE_B,
	PIECE_RED,
	PIECE_BLU,
	PIECE_GRN,
	PIECE_YLW,
	PIECE_PPL,
	PIECE_CYN,
	PIECE_MAX
};
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
	void DB_TouchBoad();
	void Update();
	void Draw();
	// flgがtrueの方向に石を置く
	bool Reverse(std::array <int, 0b1111+1> flg);

	bool SarchReverse(VECTOR2 pos);
	void AddPlayer(int number);
	// プレイターンのプレイヤーを更新
	void CurrentPlayerChange();

	player_ptr GetCurrentPlayer();
	//
private:
	piece_ptr AddObjList(piece_ptr&& objPtr);
	//auto AddObjList(piece_ptr&& objPtr);
	//
	// 盤面のサイズを設定する関数
	bool Resize(VECTOR2 size);
	// 駒を置いた場所を軸に白黒を反転させる処理
	void ChangeStone(VECTOR2 pos);

	void SetPiece(VECTOR2 pos, PIECE_ST st);

	VECTOR2 boardSize;
	std::vector<std::vector<PIECE_ST>> board;
	std::vector<int> vect;
	//std::list<Player> playerList;

	// 二次円配列用のポインタ
	std::vector <piece_ptr_w*> data;
	std::vector <piece_ptr_w> BaseData;
	
	//
	player_list playerlist;
	// iterator 現在行動中のプレイヤー
	player_list::iterator currentPlayer;
	// 現在選択しているプレイヤーのアドレスを格納する
	//player_ptr currentPlayer;

	piece_list piecelist;
	VECTOR2 size;

	std::array <int,0b1111 + 1> hitDir;
};

