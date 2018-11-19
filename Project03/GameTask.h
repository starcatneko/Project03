#pragma once

class MouseCtr;

#include <list>
#include <vector>
#include <array>
#include <memory>
#include "VECTOR2.h"
#include "GameState.h"
#include "GameBoard.h"
#include "MouseCtr.h"


class GamePiece;
class Player;
typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_list;


#define lpGameTask GameTask::GetInstance()
#define lpMouse lpGameTask.Mouse

// �v���C���[�l��
#define PL_MAX (2)

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
	// iterator ���ݍs�����̃v���C���[
	player_list playerlist;


	player_list::iterator currentPlayer;
	// ���ݑI�����Ă���v���C���[�̃A�h���X���i�[����

	state_ptr state;
	std::vector<std::shared_ptr<MouseCtr>> Mouse;

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

	void (GameTask::*CurrentScene)();
	void (GameState::*Scene)();
	
	// �E�F�C�g�t���[����
	int wait;

	int mouseFlg;
	int mouseOld;
	
	
	//std::array<OPRT_TYPE,static_cast<int>(OPRT_TYPE::MAX)> oprt_tbl;
	// �v���C���[����OPRT_TYPE;
	// �v���C���[����(OPRT_TYPE::MAN)�͖����I�ɐݒ肷��
	std::vector<OPRT_TYPE> oprt_tbl;
	std::vector<OPRT_State> oprt_tbl_s;
};


