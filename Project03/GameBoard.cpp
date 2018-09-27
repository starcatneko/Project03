#include "GameBoard.h"
#include "GamePiece.h"
#include "Dxlib.h"
#include "Player.h"

const int CHIPSIZE = 64;
#define BoardSize int(8)

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

#define X_DIS ((SCREEN_SIZE_X / 2) - (boardSize.x / 2)*CHIPSIZE)
#define Y_DIS ((SCREEN_SIZE_Y / 2) - (boardSize.y / 2)*CHIPSIZE)

// �v���C���[�l��
#define PL_MAX 2

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
	int pl_cnt = 0;
	while (pl_cnt < PL_MAX)
	{
		// �֐���pl_cnt�����Z�����鏈����g�ݍ��񂾂�Z�k�\
		AddPlayer(pl_cnt);
		pl_cnt++;
	}
	SetPiece({ 4,4 }, PIECE_W);
	SetPiece({ 5,5 }, PIECE_RED);
	SetPiece({ 4,5 }, PIECE_BLU);
	SetPiece({ 5,4 }, PIECE_B);


	currentPlayer = playerlist.begin();
	return true;
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
void GameBoard::SetPiece(VECTOR2 pos , PIECE_ST st)
{
	VECTOR2 vec = { X_DIS,Y_DIS };

	piece_ptr tmp = AddObjList(std::make_shared<GamePiece>(pos, vec,st));
	data[pos.y][pos.x] = (tmp);
	data[pos.y][pos.x].lock()->SetState(st);

}

void GameBoard::SetPiece(VECTOR2 pos)
{
	int setPosX = pos.x - X_DIS;
	int setPosY = pos.y - Y_DIS;

	// �}�E�X�ŃN���b�N�����ӏ����Ֆʂ̊O�̏ꍇ�A���̏����͍s��Ȃ�
	if (setPosX >= 0 && setPosY >= 0
		&& setPosX < (CHIPSIZE * boardSize.x)
		&& setPosY < (CHIPSIZE * boardSize.y))
	{
		// setPos��

		setPosX /= CHIPSIZE;
		setPosY /= CHIPSIZE;

		VECTOR2 vec1 = { setPosX,setPosY };
		VECTOR2 vec2 = { X_DIS,Y_DIS };

		VECTOR2 sarchTBL[8] = { { 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 }, };


		if (data[vec1.y][vec1.x].expired())
		{
			for (auto itr : sarchTBL)
			{

				// �����Ɍ������ĂЂ�����Ԃ��֐�
				if(SarchReverse(vec1, itr))
				{
					piece_ptr tmp = AddObjList(std::make_shared<GamePiece>(vec1, vec2));
					data[vec1.y][vec1.x] = (tmp);
					data[vec1.y][vec1.x].lock()->SetState((*currentPlayer)->GetType());

					for(int i = 1;Reverse(vec1, itr*i) == true;i++)
					{
						VECTOR2 setvec = vec1 + itr * i;

						piece_ptr tmp = AddObjList(std::make_shared<GamePiece>(setvec, vec2));
						data[setvec.y][setvec.x] = (tmp);
						data[setvec.y][setvec.x].lock()->SetState((*currentPlayer)->GetType());
					}
					CurrentPlayerChange();

				}
			}


		}
		else
		{
			return;
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
	for (auto itr : piecelist)
	{
		itr->Draw();
		DrawFormatString(0, 48, 0xdddddd,"�%d",piecelist.size());
	}

	DrawFormatString(0, 64, 0xdddddd, "�v���C���[��%d", playerlist.size());
	DrawFormatString(0, 96, 0xdddddd, "���݂̃v���C���[\n%d", (*currentPlayer)->GetNo());

}
bool GameBoard::Reverse(VECTOR2 pos, VECTOR2 vec)
{
	// i����
	VECTOR2 sarchPos = pos + (vec);

	if (data[sarchPos.y][sarchPos.x].lock()->GetState() != (*currentPlayer)->GetType())
		return true;
	else
		return false;
}

bool GameBoard::SarchReverse(VECTOR2 pos, VECTOR2 vec)
{
	PIECE_ST check_piece = (*currentPlayer)->GetType();
	VECTOR2 sarchPos;

	for (int i = 1; i < data.size(); i++)
	{
		sarchPos = pos + (vec*i);

		// �T�[�`����}�X���Ֆʂ̊O�ɂ͂ݏo���Ă��Ȃ����̃`�F�b�N
		if (sarchPos.x < 0 || sarchPos.y < 0 ||
			sarchPos.x >= data.size() || sarchPos.y >= BaseData.size()
			)
		{
			return false;
		}

		// �T�[�`�ʒu�ɋ�z�u����Ă��邩
		if (!data[sarchPos.y][sarchPos.x].expired())
		{
			// ��z�u����Ă����ꍇ�A���̋�v���C���[�̋�ƈ�v���邩
			if (data[sarchPos.y][sarchPos.x].lock()->GetState() == check_piece)
			{
				// ��T�[�`��Ɨאڂ��Ă��Ȃ��ꍇtrue
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

bool GameBoard::SarchReverse_OLD(VECTOR2 pos)
{
	// 0001 ����� 
	// 0010 �E����
	// 0100 ������
	// 1000 ������
	int sarch_dir = 0b0000;

	bool flg = false;

	// �`�F�b�N�̊�ɂȂ�s�[�X
	PIECE_ST check_piece = (*currentPlayer)->GetType();

	/*
	int bit;
	bit = (sarch_dir>>2 &0b01);
	*/

	// ��ɗ]��
	if (pos.y > 0) sarch_dir += 0001;
	// �E�ɗ]��
	if (pos.x < boardSize.x - 1) sarch_dir += 0b0010;
	// ���ɗ]��
	if (pos.y < boardSize.y - 1) sarch_dir += 0b0100;
	// ���ɗ]��
	if (pos.x > 0) sarch_dir += 0b1000;


	if (sarch_dir & 0b0001)
	{
		for (int i = 1; i < boardSize.y; i++)
		{
			// �T�[�`�ʒu�ɋ�z�u����Ă��邩
			if (!data[pos.y - i][pos.x].expired())
			{
				// ��z�u����Ă����ꍇ�A���̋�v���C���[�̋�ƈ�v���邩
				if (data[pos.y - i][pos.x].lock()->GetState() == check_piece && i >= 2)
				{
					hitDir[sarch_dir] = true;
					flg = true;
				}
				else if (i == 1 && data[pos.y - i][pos.x].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}
		}
	}
		
	if (sarch_dir & 0b0011)
	{
		for (int i = 1; (i < (boardSize.x - boardSize.x) || (i < boardSize.y)); i++)
		{
			if (!data[pos.y - i][pos.x - i].expired())
			{
				if (!data[pos.y - i][pos.x - i].lock()->GetState() == check_piece && i >= 2)
				{
					hitDir[sarch_dir] = true;
					flg = true;
				}
				else if (i == 1 && data[pos.y - i][pos.x - i].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}

		}
	}
		
	if( sarch_dir &0b0010)
		for (int i = 1; i < (boardSize.x - boardSize.x); i++)
		{
			if (!data[pos.y][pos.x + i].expired())
			{
				if (!data[pos.y][pos.x + i].lock()->GetState() == check_piece && i >= 2)
				{
					hitDir[sarch_dir] = true;
					flg = true;
				}

				else if (i == 1 && data[pos.y][pos.x + i].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}

		}

		
	if (sarch_dir & 0b0110)
	{
		for (int i = 1; (i < (boardSize.x - boardSize.x) || i < (boardSize.y - boardSize.y)); i++)
		{
			if (!data[pos.y + i][pos.x + i].expired())
			{
				if (data[pos.y + i][pos.x + i].lock()->GetState() == check_piece && i >= 2)
				{
					hitDir[sarch_dir] = true;
					flg = true;
				}
				else if (i == 1 && data[pos.y + i][pos.x + i].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}
		}
	}
		
	if (sarch_dir & 0b0100)
	{
		for (int i = 1;i < (boardSize.y - boardSize.y); i++)
		{
			if (!data[pos.y - i][pos.x].expired())
			{
				if (data[pos.y - i][pos.x].lock()->GetState() == check_piece && i >= 2)
				{
					hitDir[sarch_dir] = true;
					flg = true;
				}
				else if (i == 1 && data[pos.y - i][pos.x].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}

		}
		return flg;
	}
		

	if (sarch_dir & 0b1100)
	{
		for (int i = 1;(i < boardSize.y || i < boardSize.x); i++)
		{
			if (!data[pos.y + i][pos.x - i].expired())
			{
				if (data[pos.y + i][pos.x - i].lock()->GetState() == check_piece && i >= 2)
				{
					hitDir[sarch_dir] = true;
				}
				else if (i == 1 && data[pos.y - i][pos.x - i].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}

		}
	}
	if (sarch_dir & 0b1000)
	{
		for (int i = 1;  i < boardSize.x; i++)
		{
			if (!data[pos.y][pos.x - i].expired())
			{
				if (data[pos.y ][pos.x - i].lock()->GetState() == check_piece && i >=2)
				{
					hitDir[sarch_dir] = true;
				}
				else if (i == 1 && data[pos.y][pos.x - i].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}


		}
	}
	if (sarch_dir & 0b1001)
	{
		for (int i = 1; (i < boardSize.y || i < boardSize.x); i++)
		{

			if (!data[pos.y - i][pos.x - i].expired())
			{
				if (data[pos.y - i][pos.x - i].lock()->GetState() == check_piece && i >= 2)
				{
					hitDir[sarch_dir] = true;
				}
				else if (i == 1 && data[pos.y - i][pos.x - i].lock()->GetState() == check_piece)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{

				break;
			}
		}
	}

}

void GameBoard::AddPlayer(int number)
{
	//std::make_shared<Player>();
	playerlist.push_back(std::make_shared<Player>(number));

}

void GameBoard::CurrentPlayerChange()
{
	currentPlayer++;

	if (currentPlayer == playerlist.end())
	{
		currentPlayer = playerlist.begin();
	}
	
	// ���݂̏��Ԃ�\������֐����Ă��
}

player_ptr GameBoard::GetCurrentPlayer()
{
	return (*currentPlayer);
}

piece_ptr GameBoard::AddObjList(piece_ptr && objPtr)
{
	// ������ ���e�����X�g�ɒǉ�
	piecelist.push_back(objPtr);
	//itr�ɒǉ�����piece�̃A�h���X������
	auto itr = piecelist.end();
	itr--;
	return *itr;
}
