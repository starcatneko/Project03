#pragma once

class GameBoard;
class MouseCtr;

#include <list>
#include <memory>

class GameTask
{
public:
	static GameTask &GetInstance()
	{
		return *s_Instance;
	};
	void Run();
	// �Ԃ�l 0b0001:���{�^��,0b0010:�E�{�^��,0b0100:���{�^��
	void UpDate(const MouseCtr& mouseCtr);

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

	void CreateNewBoard();

	// ���j�[�N�|�C���^
	std::unique_ptr<GameBoard> Board;
	std::unique_ptr<MouseCtr> Mouse;

	void (GameTask::*CurrentScene)();

	int mouseFlg;
	int mouseOld;
};


