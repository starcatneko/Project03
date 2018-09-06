#include "DxLib.h"

#include "Run.h"

#define SCREEN_SIZE_X 860
#define SCREEN_SIZE_Y 640

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	
		ClsDrawScreen();

		Run::GetInstance()->SceneCtr();
		ScreenFlip();


	Run::GetInstance()->Destroy();
	return 0;
}