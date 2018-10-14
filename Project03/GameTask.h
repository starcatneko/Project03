#pragma once

class GameBoard;
class MouseCtr;

#include <list>
#include <vector>
#include <array>
#include <memory>

#include "VECTOR2.h"

class Player;


typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_list;


#define lpGameTask GameTask::GetInstance()

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


	void GameEnd();


	// iterator ���ݍs�����̃v���C���[
	player_list playerlist;

	player_list::iterator currentPlayer;
	// ���ݑI�����Ă���v���C���[�̃A�h���X���i�[����

	VECTOR2 GetBoardSize();

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
	void GameMain();
	void Result();

	void CreateNewBoard();

	void AddPlayer();

	// ���j�[�N�|�C���^
	std::unique_ptr<GameBoard> Board;
	std::unique_ptr<MouseCtr> Mouse;

	void (GameTask::*CurrentScene)();
	
	// �E�F�C�g�t���[����
	int wait;


	int mouseFlg;
	int mouseOld;
};


