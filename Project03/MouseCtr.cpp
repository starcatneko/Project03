#include "MouseCtr.h"
#include "GameTask.h"
#include "DxLib.h"


// const_cast�͐�΂Ɏg���Ă͂����Ȃ�

MouseCtr::MouseCtr()
{
}


MouseCtr::~MouseCtr()
{
}


void MouseCtr::Update(OPRT_TYPE oprt)
{
	if (oprt == OPRT_TYPE::MAN)
	{
		int mx, my;
		GetMousePoint(&mx, &my);
		pos = { mx,my };

		int flg = 0;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			flg += 0b0001;
		}
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
		{
			flg += 0b0010;
		}
		if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
		{
			flg += 0b0100;
		}
		button[ST_NEW] = flg;
	}

	if (oprt == OPRT_TYPE::CPU)
	{
		
		// �u����ꏊ���X�g���Q��
		// ���X�g���̂��ꂼ��̃P�[�X�ŏ�������

		if (!lpGameTask.Board)
		{
			return;
		}
		pos = lpGameTask.Board->SetListSerch(PIECE_ST::W);
		button[ST_OLD] = 0b0000;

		button[ST_NEW] = 0b0001;
		
		// �P�Ƃ�鐔
		// �Q���肪�u����ꏊ�̐�
		// �R�ǍہE�p

		return;
	}

	//mouseCtr.GetBtn()[ST_NOW]
}



void MouseCtr::SetPos(VECTOR2 pos)
{
	MouseCtr::pos = pos;
}

int MouseCtr::GetButton()
{


	if (button[ST_OLD] != button[ST_NEW])
	{
		button[ST_OLD] = button[ST_NEW];
		return button[ST_NEW];
	}
	else
	{
		button[ST_OLD] = button[ST_NEW];
		return 0;
	}
}

VECTOR2 MouseCtr::GetPos()
{
	return { pos };
}

int MouseCtr::GetDrag()
{
	return 0;
}

void MouseCtr::SetOprtType(OPRT_TYPE type)
{
}

OPRT_TYPE MouseCtr::GetOprtType()
{
	//return ;
	return OPRT_TYPE::CPU;
}
