#pragma once
class GameMain
{
public:
	static void Create();
	static void Destroy();
	static GameMain *GetInstance()
	{
		Create();
		return s_Instance;
	};
	void Init();
 
private:
	//マップとチップを持たせる
	static GameMain *s_Instance;
	GameMain();
	~GameMain();

	void Update();

};

