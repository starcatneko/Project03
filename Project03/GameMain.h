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
	//�}�b�v�ƃ`�b�v����������
	static GameMain *s_Instance;
	GameMain();
	~GameMain();

	void Update();

};

