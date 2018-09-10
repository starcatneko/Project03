#pragma once
#include "Geometry.h"
#include "VECTOR2.h"
#include <vector>
#include <list>

class GamePiece;
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
	// �w�肵���ʒu�ɐ΂�z�u
	void SetStone(VECTOR2 pos);
	void DB_TouchBoad();
	void Update();
	void Draw();
	//
private:
	//
	// �Ֆʂ̃T�C�Y��ݒ肷��֐�
	bool Resize(VECTOR2 size);
	// ���u�����ꏊ�����ɔ����𔽓]�����鏈��
	void ChangeStone(VECTOR2 pos);

	VECTOR2 boardSize;
	std::vector<std::vector<PIECE_ST>> board;

	// �񎟉~�z��p�̃|�C���^
	std::vector < PIECE_ST*> data;
	std::vector < PIECE_ST> BaseData;

	std::list<GamePiece> piecelist;
	VECTOR2 size;
};

