#pragma once
// State�f�U�C��
// ���̉��͂����Ȃ�

//�@�}�X�ɒu����Ă����
enum PIECE_ST
{
	PIECE_NON,
	PIECE_B,
	PIECE_W,
	PIECE_RED,
	PIECE_BLU,
	PIECE_GRN,
	PIECE_YLW,
	PIECE_PPL,
	PIECE_CYN,
	PIECE_MAX
};


class PieceState
{
public:
	virtual ~PieceState();
	virtual PIECE_ST GetState() = 0;
	virtual unsigned int GetDrawColor() = 0;
	/*
	virtual int GetHp() = 0;
	virtual int SkillNumber() = 0;
	*/
	//virtual int Image() = 0;
	
protected:
};

