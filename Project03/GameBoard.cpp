#include "GameBoard.h"
#include "GamePiece.h"
#include "Dxlib.h"
#include "Player.h"
#include "GameTask.h"


const int CHIPSIZE = 64;
#define BoardSize int(8)

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600
#define SCREEN_HALF_X SCREEN_SIZE_X/2
#define SCREEN_HALF_Y SCREEN_SIZE_Y/2
#define X_DIS (int)((SCREEN_SIZE_X / 2) - (boardSize.x / 2)*CHIPSIZE)
#define Y_DIS (int)((SCREEN_SIZE_Y / 2) - (boardSize.y / 2)*CHIPSIZE)


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
	gameEndFlg = false;
	int pl_cnt = 0;
	while (pl_cnt < PL_MAX)
	{
		// �֐���pl_cnt�����Z�����鏈����g�ݍ��񂾂�Z�k�\
		AddPlayer(pl_cnt);
		pl_cnt++;
	}

	SetPiece({ 0,3 }, PIECE_W);
	SetPiece({ 0,0 }, PIECE_W);
	SetPiece({ 0,2 }, PIECE_W);
	SetPiece({ 0,1 }, PIECE_W);
	SetPiece({ 1,3 }, PIECE_B);
	SetPiece({ 1,0 }, PIECE_B);
	SetPiece({ 1,2 }, PIECE_B);
	SetPiece({ 1,1 }, PIECE_B);

	currentPlayer = playerlist.begin();
	CurrentPlPiece = std::make_unique<GamePiece>(VECTOR2{ 9,0 }, VECTOR2{ X_DIS,Y_DIS }, PIECE_B);
	return true;
}

VECTOR2 GameBoard::Pos_MouseToBoard(VECTOR2 mousePos)
{
	int setPosX = mousePos.x - X_DIS;
	int setPosY = mousePos.y - Y_DIS;
	return{ setPosX /= CHIPSIZE, setPosY /= CHIPSIZE };
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

void GameBoard::ChangeStone(VECTOR2 pos)
{
	for (int y = -1; y <= 1; y++)
	{

		for (int x = -1; x <= 1; x++)
		{

		}

	}

}

void GameBoard::Debug_SetPiece(VECTOR2 pos)
{
	VECTOR2 vec = { Pos_MouseToBoard(pos)};

	piece_ptr tmp = AddObjList(std::make_shared<GamePiece>(pos, vec, (*currentPlayer)->GetType()));
	data[pos.y][pos.x] = (tmp);
	data[pos.y][pos.x].lock()->SetState((*currentPlayer)->GetType());
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
	VECTOR2 vec1 = Pos_MouseToBoard(pos);

	bool plChangeFlg = false;
	// �}�E�X�ŃN���b�N�����ӏ����Ֆʂ̊O�̏ꍇ�A���̏����͍s��Ȃ�
	if (vec1.x >= 0 && vec1.y >= 0
		&& vec1.x <  boardSize.x
		&& vec1.y < boardSize.y)
	{

		VECTOR2 vec2 = { X_DIS,Y_DIS };

		VECTOR2 sarchTBL[8] = { { 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 }, };


		if (data[vec1.y][vec1.x].expired())
		{
			for (auto itr : sarchTBL)
			{

				// �����Ɍ������ĂЂ�����Ԃ��֐�

				if(SarchReverse(vec1, itr, (*currentPlayer)->GetType()))
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
						lastset = (*currentPlayer)->GetNo();
						plChangeFlg = true;


					}

				}
			}
		}
		else
		{
			return;
		}
		if (plChangeFlg)
		{
			// �N�����u�����Ԃ̏ꍇ
			CurrentPlayerChange();
		}

	}
}

void GameBoard::DB_TouchBoad()
{

}

void GameBoard::Update()
{
	Draw();
	if (gameEndFlg)
	{
		std::string str1;
		str1 = "WINNER PLAYER";
		SetFontSize(48);

		//GetDrawStringWidth(str1.c_str(),strlen(str1.c_str()))
		DrawFormatString(
			SCREEN_HALF_X - GetDrawStringWidth(str1.c_str(), strlen(str1.c_str()))/2,
			320, 0xFF4444, str1.c_str(), (*currentPlayer)->GetNo());

		SetFontSize(10);
	}
}

bool GameBoard::Reverse(VECTOR2 pos, VECTOR2 vec)
{
	// i����
	VECTOR2 sarchPos = pos + (vec);
	if (data[sarchPos.y][sarchPos.x].lock()->GetState() != (*currentPlayer)->GetType())
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

		// �T�[�`����}�X���Ֆʂ̊O�ɂ͂ݏo���Ă��Ȃ����̃`�F�b�N
		if (sarchPos.x < 0 || sarchPos.y < 0 ||
			sarchPos.x >= data.size() || sarchPos.y >= data.size()
			)
		{
			return false;
		}

		// �T�[�`�ʒu�ɋ�z�u����Ă��邩
		if (!data[sarchPos.y][sarchPos.x].expired())
		{
			// ��z�u����Ă����ꍇ�A���̋�v���C���[�̋�ƈ�v���邩
			if (data[sarchPos.y][sarchPos.x].lock()->GetState() == st)
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
	// ������ ���e�����X�g��f�ǉ�
	piecelist.push_back(objPtr);
	//itr�ɒǉ�����piece�̃A�h���X������
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
		pieceCnt[(itr->GetState())-1]++;
	}
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

	VECTOR2 CurrntPlPos = CurrentPlPiece->GetPos();

	// -----���݂̃v���C���[�\��
	CurrentPlPiece->SetState((*currentPlayer)->GetType());
	
	DrawBox(CurrntPlPos.x*CHIPSIZE + X_DIS, CurrntPlPos.y*CHIPSIZE + Y_DIS
		, CurrntPlPos.x*CHIPSIZE + CHIPSIZE + X_DIS,
		CurrntPlPos.y*CHIPSIZE + CHIPSIZE + Y_DIS, 0x006600, true);

	CurrentPlPiece->Draw();

	if (gameEndFlg != true)
	{
		CurrentSetUpData();
	}

	// ���݂̔Ԃ̃v���C���[��\������

	for (auto itr : piecelist)
	{
		itr->Draw();
		DrawFormatString(0, 48, 0xdddddd, "�%d", piecelist.size());
	}

	DrawFormatString(0, 64, 0xdddddd, "�v���C���[��%d", playerlist.size());
	DrawFormatString(0, 96, 0xdddddd, "���݂̃v���C���[\n%d", (*currentPlayer)->GetNo());

}


void GameBoard::CurrentSetUpData()
{
	VECTOR2 sarchTBL[8] = { { 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 }, };
	
	// �ݒu�\�ȃ^�C���̐�
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

				if (SarchReverse(drawPos, vec_itr2, (*currentPlayer)->GetType())
					&& data[drawPos.y][drawPos.x].expired())
				{
					tilecnt++;
					DrawBox(drawPos.x*CHIPSIZE + X_DIS, drawPos.y*CHIPSIZE + Y_DIS
						, drawPos.x*CHIPSIZE + CHIPSIZE + X_DIS,
						drawPos.y*CHIPSIZE + CHIPSIZE + Y_DIS, 0xaadd00, true);
				}
			}
		}
	}

	// �ݒu�\�ȃ^�C���������ꍇ
	if (tilecnt == 0)
	{
		// �ݒu�ł���v���C���[����l�����Ȃ��ꍇ
		if (lastset == (*currentPlayer)->GetNo())
		{
			GameTask::GetInstance().GameEnd();
			this->GameEnd();
			gameEndFlg = true;
			return;
		}
		CurrentPlayerChange();
	}

}