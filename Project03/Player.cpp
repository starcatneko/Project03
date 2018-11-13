#include "Player.h"
#include "GameBoard.h"
#include "PieceTray.h"
#include "GameTask.h"
#include "MouseCtr.h"


int Player::playercnt = 0;

Player::Player()
{
	this->playerNo = playercnt++;
	this->piecetype = PIECE_ST(this->playerNo + 1);
	this->pieceTray = std::make_unique<PieceTray>(this->piecetype);
	//this->SetTray();
}



Player::~Player()
{
	playercnt--;
}

void Player::Update()
{
	pieceTray->DrawTray({ (playerNo != 1 ? 11 * 64 : 0), 0});
}

void Player::SetTray()
{
	this->pieceTray = std::make_unique<PieceTray>(this->piecetype);
}

int Player::GetNo()
{
	return playerNo;
}



bool Player::Draw()
{
	if (pieceTray)
	{
		//pieceTray->DrawTray();
		return true;
	}
	//DrawFormatString(playerNo * 64, 420, 0xeeeeee, "num%d", );
	return false;
}

void Player::SelectTray(VECTOR2 pos)
{
	pieceTray->SelectTrayPiece(pos);
}


PIECE_ST Player::GetType()
{
	return piecetype;
}

void Player::DeleteTrayPiece()
{
	pieceTray->TrayUpdate();
}

void Player::TurnAct()
{
	pieceTray->SetTurnFlg(true);

	// TurnAct�̃s�[�X���ݒu��if��
	// �s�[�X��ݒu������v���C���[���؂�ւ�邩��
	
	if ((lpGameTask.Mouse->GetButton() & 0b0001) != 0)
	{
		lpGameTask.Board->SetPiece(lpGameTask.Mouse->GetPos());
	}
	


	//�s�[�X�̐����`�F�b�N
	//�}�E�X�擾{
	//�ݒu�\�Ȃ�ݒu
	//	{
	//
	//	}
	//}
}

bool Player::SetTunrFlg(bool flg)
{
	 return pieceTray->SetTurnFlg(flg);
}

bool Player::GetTunrFlg()
{
	return pieceTray->GetTurnFlg();

}

int Player::GetScore()
{
	return pieceTray->GetScore();
}

/*Player��public��
�����o�֐�void�^��SetTurnFlg
�����

Player��SetTurnFlg���̏�����
pieceTray->SetTurnFlg(����);


*/