#include "GameBoard.h"
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
}

GameBoard::GameBoard(int size)
{
	Resize({ size,size });
}
GameBoard::GameBoard(VECTOR2 size)
{
	Resize(size);
}
GameBoard::~GameBoard()
{

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

void GameBoard::SetStone(VECTOR2 pos)
{
	int setPosX = pos.x - X_DIS;
	int setPosY = pos.y - Y_DIS;

	if (setPosX >= 0 && setPosY >= 0
		&& setPosX < (CHIPSIZE * boardSize.x)
		&& setPosY < (CHIPSIZE * boardSize.y))
	{
		setPosX /= CHIPSIZE;
		setPosY /= CHIPSIZE;

		//piecelist.push_back();

		switch (data[setPosY][setPosX])
		{
		case PIECE_NON:
			data[setPosY][setPosX] = PIECE_W;
			break;
		case PIECE_W:
			data[setPosY][setPosX] = PIECE_B;
			break;
		case PIECE_B:
			data[setPosY][setPosX] = PIECE_NON;
			break;
		default:
			break;
		}
	}
}

void GameBoard::DB_TouchBoad()
{
	/*
	int *XBuf = nullptr,*YBuf = nullptr;
	VECTOR2 MousePos;

	if ((GetMouseInput() == MOUSE_INPUT_LEFT) == true)
	{
		GetMousePoint(XBuf,YBuf);
		MousePos = { XBuf, YBuf };
		XBuf /= 8;
	}
	*/
}

void GameBoard::Update()
{
	Draw();
}

void GameBoard::Draw()
{

	DrawBox(X_DIS,Y_DIS, boardSize.x*CHIPSIZE + X_DIS,
		boardSize.y*CHIPSIZE + Y_DIS,
		0x008822, true);

	for (int y = 0; y < data.size(); y++)
	{

		for (int x = 0; x < BaseData.size()/ data.size(); x++)
		{
			/*
			DrawLine(x*CHIPSIZE + X_DIS, y*CHIPSIZE + Y_DIS
				, x*CHIPSIZE + CHIPSIZE + X_DIS,
				y*CHIPSIZE + Y_DIS, 0xffffff);
				*/
			
			DrawBox(x*CHIPSIZE+ X_DIS, y*CHIPSIZE+ Y_DIS
				, x*CHIPSIZE+ CHIPSIZE+ X_DIS,
				y*CHIPSIZE + CHIPSIZE+ Y_DIS, 0xffffff, false);

			switch (data[y][x])
			{
			case PIECE_W:
				DrawCircle(x*CHIPSIZE + X_DIS +(CHIPSIZE /2),
					y*CHIPSIZE + Y_DIS + (CHIPSIZE / 2),
					CHIPSIZE/2, 0xffffff, true, 1);
				break;
			case PIECE_B:
				DrawCircle(x*CHIPSIZE + X_DIS + (CHIPSIZE / 2),
					y*CHIPSIZE + Y_DIS + (CHIPSIZE / 2),
					CHIPSIZE/2, 0x000000, true, 1);
				break;
			}
		}
	}
}
