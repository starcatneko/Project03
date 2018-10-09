#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <memory>

#include "PieceState.h";
class GameBoard;
class Player;

class GamePiece
{
public:
	GamePiece();
	GamePiece(VECTOR2 pos , PIECE_ST st);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset, PIECE_ST st);
	~GamePiece();
	VECTOR2 GetPos();
	// state���Z�b�g����
	void SetState(PIECE_ST st);
	// ���݂�state��Ԃ�
	PIECE_ST GetState();
	// ��𗠕Ԃ�
	void Revarse(PIECE_ST st);
	int ColorSet();
	void Draw();
	void SetWait(int i);
	void SetAnimF(int i);
private:
	std::unique_ptr <PieceState> state;
	// �Ֆʏ�̍��W
	VECTOR2 pos;
	// �`��p�̂��炷�l
	VECTOR2 drawOffset;
	// �A�j���[�V��������t���[���p
	int animF;
	int wait;
};

