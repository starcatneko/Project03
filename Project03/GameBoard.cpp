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
	boardSize = { BoardSize,BoardSize };
	BaseData.resize(BoardSize*BoardSize);
	data.resize(BoardSize);
	for (int x = 0; x < data.size(); x++)
	{
		data[x] = &BaseData[x * BoardSize];
	}
	//board.resize(8,8) ;
}

GameBoard::GameBoard(int size)
{
	boardSize = { size,size};

	BaseData.resize(size*size);
	data.resize(size);
	for (int x = 0; x < size; x++)
	{
		data[x] = &BaseData[x * size];
	}
}
GameBoard::GameBoard(VECTOR2 size)
{
	boardSize = size;

	BaseData.resize(size.x*size.y);
	data.resize(size.x);
	for (int x = 0; x < size.x; x++)
	{
		data[x] = &BaseData[x * size.y];
	}
}
GameBoard::~GameBoard()
{
}

void GameBoard::SetBoardSize(VECTOR2 size)
{
	//board = std::vector<std::vector<PIECE_ST>>(size.x,size.y);
}

void GameBoard::SetStone(VECTOR2 pos)
{
	int setPosX = pos.x - X_DIS;
	int setPosY = pos.y - Y_DIS;

	if (setPosX >= 0 && setPosY >= 0)
	{
		switch (data[y][x])
		{

		case PIECE_NON:
			data[(setPosY / CHIPSIZE)][(setPosX / CHIPSIZE)] = PIECE_W;
			break;
		case PIECE_W:
			data[(setPosY / CHIPSIZE)][(setPosX / CHIPSIZE)] = PIECE_B;
			break;
		case PIECE_B:
			data[(setPosY / CHIPSIZE)][(setPosX / CHIPSIZE)] = PIECE_NON;
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
	DrawBoardGrid();

}

void GameBoard::DrawBoardGrid()
{

	DrawBox(X_DIS,Y_DIS, boardSize.x*CHIPSIZE + X_DIS,
		boardSize.y*CHIPSIZE + Y_DIS,
		0x008822, true);

	for (int y = 0; y < data.size(); y++)
	{

		for (int x = 0; x < data.size(); x++)
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
				DrawCircle(x*CHIPSIZE + X_DIS, y*CHIPSIZE + Y_DIS,
					CHIPSIZE, 0xffffff, true, 1);
				break;
			case PIECE_B:
				DrawCircle(x*CHIPSIZE + X_DIS, y*CHIPSIZE + Y_DIS,
					CHIPSIZE, 0x000000, true, 1);
				break;
			}
		}
	}
}
