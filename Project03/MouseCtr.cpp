#include "MouseCtr.h"
#include "GameTask.h"
#include "DxLib.h"


// const_castは絶対に使ってはいけない

MouseCtr::MouseCtr()
{
}


MouseCtr::~MouseCtr()
{
}

void MouseCtr::Update()
{
	if (type == OPRT_TYPE::OPRT_MAN)
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
	if (type == OPRT_TYPE::OPRT_CPU)
	{
		// 置ける場所リストを参照
		// リスト内のそれぞれのケースで条件分岐




		// １とれる数
		// ２相手が置ける場所の数
		// ３壁際・角

	}

	//mouseCtr.GetBtn()[ST_NOW]
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
	if (type == OPRT_TYPE::OPRT_MAN)
	{

	int mx, my;
	GetMousePoint(&mx, &my);
	pos = { mx,my };
	return { pos };

	}
	if (type == OPRT_TYPE::OPRT_CPU)
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
