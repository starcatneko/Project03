#include "OPRT_CPU.h"
#include "GameTask.h"




OPRT_CPU::OPRT_CPU()
{
	wait = 30;
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
	}
	lpMouse.SetClick(0b0001); 
	
}
