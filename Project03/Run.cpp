#include "Run.h"
#include "GameMain.h"

Run *Run::s_Instance = nullptr;

void Run::Create()
{
	if (!s_Instance)
		s_Instance = new Run();
}

void Run::Destroy()
{
	if (s_Instance)
		delete s_Instance;
	s_Instance = nullptr;
}

Run::Run()
{
}
Run::~Run()
{
}

void Run::SceneCtr()
{
	/*
		��ʃN���b�N
		CurrentScene�؂�ւ�
	*/
	//CurrentScene = &GameMain::GetInstance()->GetInstance();
	//this->*(CurrentScene)();

}
