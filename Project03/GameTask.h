#pragma once

class GameBoard;
class MouseCtr;

#include <list>
#include <vector>
#include <array>
#include <memory>

#include "VECTOR2.h"

class GamePiece;
class Player;
class GameState;



typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_list;


#define lpGameTask GameTask::GetInstance()

// �v���C���[�l��
#define PL_MAX 2

#define SETWAIT(int) (GameTask::GetInstance().SetWait(int))
#define ADDWAIT(int) (GameTask::GetInstance().AddWait(int))
#define GETWAIT() (GameTask::GetInstance().GetWait())
class GameTask
{
public:
	static GameTask &GetInstance()
	{
		return *s_Instance;
	};
	// �Ԃ�l 0b0001:���{�^��,0b0010:�E�{�^��,0b0100:���{�^��

	void Run();
	void SetWait(int wait);
	void AddWait(int wait);
	int GetWait();

	VECTOR2 GetBoardSize();

	void CurrentPlayerChange();


	void GameEnd();


	// iterator ���ݍs�����̃v���C���[
	player_list playerlist;

	player_list::iterator currentPlayer;
	// ���ݑI�����Ă���v���C���[�̃A�h���X���i�[����

	state_ptr state;
	std::unique_ptr<MouseCtr> Mouse; 
	Board_ptr Board;




private:

	struct GameTaskDeleter
	{
		void operator ()(GameTask* GameTask) const
		{
			delete GameTask;
		}
	};

	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;

	GameTask();
	~GameTask();
	void Init();
	void Title();
	//const MouseCtr * MouseCtr;
	void CreateNewBoard();

	void AddPlayer();

	//bool SetState(state_ptr st);

	// ���j�[�N�|�C���^
	//std::shared_ptr<GameBoard> Board;


	void (GameTask::*CurrentScene)();
	void (GameState::*Scene)();
	
	// �E�F�C�g�t���[����
	int wait;


	int mouseFlg;
	int mouseOld;
};


