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
	// 返り値 0b0001:左ボタン,0b0010:右ボタン,0b0100:中ボタン

	void Run();
	void SetWait(int wait);
	void AddWait(int wait);
	int GetWait();


	void GameEnd();


	// iterator 現在行動中のプレイヤー
	player_list playerlist;

	player_list::iterator currentPlayer;
	// 現在選択しているプレイヤーのアドレスを格納する

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

	// ユニークポインタ
	std::unique_ptr<GameBoard> Board;
	std::unique_ptr<MouseCtr> Mouse;

	void (GameTask::*CurrentScene)();
	
	// ウェイトフレーム数
	int wait;


	int mouseFlg;
	int mouseOld;
};


