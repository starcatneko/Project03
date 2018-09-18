#pragma once
#include "Geometry.h"
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <memory>

class GamePiece;
class Player;


typedef std::shared_ptr<GamePiece> piece_ptr;
typedef std::shared_ptr<Player> player_ptr;

typedef std::list<piece_ptr> piece_list;
typedef std::list<player_ptr> player_list;

typedef std::weak_ptr<GamePiece> piece_ptr_w;


//�@�}�X�ɒu����Ă����
enum PIECE_ST
{
	PIECE_NON,
	PIECE_W,
	PIECE_B,
	PIECE_RED,
	PIECE_BLU,
	PIECE_GRN,
	PIECE_YLW,
	PIECE_PPL,
	PIECE_CYN,
	PIECE_MAX
};
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
	void DB_TouchBoad();
	void Update();
	void Draw();
	void SarchReverse(VECTOR2 pos);
	void AddPlayer(int number);
	// �v���C�^�[���̃v���C���[���X�V
	void CurrentPlayerChange();

	player_ptr GetCurrentPlayer();
	//
private:
	piece_ptr AddObjList(piece_ptr&& objPtr);
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
	
	//
	player_list playerlist;
	// iterator ���ݍs�����̃v���C���[
	player_list::iterator currentPlayer;
	// ���ݑI�����Ă���v���C���[�̃A�h���X���i�[����
	//player_ptr currentPlayer;

	piece_list piecelist;
	VECTOR2 size;

	
};

