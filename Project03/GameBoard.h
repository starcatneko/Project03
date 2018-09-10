#pragma once
#include "Geometry.h"
#include "VECTOR2.h"
#include <vector>
#include <list>

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
	void SetBoardSize(VECTOR2 size);
	// 指定した位置に石を配置
	void SetStone(VECTOR2 pos);
	void DB_TouchBoad();
	void Update();
	void Draw();
	//
private:
	//
	VECTOR2 boardSize;
	void DrawBoardGrid();
	std::vector<std::vector<PIECE_ST>> board;

	// 二次円配列用のポインタ
	std::vector < PIECE_ST*> data;
	std::vector < PIECE_ST> BaseData;
	VECTOR2 size;
};

