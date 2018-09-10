#pragma once
#include "Geometry.h"
#include "VECTOR2.h"
#include <vector>
#include <list>

/*
	�σT�C�Y�̔Ֆ�

	�C�ӂ̃}�X���N���b�N������enum�̃X�e�[�g���ω�����悤�ɂ���

*/

//�@�}�X�ɒu����Ă����
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
	// �w�肵���ʒu�ɐ΂�z�u
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

	// �񎟉~�z��p�̃|�C���^
	std::vector < PIECE_ST*> data;
	std::vector < PIECE_ST> BaseData;
	VECTOR2 size;
};

