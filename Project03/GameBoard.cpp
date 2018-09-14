#include "GameBoard.h"
#include "GamePiece.h"
#include "Dxlib.h"
const int CHIPSIZE = 64;
#define BoardSize int(8)

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

#define X_DIS ((SCREEN_SIZE_X / 2) - (boardSize.x / 2)*CHIPSIZE)
#define Y_DIS ((SCREEN_SIZE_Y / 2) - (boardSize.y / 2)*CHIPSIZE)


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
	AddPlayer();
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

void GameBoard::ChangeStone(VECTOR2 pos)
{
	for (int y = -1; y <= 1; y++)
	{

		for (int x = -1; x <= 1; x++)
		{

		}

	}

}

void GameBoard::SetPiece(VECTOR2 pos)
{
	int setPosX = pos.x - X_DIS;
	int setPosY = pos.y - Y_DIS;

	// マウスでクリックした箇所が盤面の外の場合、この処理は行わない
	if (setPosX >= 0 && setPosY >= 0
		&& setPosX < (CHIPSIZE * boardSize.x)
		&& setPosY < (CHIPSIZE * boardSize.y))
	{
		// setPosを
		setPosX /= CHIPSIZE;
		setPosY /= CHIPSIZE;

		VECTOR2 vec1 = { setPosX,setPosY };
		VECTOR2 vec2 = { X_DIS,Y_DIS };

		if (data[setPosY][setPosX].expired())
		{
			piece_ptr tmp = AddObjList(std::make_shared<GamePiece>(vec1, vec2));
			data[setPosY][setPosX] = (tmp);
			data[setPosY][setPosX].lock()->SetState(PIECE_W);
		}

		
		switch (data[setPosY][setPosX].lock()->GetState())
		{

		case PIECE_W:
			data[setPosY][setPosX].lock()->SetState(PIECE_B);
			break;
		case PIECE_B:
			data[setPosY][setPosX].lock()->SetState(PIECE_W);

			break;
		default:
			break;
		}

		SarchReverse(vec1);
		CurrentPlayerChange();
	}
}

void GameBoard::DB_TouchBoad()
{

}

void GameBoard::Update()
{

	Draw();
}

void GameBoard::Draw()
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
	for (auto itr : piecelist)
	{
		itr->Draw();
		DrawFormatString(0, 48, 0xdddddd,"駒数%d",piecelist.size());
	}
}

void GameBoard::SarchReverse(VECTOR2 pos)
{
	// 0001 上方向 
	// 0010 右方向
	// 0100 下方向
	// 1000 左方向
	int sarch_dir = 0b0000;
	// チェックの基準になるピース
	PIECE_ST check_piece = data[pos.y][pos.x].lock()->GetState();

	if (pos.y < boardSize.y - 1 ) sarch_dir += 0001;
	if (pos.x > 0) sarch_dir += 0b0010;
	if (pos.y > 0) sarch_dir += 0b0100;
	if (pos.x < boardSize.x-1) sarch_dir += 0b1000;



	if( sarch_dir &0b0001);
		for (int i = 0; i < size.y; i++)
		{
			if (data[size.y - i][size.x].lock()->GetState() != check_piece
				&& data[size.y - i][size.x].lock() != nullptr)
			{
				data[size.y - i][size.x].lock()->Revarse();
			}
			else
			{
				return;
			}
		}
		
	if( sarch_dir &0b0011);
		for (int i = 0; (i < (boardSize.x - size.x)|| (i < size.y)); i++)
		{
			if (data[size.y - i][size.x - i].lock()->GetState() != check_piece
				&& data[size.y - i][size.x - i].lock() != nullptr)
			{
				data[size.y - i][size.x - i].lock()->Revarse();
			}
			else
			{
				return;
			}

		}
		
	if( sarch_dir &0b0010);
		for (int i = 0; i < (boardSize.x - size.x); i++)
		{
			if (data[size.y][size.x + i].lock()->GetState() != check_piece
				&& data[size.y][size.x + i].lock() != nullptr)
			{
				data[size.y][size.x + i].lock()->Revarse();
			}
			else
			{
				return;
			}

		}

		
	if( sarch_dir &0b0110);
		for (int i = 0; (i < (boardSize.x - size.x) || i < (boardSize.y - size.y)); i++)
		{
			if (data[size.y + i][size.x + i].lock()->GetState() != check_piece
				&& data[size.y + i][size.x + i].lock() != nullptr)
			{
				data[size.y + i][size.x + i].lock()->Revarse();
			}
			else
			{
				return;
			}

		}
		
	if( sarch_dir &0b0100);
		for (int i = 0; i < (boardSize.y - size.y); i++)
		{
			if (data[size.y + i][size.x].lock()->GetState() != check_piece
				&& data[size.y + i][size.x].lock() != nullptr)
			{
				data[size.y + i][size.x].lock()->Revarse();
			}
			else
			{
				return;
			}

		}

		

	if( sarch_dir &0b1100);
		for (int i = 0; i < ((boardSize.y - size.y) || i < size.x); i++)
		{
			if (data[size.y + i][size.x - i].lock()->GetState() != check_piece
				&& data[size.y + i][size.x - i].lock() != nullptr)
			{
				data[size.y + i][size.x - i].lock()->Revarse();
			}
			else
			{
				return;
			}

		}


		
	if( sarch_dir &0b1000);

		for (int i = 0; i < i < size.x; i++)
		{
			if (data[size.y][size.x - i].lock()->GetState() != check_piece
				&& data[size.y][size.x - i].lock() != nullptr)
			{
				data[size.y][size.x - i].lock()->Revarse();
			}
			else
			{
				return;
			}


		}
		
	if( sarch_dir &0b1001);

		for (int i = 0; i < (i < size.y || i < size.x); i++)
		{

			if (data[size.y - i][size.x - i].lock()->GetState() != check_piece
				&& data[size.y - i][size.x - i].lock() != nullptr)
			{
				data[size.y - i][size.x - i].lock()->Revarse();
			}
			else
			{
				return;
			}
		}
		

}

void GameBoard::AddPlayer()
{
	//std::make_shared<Player>();
	playerlist.push_back(std::make_shared<Player>());
}

void GameBoard::CurrentPlayerChange()
{
	if (currentPlayer == playerlist.end())
	{
		currentPlayer = playerlist.begin();
	}
	currentPlayer++;

	// 現在の順番を表示する関数を呼んで
}

piece_ptr GameBoard::AddObjList(piece_ptr && objPtr)
{
	// 引数の 内容をリストに追加
	piecelist.push_back(objPtr);
	//itrに追加したpieceのアドレスを入れる
	auto itr = piecelist.end();
	itr--;
	return *itr;
}
