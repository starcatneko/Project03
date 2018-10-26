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


typedef std::weak_ptr<GamePiece> piece_shared_w;

typedef std::shared_ptr<GamePiece> piece_shared;

typedef std::list<piece_shared> piece_list;

using piece_unique = std::unique_ptr <PieceState>;

using state_list = std::list<piece_unique>;


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

