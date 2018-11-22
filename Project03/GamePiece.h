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

	void SetOldState(PIECE_ST st, int cnt);


	VECTOR2 GetPos() { return pos;}
	void SetPos(VECTOR2 pos){ this->pos = pos;}

	VECTOR2 GetDrawOffset(){ return drawOffset;}
	bool SetDrawOffset(VECTOR2 pos);
	void SetOldState(PIECE_ST st);
	// state���Z�b�g����
	void SetState(PIECE_ST st);
	// ���݂�state��Ԃ�
	PIECE_ST GetState();
	void SetReverse(int num);
	// false���Ԃ�����s�[�X���폜����
	bool Update();
	// �^�C�}�[��0�ɂȂ�������piece_list���炱�̃s�[�X���폜����
	bool ReverseStandby();


	// ��𗠕Ԃ�
	void SetWait(int i) { this->wait = i;}
	void SetAnimF(int i) { this->animF = i;}
	void Draw();
private:
	void Init();

	state_list state;
	// �Ֆʏ�̍��W
	state_list old_state;
	// ���]�O�̃s�[�X���
	VECTOR2 pos;
	// �`��p�̂��炷�l
	VECTOR2 drawOffset;


	// �A�j���[�V��������t���[���p
	int animF;
	int wait;
	// ���]���鏇��
	int rev_Num;
	// ���]���ԃt���[���p
	int rev_F;
	// �s�[�X���폜����ׂ̃^�C�}�[
	int clearTimer;
};

