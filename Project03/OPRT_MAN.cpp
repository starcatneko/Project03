#include "OPRT_MAN.h"
#include "DxLib.h"
#include "MouseCtr.h"
#include "GameTask.h"

OPRT_MAN::OPRT_MAN()
{
}

OPRT_MAN::~OPRT_MAN()
{
}

OPRT_TYPE OPRT_MAN::GetType()
{
	return OPRT_TYPE::MAN;
}

void OPRT_MAN::Update( MouseCtr &mouse)
{
	//.SetPos;

	int mx, my;
	GetMousePoint(&mx, &my);
	mouse.SetPos({ mx, my });

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
	mouse.SetButton(ST_NEW, flg);

	return;
}
