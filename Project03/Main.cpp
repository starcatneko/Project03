#include "DxLib.h"
#include "GameTask.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DxLib_Init();
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	

	GameTask::GetInstance()->Run();


	DxLib_End();
	return 0;
}