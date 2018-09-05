#pragma once
class Run
{
public:
	static void Create();
	static void Destroy();
	static Run *GetInstance()
	{
		Create();
		return s_Instance;
	};

	void SceneCtr();

private:
	static Run *s_Instance;
	Run();
	~Run();

	//int *(CurrentScene);
};

