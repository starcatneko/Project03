#pragma once

#include "VECTOR2.h"

#include <vector>
#include <list>
#include <memory>
#include "PieceState.h"

class PieceTray;
class Player
{
public:
	Player();
	~Player();
	void Update();
	void SetTray();
	int GetNo();
	void SelectTray(VECTOR2 pos);
	PIECE_ST GetType();
	void DeleteTrayPiece();

	// �^�[���؂�ւ����̏ꍇtrue��Ԃ�
	bool CheckChangeTurn();

	// �v���C���[�̃^�[������
	void TurnAct();
	bool SetTunrFlg(bool flg);
	//���݃v���C���[�̃^�[����
	bool GetTunrFlg();
	int GetScore();	
	void ChangePlSet();
	
	void SetTurnTimer(int time);
	int GetTurnTimer();
private:
	int playerNo;
	static int playercnt;
	std::unique_ptr <PieceTray> pieceTray;
	
	// �u����ꏊ���X�g
	std::list<VECTOR2> itr;

	PIECE_ST piecetype;
	bool turnFlg;

	// �v���C���[��؂�ւ���t���O�^�C�}�[
	int ChangeTimer;


};

