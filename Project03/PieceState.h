#pragma once
// State�f�U�C��
// ���̉��͂����Ȃ�
//�@�}�X�ɒu����Ă����

#include "PIECE_ST.h"

class PieceState
{
public:
	virtual ~PieceState();
	virtual PIECE_ST GetState() = 0;
	virtual unsigned int GetDrawColor() = 0;

protected:
};

