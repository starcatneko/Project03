#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <memory>

#include "PieceState.h"

class GameBoard;
class Player;
class GamePiece;

//enum PIECE_ST;


typedef std::shared_ptr<GamePiece> piece_ptr;

typedef std::list<piece_ptr> piece_list;

typedef std::list<std::unique_ptr <PieceState>> state_list;


class GamePiece
{
public:
	GamePiece();
	GamePiece(VECTOR2 pos , PIECE_ST st);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset);
	GamePiece(VECTOR2 pos, VECTOR2 drawOffset, PIECE_ST st);
	~GamePiece();

	VECTOR2 GetPos();
	bool SetPos(VECTOR2 pos);
	VECTOR2 GetDrawOffset();
	bool SetDrawOffset(VECTOR2 pos);
	// state���Z�b�g����
	void SetState(PIECE_ST st);
	// ���݂�state��Ԃ�
	PIECE_ST GetState();
	// ��𗠕Ԃ�
	void Draw();
	void SetWait(int i);
	void SetAnimF(int i);
private:
	state_list state;
	// �Ֆʏ�̍��W
	VECTOR2 pos;
	// �`��p�̂��炷�l
	VECTOR2 drawOffset;
	// �A�j���[�V��������t���[���p
	int animF;
	int wait;
};

