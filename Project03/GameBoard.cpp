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
	printf("!");
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


		if (data[setPosY][setPosX].expired())
		{
			auto tmp = AddObjList(std::make_shared<GamePiece>(VECTOR{ setPosX,setPosY }, VECTOR{ X_DIS,Y_DIS }));
			data[setPosX][setPosY] = (*tmp);
		}

		
		switch (data[setPosY][setPosX].lock)
		{
		case PIECE_NON:

			data[setPosY][setPosX].lock()->SetState(PIECE_W);
			break;
		case PIECE_W:

			data[setPosY][setPosX].lock()->SetState(PIECE_B);
			break;
		case PIECE_B:
			data[setPosY][setPosX].lock()->SetState(PIECE_W);

			break;
		default:
			break;
		}
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
	
	for (auto itr = piecelist.begin(); itr != piecelist.end(); ++itr)
	{
		//itr().lock->Draw();

	}
	
}

auto GameBoard::AddObjList(piece_ptr && objPtr)
{
	// ������ ���e�����X�g�ɒǉ�
	piecelist.push_back(objPtr);
	//itr�ɒǉ�����piece�̃A�h���X������
	auto itr = piecelist.end();
	return itr;

}
