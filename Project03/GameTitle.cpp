#include "GameTitle.h"
#include "GameTask.h"
#include "GamePiece.h"
#include "GameBoard.h"
#include "GameMain.h"
#include "MouseCtr.h"
#include "ImageMng.h"
#include "Player.h"

#include "DxLib.h"


GameTitle::GameTitle()
{
}


GameTitle::~GameTitle()
{
}
/*
void GameTitle::Update()
{

}*/
state_ptr GameTitle::Update(state_ptr pt)
{
	ImageMng::GetInstance().LoadImg("image/title.jpg", "title");

	ImageMng::GetInstance().DrawImg({ 120,240 }, "title", 0);
	DrawString(0, 0, "Title", 0xffffff, 0);

	if ((lpGameTask.Mouse->GetButton() & 0b0001) > 0)
	{

		int pl_cnt = 0;
		while (pl_cnt < PL_MAX)
		{
			// ŠÖ”‚Épl_cnt‚ð‰ÁŽZ‚³‚¹‚éˆ—‚ð‘g‚Ýž‚ñ‚¾‚ç’Zk‰Â”\
			AddPlayer();
			pl_cnt++;
		}

		return std::make_unique<GameMain>();
	}

	return pt;

}




void GameTitle::AddPlayer()
{
	//std::make_shared<Player>();
	lpGameTask.playerlist.push_back(std::make_shared<Player>());

}

void GameTitle::Draw()
{

}
