#pragma once

class GameBoard;

#include <list>
#include <memory>
#include <mutex>

class GameTask
{
public:
	static void Create();
	static void Destroy();
	static GameTask *GetInstance()
	{
		// mutex call_once ��x�����Ă�
		std::call_once(initFlag, Create);
		Create();
		return s_Instance;
	};
	void Run();
	// �Ԃ�l 0b0001:���{�^��,0b0010:�E�{�^��,0b0100:���{�^��
	int GetMouse();

private:
	GameTask();
	~GameTask();
	void Init();
	void Title();
	void GameMain();

	void CreateNewBoard();
	static std::once_flag initFlag;
	static GameTask *s_Instance;

	GameBoard* Board;
	void (GameTask::*CurrentScene)();

	int mouseFlg;
	int mouseOld;
};


