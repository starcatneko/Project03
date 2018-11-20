#include "OPRT_MAN.h"
#include "GameTask.h"
#include "Dxlib.h"



OPRT_MAN::OPRT_MAN()
{
}


OPRT_MAN::~OPRT_MAN()
{
}

void OPRT_MAN::Update()
{
	int mx, my;
	GetMousePoint(&mx, &my);
	lpGameTask.Mouse->SetPos({ mx,my });

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
	lpGameTask.Mouse->SetButton(flg);
}
