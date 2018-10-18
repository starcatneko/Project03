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

// プレイヤー人数
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
	// 返り値 0b0001:左ボタン,0b0010:右ボタン,0b0100:中ボタン

	void Run();
	void SetWait(int wait);
	void AddWait(int wait);
	int GetWait();

	VECTOR2 GetBoardSize();

	void CurrentPlayerChange();


	void GameEnd();


	// iterator 現在行動中のプレイヤー
	player_list playerlist;

	player_list::iterator currentPlayer;
	// 現在選択しているプレイヤーのアドレスを格納する

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

	// ユニークポインタ
	//std::shared_ptr<GameBoard> Board;


	void (GameTask::*CurrentScene)();
	void (GameState::*Scene)();
	
	// ウェイトフレーム数
	int wait;


	int mouseFlg;
	int mouseOld;
};


