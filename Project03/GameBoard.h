#pragma once
#include "VECTOR2.h"
#include <vector>
#include <list>
#include <array>
#include <memory>
#include "GamePiece.h"
#include "Player.h"

class GamePiece;
class MouseCtr;

#define PL_MAX (2)
#define REVERSE_TIME (8)		// ��]�̃t���[����

//class Player;

//enum PIECE_ST;

typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_list;
typedef std::shared_ptr<GameBoard> Board_ptr;

#define BoardSize int(8)

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600
#define SCREEN_HALF_X SCREEN_SIZE_X/2
#define SCREEN_HALF_Y SCREEN_SIZE_Y/2
#define X_DIS (int)((SCREEN_SIZE_X / 2) - (boardSize.x / 2)*CHIPSIZE)
#define Y_DIS (int)((SCREEN_SIZE_Y / 2) - (boardSize.y / 2)*CHIPSIZE)


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

	// ��{�I�ɋ�̕`��
	void DrawPiece();
	// �Z�߂ĕ`��
	void Draw();
	// flg��true�̕����ɐ΂�u��
	// Result�p�`�� �Ƃ肠����
	void ResultDraw(); 
	bool Reverse(VECTOR2 pos, VECTOR2 vec);

	// vec:���K�����ꂽ�����x�N�g��
	bool SarchReverse(VECTOR2 pos, VECTOR2 vec, PIECE_ST st);


	// �}�E�X���W���{�[�h���W�Ԋ�
	VECTOR2 Pos_MouseToBoard(VECTOR2 mousePos);
	// �{�[�h���W���}�E�X���W�Ԋ�
	VECTOR2 Pos_BoardToMouse(VECTOR2 BoardPos);
	//

	//------�f�o�b�O�p�֐�-----
	void Debug_SetPiece(VECTOR2 pos);

	bool gameEndFlg;

	VECTOR2 GetBoardSize();

	// Result�\���p�Ƀs�[�X��z�u����
	void PieceResultSet();
	// �w�肳�ꂽ�F�̃s�[�X�̐���Ԃ�
	int PieceCount(PIECE_ST olor);
	VECTOR2 SetListSerch(PIECE_ST type);
private:
	piece_shared AddObjList(piece_shared&& objPtr);
	void CurrentSetUpData();

	//auto AddObjList(piece_shared&& objPtr);
	//
	// �Ֆʂ̃T�C�Y��ݒ肷��֐�
	bool Resize(VECTOR2 size);

	VECTOR2 boardSize;
	std::vector<std::vector<PIECE_ST>> board;
	std::vector<int> vect;
	//std::list<Player> playerList;

	// �񎟉~�z��p�̃|�C���^
	std::vector <piece_shared_w*> data;
	std::vector <piece_shared_w> BaseData;

	// ���݂̃v���C���[�\���p
	std::unique_ptr <GamePiece> CurrentPlPiece;
	
	//player_ptr 
	
	;
		
	// �Ō�ɋ��u�����v���C���[
	int lastset;		
	// ���������v���C���[
	int winplayer;

	// �ݒu���W�\���X�g
	std::array<std::list<VECTOR2>,static_cast<int>(PIECE_ST::MAX)> setlist;

	piece_list piecelist;
	VECTOR2 size;
	std::array<int, PL_MAX> TotalPiece;



	int timer;

};


