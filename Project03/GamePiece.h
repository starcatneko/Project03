#pragma once
#include "VECTOR2.h"

enum PIECE_ST;

class GamePiece
{
public:
	GamePiece();
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset, PIECE_ST st);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset);
	GamePiece(VECTOR2 pos , PIECE_ST st);
	~GamePiece();
	VECTOR2 GetPos();
	// state���Z�b�g����
	void SetState(PIECE_ST st);
	// ���݂�state��Ԃ�
	PIECE_ST GetState();
	// ��𗠕Ԃ�
	void Revarse();
	void Draw();
private:

	VECTOR2 pos;
	// �`��p�̂��炷�l
	VECTOR2 drawOffset;
	PIECE_ST state;

};

