#pragma once
#include "Geometry.h"
#include "VECTOR2.h"
#include <vector>
#include <list>

class GamePiece;
/*
	可変サイズの盤面

	任意のマスをクリックしたらenumのステートが変化するようにする

*/

//　マスに置かれている石
enum PIECE_ST
{
	PIECE_NON,
	PIECE_W,
	PIECE_B,
	PIECE_MAX
};
class GameBoard
{
public:
	GameBoard();
	GameBoard(int size);
	GameBoard(VECTOR2 size);
	~GameBoard();
	// 指定した位置に石を配置
	void SetStone(VECTOR2 pos);
	void DB_TouchBoad();
	void Update();
	void Draw();
	//
private:
	//
	// 盤面のサイズを設定する関数
	bool Resize(VECTOR2 size);
	// 駒を置いた場所を軸に白黒を反転させる処理
	void ChangeStone(VECTOR2 pos);

	VECTOR2 boardSize;
	std::vector<std::vector<PIECE_ST>> board;

	// 二次円配列用のポインタ
	std::vector < PIECE_ST*> data;
	std::vector < PIECE_ST> BaseData;

	std::list<GamePiece> piecelist;
	VECTOR2 size;
};

