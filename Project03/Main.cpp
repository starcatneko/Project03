#include "DxLib.h"
#include "GameTask.h"
#include <chrono>

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("おせろ");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return 0;
	}
	SetDrawScreen(DX_SCREEN_BACK);


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == false)
	{
		auto start = std::chrono::system_clock::now(); // 計測開始時間
												  // 処理


		GameTask::GetInstance().Run();
		auto end = std::chrono::system_clock::now();  // 計測終了時間
		int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //処理に要した時間をミリ秒に変換

		DrawFormatString(SCREEN_SIZE_X - 48, SCREEN_SIZE_Y - 20, 0xffffff, "%d", elapsed);
	}

	DxLib_End();
	return 0;
}