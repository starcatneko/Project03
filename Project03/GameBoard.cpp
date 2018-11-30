#include "Dxlib.h"
#include "GameTask.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "GameMain.h"
#include "Player.h"
#include "PieceState.h"

// リバース描画のテスト用
#define TEST_REVERSE 0


const int CHIPSIZE = 64;
GameBoard::GameBoard()
{
	Resize({ BoardSize, BoardSize });
	Init();
	

}

GameBoard::GameBoard(int size)
{
	Resize({ size,size });
	Init();
}
GameBoard::GameBoard(VECTOR2 size)
{
	Resize(size);
	Init();
}
GameBoard::~GameBoard()
{
	printf("!");
}
bool GameBoard::Init()
{
	//GameTask::GetInstance().playerlist.remove(;
	gameEndFlg = false;
	for (auto itr : GameTask::GetInstance().playerlist)
	{
		(*itr).SetTray();
	}

	timer = 0;
	CurrentPlPiece = std::make_unique<GamePiece>(VECTOR2{ 9,0 }, VECTOR2{ X_DIS,Y_DIS }, PIECE_ST::B);
	
	return true;
}

VECTOR2 GameBoard::Pos_MouseToBoard(VECTOR2 mousePos)
{
	int setPosX = mousePos.x - X_DIS;
	int setPosY = mousePos.y - Y_DIS;
	return{ setPosX / CHIPSIZE, setPosY / CHIPSIZE };
}
VECTOR2 GameBoard::Pos_BoardToMouse(VECTOR2 BoardPos)
{
	return { BoardPos.x*CHIPSIZE ,BoardPos.y*CHIPSIZE };
}

bool GameBoard::Resize(VECTOR2 size)
{

	BaseData.resize(size.x*size.y);
	data.resize(size.x);
	for (int x = 0; x < size.x; x++)
	{
		data[x] = &BaseData[x * size.y];
	}
	
	boardSize = {size.x,size.y};
	return true;
}


void GameBoard::Debug_SetPiece(VECTOR2 pos)
{
	VECTOR2 vec = { Pos_MouseToBoard(pos)};

	piece_shared tmp = AddObjList(std::make_shared<GamePiece>(pos, vec, lpCurrentPlayer->GetType()));
	data[pos.y][pos.x] = (tmp);
	data[pos.y][pos.x].lock()->SetState(lpCurrentPlayer->GetType());
}

void GameBoard::SetPiece(VECTOR2 pos , PIECE_ST st)
{
	VECTOR2 vec = { X_DIS,Y_DIS };

	piece_shared tmp = AddObjList(std::make_shared<GamePiece>(pos, vec,st));
	data[pos.y][pos.x] = (tmp);
	data[pos.y][pos.x].lock()->SetState(st);

}

bool GameBoard::CheckExpired(VECTOR2 pos)
{
	if (CheckOverBoard(pos)) {
		if (data[pos.y][pos.x].expired())
		{
			return true;
		}
	}
	return false;
}

bool GameBoard::SetPiece(VECTOR2 pos)
{
	// 返り値用変数
	bool rtn = false;
	lpCurrentPlayer->SelectTray(pos);
	VECTOR2 vec1 = Pos_MouseToBoard(pos);
	
	// マウスでクリックした箇所が盤面の外の場合、処理を中断する
	if (!CheckOverBoard(vec1) ||
		!CheckExpired(vec1)	)
	{
		return false;
	}

	bool plChangeFlg = false;
	rtn = true;
	VECTOR2 vec2 = { X_DIS,Y_DIS };
	VECTOR2 sarchTBL[8] = {{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 }};
		int cnt_Reverse = 0;
	
	for (auto itr : sarchTBL)
	{
		// 方向に向かってひっくり返す関数
		if (!SarchReverse(vec1, itr, lpCurrentPlayer->GetType()))
		{
			continue;
		}

		piece_shared tmp = AddObjList(std::make_shared<GamePiece>(vec1, vec2));
		data[vec1.y][vec1.x] = (tmp);
		data[vec1.y][vec1.x].lock()->SetState(lpCurrentPlayer->GetType());

		int reverseTime = REVERSE_TIME;
		for(int i = 1;Reverse(vec1, itr*i) == true;i++)
		{
			VECTOR2 setvec = vec1 + itr * i;
			reverseTime += REVERSE_TIME;

			piece_shared tmp = AddObjList(std::make_shared<GamePiece>(setvec, vec2));
			data[setvec.y][setvec.x] = (tmp);
			data[setvec.y][setvec.x].lock()->SetState(lpCurrentPlayer->GetType());
			lastset = lpCurrentPlayer->GetNo();
			plChangeFlg = true;

			switch (TEST_REVERSE)
			{
			case 0:
				data[setvec.y][setvec.x].lock()->SetReverse(i);
				break;
			case 1:
				data[setvec.y][setvec.x].lock()->SetReverse(cnt_Reverse++);
				break;
			}
		}
		lpCurrentPlayer->SetTurnTimer(reverseTime);
		
	}

	// 誰かが置ける状態の場合
	if (plChangeFlg)
	{
		lpCurrentPlayer->SetTunrFlg(false);
	}

	return rtn;
}

void GameBoard::DB_TouchBoad()
{

}

void GameBoard::Update()
{
	if (gameEndFlg)
	{
		std::string str1;
		str1 = "WINNER PLAYER";
		SetFontSize(48);

		//GetDrawStringWidth(str1.c_str(),strlen(str1.c_str()))
		SetFontSize(DEFAULT_FONT_SIZE);
	}

	if (TURN_CHANGE_WAIT == lpCurrentPlayer->GetTurnTimer())
	{
		setlist.clear();
	}
}

void GameBoard::ResultDraw()
{
	int i = 0;
	for (auto itr : TotalPiece)
	{
		DrawFormatString(i * 48, 0, 0xffff00, "%d", itr);
		i++;
	}
	//for(auto itr: (*lpGameTask->playerList)
}

bool GameBoard::Reverse(VECTOR2 pos, VECTOR2 vec)
{
	// i方向
	VECTOR2 sarchPos = pos + (vec);
	if (data[sarchPos.y][sarchPos.x].lock()->GetState() != lpCurrentPlayer->GetType())
	{
		return true;
	}
	return false;
}


bool GameBoard::SarchReverse(VECTOR2 pos, VECTOR2 vec ,PIECE_ST st)
{
	VECTOR2 sarchPos;

	for (int i = 1; i < data.size(); i++)
	{
		sarchPos = pos + (vec*i);
		// サーチするマスが盤面の外にはみ出していないかのチェック
		if (!CheckOverBoard(sarchPos)
			|| CheckExpired(sarchPos))
		{
			return false;
		}
		// 駒が配置されていた場合、その駒がプレイヤーの駒じゃない場合
		if (!(data[sarchPos.y][sarchPos.x].lock()->GetState() == st))
		{
			continue;
		}
		// サーチした駒がプレイヤーの駒だった場合
		// 駒がサーチ基準と隣接していない場合true
		if (i >= 2)
			return true;
		else
			return false;

	}

	return false;
}


VECTOR2 GameBoard::GetBoardSize()
{
	return { (int)BaseData.size()/ (int)data.size(), (int)data.size() };
}


piece_shared GameBoard::AddObjList(piece_shared && objPtr)
{
	piecelist.push_back(objPtr);
	for (auto itr = piecelist.begin();
		*itr != piecelist.back(); itr++)
	{
		if ((*itr)->GetPos() == objPtr->GetPos())
		{
			objPtr->SetOldState((*itr)->GetState());
			piecelist.erase(itr);
			break;
		}
	}
	// 引数の 内容をリストにf追加
	//itrに追加したpieceのアドレスを入れる
	auto itr = piecelist.end();
	itr--;
	(*itr)->SetAnimF(REVERSE_TIME-1);
	return *itr;
}
void GameBoard::GameEnd()
{
	std::array<int,PL_MAX> pieceCnt;
	pieceCnt.fill(0);
	for(auto itr : piecelist)
	{
		pieceCnt[int(itr->GetState())-1]++;
	}
}

void GameBoard::DrawPiece()
{
	DrawFormatString(120, 0, 0xdddddd, "%d", piecelist.size());

	for (auto itr : piecelist)
	{
		itr->Draw();
	}


}
void GameBoard::DrawBoard()
{
	DrawBox(X_DIS, Y_DIS, boardSize.x*CHIPSIZE + X_DIS,
		boardSize.y*CHIPSIZE + Y_DIS,
		0x008822, true);

	for (int y = 0; y < data.size(); y++)
	{

		for (int x = 0; x < BaseData.size() / data.size(); x++)
		{
			DrawBox(x*CHIPSIZE + X_DIS, y*CHIPSIZE + Y_DIS
				, x*CHIPSIZE + CHIPSIZE + X_DIS,
				y*CHIPSIZE + CHIPSIZE + Y_DIS, 0xffffff, false);
		}
	}
}
void GameBoard::Draw()
{

	DrawBoard();
	VECTOR2 CurrntPlPos = CurrentPlPiece->GetPos();
	for (auto itr : setlist)
	{
		VECTOR2 drawpos = itr * 64;
		DrawBox(drawpos.x + X_DIS+1, drawpos.y + Y_DIS+1,
			drawpos.x + 64 + X_DIS-1, drawpos.y + 64 + Y_DIS-1, 0x00dd00, true);
	}
	DrawPiece();
	DrawFormatString(0, 64, 0xdddddd, "プレイヤー数%d", GameTask::GetInstance().playerlist.size());
	DrawFormatString(0, 96, 0xdddddd, "現在のプレイヤー\n%d", lpCurrentPlayer->GetNo());

}
void GameBoard::SetlistUpdata()
{
	VECTOR2 sarchTBL[8] = { { 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 }, };
	
	// 設置可能なタイルの数
	int tilecnt = 0;
	// 既に置いてある駒
	for (auto piece_itr : piecelist)
	{
		// 駒の周囲八方向
		for (auto vec_itr : sarchTBL)
		{
			// 配置されている駒の周りのマス
			VECTOR2 tempPos = piece_itr->GetPos() + vec_itr;

			if (!CheckOverBoard(tempPos))
			{
				continue;
			}
			// 駒の周囲八方向のマスを中心に、八方向に向かって駒を配置できるか検索する
			for (auto vec_itr2 : sarchTBL)
			{
				if (SarchReverse(tempPos, vec_itr2, (*lpGameTask.currentPlayer)->GetType())
					&& data[tempPos.y][tempPos.x].expired()
					)
				{
					tilecnt++;
					setlist.push_back(tempPos);
				}
			}
		}
	}

	// 設置可能なタイルが無い場合
	if (tilecnt == 0)
	{
		// 設置できるプレイヤーが一人も居ない場合
		if (lastset == lpCurrentPlayer->GetNo())
		{
			this->GameEnd();
			gameEndFlg = true;
			return;
		}
		(*lpGameTask.currentPlayer)->SetTunrFlg(false);
	}
}

void GameBoard::PieceResultSet()
{
	TotalPiece.fill(0);
	int i = 0;
	for (auto itr : BaseData)
	{
		i++;
		if (itr.expired())
			continue;
		TotalPiece[(int)(itr.lock()->GetState()) - 1]++;
	}

	for (auto itr : TotalPiece)
	{
	}
}

int GameBoard::PieceCount(PIECE_ST color)
{
	int cnt = 0;
	for (int y = 0; y < data.size(); y++)
	{
		for (int x = 0; x < BaseData.size() / data.size(); x++)
		{
			if (color == data[y][x].lock()->GetState())
			{
				cnt++;
			}
		}
	}
	return cnt;
}

VECTOR2 GameBoard::SetlistSerch()
{
	VECTOR2 tmpPos;
	if (&setlist == nullptr)
	{
		return { -1,-1 };
	}

	int rnd = GetRand(static_cast<int>(setlist.size()));
	int cnt = 0;
	for (auto itr : setlist)
	{
		if (rnd == cnt)
		{
			tmpPos = (itr*CHIPSIZE)+(CHIPSIZE/2 )+ VECTOR2( X_DIS, Y_DIS );
			break;
		}
		cnt++;
	}


	return tmpPos;
}

bool GameBoard::CheckOverBoard(VECTOR2 checkPos)
{
	if (checkPos.x < 0 || checkPos.y < 0 ||
		checkPos.x >= data.size() || checkPos.y >= BaseData.size()/ data.size()
		)
	{
		return false;
	}
	return true;
}