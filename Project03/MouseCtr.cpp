#include "MouseCtr.h"
#include "DxLib.h"


// const_castÇÕê‚ëŒÇ…égÇ¡ÇƒÇÕÇ¢ÇØÇ»Ç¢

MouseCtr::MouseCtr()
{
}


MouseCtr::~MouseCtr()
{
}

void MouseCtr::Update()
{
	//mouseCtr.GetBtn()[ST_NOW]
}

int MouseCtr::GetButton()
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
	int mx, my;
	GetMousePoint(&mx, &my);

	return { mx,my };
}

int MouseCtr::GetDrag()
{
	return 0;
}
