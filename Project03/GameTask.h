#pragma once

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
		// mutex call_once ˆê“x‚¾‚¯ŒÄ‚Ô
		std::call_once(initFlag, Create);
		Create();
		return s_Instance;
	};
	void Run();

	void GetMouse();

private:
	GameTask();
	~GameTask();
	void Init();
	static std::once_flag initFlag;
	static GameTask *s_Instance;

	int (*CurrentScene)();

	int mouseOld;
};


