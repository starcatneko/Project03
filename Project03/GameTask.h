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

class OPRT_State;
class GamePiece;
class Player;
typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_list;


//		
#define lpGameTask GameTask::GetInstance()
// 現在のプレイヤー		
#define lpCurrentPlayer (*lpGameTask.currentPlayer)
//		

// プレイヤー人数
#define PL_MAX (2)

class GameTask
{
public:
	static GameTask &GetInstance()
	{
		return *s_Instance;
	};

	void Run();

	VECTOR2 GetBoardSize();
	// iterator 現在行動中のプレイヤー
	player_list playerlist;
	player_list::iterator currentPlayer;
	// 現在選択しているプレイヤーのアドレスを格納する

	state_ptr state;
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

	int mouseFlg;
	int mouseOld;
		
	//std::array<OPRT_TYPE,static_cast<int>(OPRT_TYPE::MAX)> oprt_tbl;
	// プレイヤー毎のOPRT_TYPE;
	// プレイヤー操作(OPRT_TYPE::MAN)は明示的に設定する
	//std::vector<OPRT_State> oprt_tbl_s;
};


