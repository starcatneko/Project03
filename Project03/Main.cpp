#include "DxLib.h"
#include "GameTask.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("‚¨‚¹‚ë");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1);
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == false)
	{
		GameTask::GetInstance().Run();
	}

	DxLib_End();
	return 0;
}