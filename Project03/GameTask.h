#pragma once

class GameBoard;
class MouseCtr;

#include <list>
#include <memory>
#include <mutex>
//#include <

class GameTask
{
public:
	static void Create();
	static void Destroy();
	static GameTask *GetInstance()
	{
		// mutex call_once 一度だけ呼ぶ
		std::call_once(initFlag, Create);
		Create();
		return s_Instance;
	};
	void Run();
	// 返り値 0b0001:左ボタン,0b0010:右ボタン,0b0100:中ボタン
	void UpDate(const MouseCtr& mouseCtr);

private:
	GameTask();
	~GameTask();
	void Init();
	void Title();
	void GameMain();

	void CreateNewBoard();
	static std::once_flag initFlag;
	static std::unique_ptr<GameTask> s_Instance;

	// ユニークポインタ
	std::unique_ptr<GameBoard> Board;
	std::unique_ptr<MouseCtr> Mouse;

	void (GameTask::*CurrentScene)();

	int mouseFlg;
	int mouseOld;
};


