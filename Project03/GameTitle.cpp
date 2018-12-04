#include "GameTitle.h"
#include "GameTask.h"
#include "GameMain.h"
#include "MouseCtr.h"
#include "ImageMng.h"
#include "Player.h"

#include "DxLib.h"


GameTitle::GameTitle()
{
	Init();
}


GameTitle::~GameTitle()
{
}

void GameTitle::Init()
{
}

state_ptr GameTitle::Update(state_ptr pt)
{
	ImageMng::GetInstance().LoadImg("image/title.jpg", "title");
	DrawString(0, 0, "Title", 0xffffff, 0);	

	ImageMng::GetInstance().DrawImg({ 120,240 }, "title", 0);

	if ((lpMouse.GetButton() & 0b0001) > 0)
	{
		return std::make_unique<GameMain>();
	}
	return pt;

}



void GameTitle::Draw()
{

}