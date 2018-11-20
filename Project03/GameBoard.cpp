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

	PIECE_ST ai = PIECE_ST::B;
	++ai;
	++ai;
	++ai;

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

	piece_shared tmp = AddObjList(std::make_shared<GamePiece>(pos, vec, (*GameTask::GetInstance().currentPlayer)->GetType()));
	data[pos.y][pos.x] = (tmp);
	data[pos.y][pos.x].lock()->SetState((*GameTask::GetInstance().currentPlayer)->GetType());
}

void GameBoard::SetPiece(VECTOR2 pos , PIECE_ST st)
{
	VECTOR2 vec = { X_DIS,Y_DIS };

	piece_shared tmp = AddObjList(std::make_shared<GamePiece>(pos, vec,st));
	data[pos.y][pos.x] = (tmp);
	data[pos.y][pos.x].lock()->SetState(st);

}

void GameBoard::SetPiece(VECTOR2 pos)
{
	(*GameTask::GetInstance().currentPlayer)->SelectTray(pos);
	VECTOR2 vec1 = Pos_MouseToBoard(pos);

	bool plChangeFlg = false;
	// マウスでクリックした箇所が盤面の外の場合、この処理は行わない
	if (vec1.x >= 0 && vec1.y >= 0
		&& vec1.x <  boardSize.x
		&& vec1.y < boardSize.y)
	{

		VECTOR2 vec2 = { X_DIS,Y_DIS };

		VECTOR2 sarchTBL[8] = {{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 }};
		
		// クラスに組み込んだ方がいい
		int cnt_Reverse = 0;

		if (data[vec1.y][vec1.x].expired())
		{
			for (auto itr : sarchTBL)
			{
				// 方向に向かってひっくり返す関数
				if(SarchReverse(vec1, itr, (*GameTask::GetInstance().currentPlayer)->GetType()))
				{
					piece_shared tmp = AddObjList(std::make_shared<GamePiece>(vec1, vec2));
					data[vec1.y][vec1.x] = (tmp);
					data[vec1.y][vec1.x].lock()->SetState((*GameTask::GetInstance().currentPlayer)->GetType());

					int reverseTime = REVERSE_TIME;

					for(int i = 1;Reverse(vec1, itr*i) == true;i++)
					{
						VECTOR2 setvec = vec1 + itr * i;
						reverseTime += REVERSE_TIME;
						//delete &data[setvec.y][setvec.x].lock();
						piece_shared tmp = AddObjList(std::make_shared<GamePiece>(setvec, vec2));
						data[setvec.y][setvec.x] = (tmp);
						data[setvec.y][setvec.x].lock()->SetState((*GameTask::GetInstance().currentPlayer)->GetType());
						lastset = (*GameTask::GetInstance().currentPlayer)->GetNo();
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
					(*lpGameTask.currentPlayer)->SetTurnTimer(reverseTime);
				}
			}
		}
		else
		{
			return;
		}
		if (plChangeFlg)
		{
			//(//*lpGameTask.currentPlayer)->DeleteTrayPiece()
			/*
			if (lpGameTask.currentPlayer.size())
			{
				(*lpGameTask.currentPlayer)->DeleteTrayPiece();
			}*/
			// 誰かが置ける状態の場合
			(*lpGameTask.currentPlayer)->SetTunrFlg(false);

			// -----現在のプレイヤー表示
			CurrentPlPiece->SetState((*lpGameTask.currentPlayer)->GetType());

		}

	}
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
		
		/*DrawFormatString(
			SCREEN_HALF_X - GetDrawStringWidth(str1.c_str(), strlen(str1.c_str()))/2,
			320, 0xFF4444, str1.c_str(), (*GameTask::GetInstance().currentPlayer)->GetNo());
			*/
		SetFontSize(16);
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
	if (data[sarchPos.y][sarchPos.x].lock()->GetState() != (*GameTask::GetInstance().currentPlayer)->GetType())
	{
		return true;
	}
	else
		return false;
}

bool GameBoard::SarchReverse(VECTOR2 pos, VECTOR2 vec ,PIECE_ST st)
{
	VECTOR2 sarchPos;

	for (int i = 1; i < data.size(); i++)
	{
		sarchPos = pos + (vec*i);

		// サーチするマスが盤面の外にはみ出していないかのチェック
		if (sarchPos.x < 0 || sarchPos.y < 0 ||
			sarchPos.x >= data.size() || sarchPos.y >= data.size()
			)
		{
			return false;
		}

		// サーチ位置に駒が配置されているか
		if (!data[sarchPos.y][sarchPos.x].expired())
		{
			// 駒が配置されていた場合、その駒がプレイヤーの駒と一致するか
			if (data[sarchPos.y][sarchPos.x].lock()->GetState() == st)
			{
				// 駒がサーチ基準と隣接していない場合true
				if (i >= 2)
					return true;
				else
					return false;
			}
			else
			{
				continue;
			}
		}
		else
		{
			return false;
		}
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
	ADDWAIT(4);
	(*itr)->SetWait(GETWAIT());
	(*itr)->SetAnimF(7);
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
		itr->Update();
	}

	/*
	for (piece_list::iterator itr = piecelist.begin();
		*itr != piecelist.back(); itr++)
	{
		(*itr)->Draw();
		/*
		if ((*itr)->Update() == false)
		{
			piecelist.erase(itr);
		}
	}*/

}

void GameBoard::Draw()
{
	

	//DrawBox(itr.x, itr.y, itr.x + 64, itr.y + 64, 0xDDDDDD, true);

	auto DrawBoard = [&]() {
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
	};

	DrawBoard();

	VECTOR2 CurrntPlPos = CurrentPlPiece->GetPos();

	/*
	DrawBox(CurrntPlPos.x*CHIPSIZE + X_DIS, CurrntPlPos.y*CHIPSIZE + Y_DIS
		, CurrntPlPos.x*CHIPSIZE + CHIPSIZE + X_DIS,
		CurrntPlPos.y*CHIPSIZE + CHIPSIZE + Y_DIS, 0x006600, true);

	CurrentPlPiece->Draw();
	*/
	/*
	if (gameEndFlg != true)
	{
		CurrentSetUpData();
	}
	*/
	// 現在の番のプレイヤーを表示する

	DrawPiece();

	DrawFormatString(0, 64, 0xdddddd, "プレイヤー数%d", GameTask::GetInstance().playerlist.size());
	DrawFormatString(0, 96, 0xdddddd, "現在のプレイヤー\n%d", (*GameTask::GetInstance().currentPlayer)->GetNo());

}

void SetlistClear()
{

}

void GameBoard::CurrentSetUpData()
{
	
	setlist.clear();
	VECTOR2 sarchTBL[8] = { { 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 }, };
	
	// 設置可能なタイルの数
	int tilecnt = 0;
	for (auto itr : piecelist)
	{
		for (auto vec_itr : sarchTBL)
		{
			for (auto vec_itr2 : sarchTBL)
			{
				VECTOR2 drawPos = itr->GetPos() + vec_itr;
				

				if (drawPos.x < 0 || drawPos.y < 0 ||
					drawPos.x >= data.size() || drawPos.y >= data.size()
					)
				{
					break;
				}
				SarchReverse(drawPos, vec_itr2, (*lpGameTask.currentPlayer)->GetType());

				if (SarchReverse(drawPos, vec_itr2, (*lpGameTask.currentPlayer)->GetType())
					&& data[drawPos.y][drawPos.x].expired())
				{
					tilecnt++;
					setlist.push_back(drawPos);
				/*
					DrawBox(drawPos.x*CHIPSIZE + X_DIS, drawPos.y*CHIPSIZE + Y_DIS
						, drawPos.x*CHIPSIZE + CHIPSIZE + X_DIS,
						drawPos.y*CHIPSIZE + CHIPSIZE + Y_DIS, 0xaadd00, true);
				*/}
			}
		}
	}

	// 設置可能なタイルが無い場合
	if (tilecnt == 0)
	{
		// 設置できるプレイヤーが一人も居ない場合
		if (lastset == (*GameTask::GetInstance().currentPlayer)->GetNo())
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
	/*auto listD = [&](auto i) {
		i.erase(
			i.begin(),
			i.end());
	};*/
	TotalPiece.fill(0);
	int i = 0;
	for (auto itr : BaseData)
	{
		i++;
		if (itr.expired())
			continue;
		TotalPiece[(int)(itr.lock()->GetState()) - 1]++;
	}

	//listD(BaseData);
	//listD(piecelist);
	BaseData.clear();
	piecelist.clear();
	for (auto itr : TotalPiece)
	{
		//BaseData.push_back(
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
			tmpPos = (itr*64)+12 + VECTOR2( X_DIS, Y_DIS );
			break;
		}
		cnt++;
	}


	return tmpPos;
}