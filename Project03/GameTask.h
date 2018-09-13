#pragma once

class GameBoard;
class MouseCtr;

#include <list>
#include <memory>
//#include <

class GameTask
{
public:
	static GameTask &GetInstance()
	{
		return *s_Instance;
	};
	void Run();
	// 返り値 0b0001:左ボタン,0b0010:右ボタン,0b0100:中ボタン
	void UpDate(const MouseCtr& mouseCtr);

private:
	struct GameTaskDeleter
	{
		void operator ()(GameTask* gameTask) const
		{
			delete gameTask;
		}
	};
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;

	GameTask();
	~GameTask();
	void Init();
	void Title();
	void GameMain();

	void CreateNewBoard();

	// ユニークポインタ
	std::unique_ptr<GameBoard> Board;
	std::unique_ptr<MouseCtr> Mouse;

	void (GameTask::*CurrentScene)();

	int mouseFlg;
	int mouseOld;
};


