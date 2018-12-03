#include "OPRT_CPU.h"
#include "GameTask.h"

#define COM_WAIT_TIME 30


OPRT_CPU::OPRT_CPU()
{
	wait = COM_WAIT_TIME;
}


OPRT_CPU::~OPRT_CPU()
{
}

void OPRT_CPU::Update()
{
	if (wait > 0)
	{
		wait--;
		return;
	}

	if (!lpGameTask.Board)
	{
		return;
	}
	if (!lpCurrentPlayer->CheckChangeTurn())
	{
		lpMouse.SetPos(lpGameTask.Board->SetlistSerch());
		lpMouse.SetClick(0b0001);
		lpMouse.SetOprtType(OPRT_TYPE::MAN);
	}
}
