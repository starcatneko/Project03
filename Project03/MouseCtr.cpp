#include "MouseCtr.h"
#include "GameTask.h"
#include "DxLib.h"


// const_castは絶対に使ってはいけない

MouseCtr::MouseCtr()
{
	type = OPRT_TYPE::MAN;
}


MouseCtr::~MouseCtr()
{
}

void MouseCtr::Update()
{
	if (type == OPRT_TYPE::MAN)
	{
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
	if (type == OPRT_TYPE::CPU)
	{
		// 置ける場所リストを参照
		// リスト内のそれぞれのケースで条件分岐
		/*
		pos = lpGameTask.Board->SetListSerch();
		button[ST_OLD] = 0b0000;

		button[ST_NEW] = 0b0001;
		*/
		// １とれる数
		// ２相手が置ける場所の数
		// ３壁際・角


	}

	//mouseCtr.GetBtn()[ST_NOW]
}

void MouseCtr::Update(OPRT_TYPE oprt)
{
	if (oprt == OPRT_TYPE::MAN)
	{
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
		
		// 置ける場所リストを参照
		// リスト内のそれぞれのケースで条件分岐

		if (!lpGameTask.Board)
		{
			return;
		}
		pos = lpGameTask.Board->SetListSerch(PIECE_ST::W);
		button[ST_OLD] = 0b0000;

		button[ST_NEW] = 0b0001;
		
		// １とれる数
		// ２相手が置ける場所の数
		// ３壁際・角


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
	if (type == OPRT_TYPE::MAN)
	{

	int mx, my;
	GetMousePoint(&mx, &my);
	pos = { mx,my };
	return { pos };

	}
	if (type == OPRT_TYPE::CPU)
	{
		return { pos };
	}
}

int MouseCtr::GetDrag()
{
	return 0;
}

void MouseCtr::SetType(OPRT_TYPE type)
{
	MouseCtr::type = type;
}
