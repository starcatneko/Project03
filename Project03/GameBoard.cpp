#include "GameBoard.h"
#include "Dxlib.h"
const int CHIPSIZE = 64;
#define BoardSize int(8)

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

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

void GameBoard::DB_TouchBoad()
{
	int *XBuf = nullptr,*YBuf = nullptr;
	VECTOR2 MousePos;

	if ((GetMouseInput() == MOUSE_INPUT_LEFT) == true)
	{
		GetMousePoint(XBuf,YBuf);
		/*MousePos = { &XBuf, &YBuf };
		XBuf /= 8;*/
	}
}

void GameBoard::Update()
{
	DrawBoardGrid();
}

void GameBoard::DrawBoardGrid()
{
	int x_Dis = (SCREEN_SIZE_X / 2) - (boardSize.x / 2)*CHIPSIZE;
	int Y_Dis = (SCREEN_SIZE_Y / 2) - (boardSize.y / 2)*CHIPSIZE;

	DrawBox(x_Dis,Y_Dis
		, boardSize.x*CHIPSIZE + x_Dis,
		boardSize.y*CHIPSIZE + Y_Dis,
		0x008822, true);

	for (int y = 0; y < data.size(); y++)
	{

		for (int x = 0; x < data.size(); x++)
		{
			DrawBox(x*CHIPSIZE+ x_Dis, y*CHIPSIZE+ Y_Dis
				, x*CHIPSIZE+ CHIPSIZE+ x_Dis,
				y*CHIPSIZE + CHIPSIZE+ Y_Dis, 0xffffff, false);
		}
	}
}
