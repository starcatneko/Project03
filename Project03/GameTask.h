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
		// mutex call_once ��x�����Ă�
		std::call_once(initFlag, Create);
		Create();
		return s_Instance;
	};
	void Run();
	// �Ԃ�l 0b0001:���{�^��,0b0010:�E�{�^��,0b0100:���{�^��
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

	// ���j�[�N�|�C���^
	std::unique_ptr<GameBoard> Board;
	std::unique_ptr<MouseCtr> Mouse;

	void (GameTask::*CurrentScene)();

	int mouseFlg;
	int mouseOld;
};


