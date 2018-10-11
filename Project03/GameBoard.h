#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <array>
#include <memory>


#include "GamePiece.h"
//class GamePiece;
class Player;
class MouseCtr;

enum PIECE_ST;


typedef std::shared_ptr<Player> player_ptr;

typedef std::list<player_ptr> player_list;

typedef std::weak_ptr<GamePiece> piece_ptr_w;



class GameBoard
{
public:
	GameBoard();
	GameBoard(int size);
	GameBoard(VECTOR2 size);
	~GameBoard();
	bool Init();
	// �w�肵���ʒu�ɐ΂�z�u
	void SetPiece(VECTOR2 pos);
	void SetPiece(VECTOR2 pos, PIECE_ST st);

	void DB_TouchBoad();
	void Update();
	// �Q�[���Z�b�g������
	void GameEnd();
	void Draw();
	// flg��true�̕����ɐ΂�u��
	bool Reverse(VECTOR2 pos, VECTOR2 vec);

	// vec:���K�����ꂽ�����x�N�g��
	bool SarchReverse(VECTOR2 pos, VECTOR2 vec, PIECE_ST st);

	void AddPlayer();
	// �v���C�^�[���̃v���C���[���X�V
	void CurrentPlayerChange();
	player_ptr GetCurrentPlayer();


	// �}�E�X���W���{�[�h���W�Ԋ�
	VECTOR2 Pos_MouseToBoard(VECTOR2 mousePos);
	// �{�[�h���W���}�E�X���W�Ԋ�
	VECTOR2 Pos_BoardToMouse(VECTOR2 BoardPos);
	//

	//------�f�o�b�O�p�֐�-----
	void Debug_SetPiece(VECTOR2 pos);

	bool gameEndFlg;

private:
	piece_ptr AddObjList(piece_ptr&& objPtr);
	void CurrentSetUpData();
	//auto AddObjList(piece_ptr&& objPtr);
	//
	// �Ֆʂ̃T�C�Y��ݒ肷��֐�
	bool Resize(VECTOR2 size);
	// ���u�����ꏊ�����ɔ����𔽓]�����鏈��
	void ChangeStone(VECTOR2 pos);



	VECTOR2 boardSize;
	std::vector<std::vector<PIECE_ST>> board;
	std::vector<int> vect;
	//std::list<Player> playerList;

	// �񎟉~�z��p�̃|�C���^
	std::vector <piece_ptr_w*> data;
	std::vector <piece_ptr_w> BaseData;

	// ���݂̃v���C���[�\���p
	std::unique_ptr <GamePiece> CurrentPlPiece;
	
	//
	player_list playerlist;
	// iterator ���ݍs�����̃v���C���[
	player_list::iterator currentPlayer;
	// ���ݑI�����Ă���v���C���[�̃A�h���X���i�[����
	
	//player_ptr currentPlayer;
		
	// �Ō�ɋ��u�����v���C���[
	int lastset;		
	// ���������v���C���[
	int winplayer;

	piece_list piecelist;
	VECTOR2 size;

	std::array <int,0b1111 + 1> hitDir;

};

