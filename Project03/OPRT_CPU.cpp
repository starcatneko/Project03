#include "OPRT_CPU.h"
#include "GameTask.h"




OPRT_CPU::OPRT_CPU()
{
}


OPRT_CPU::~OPRT_CPU()
{
}

void OPRT_CPU::Update()
{
	if (!lpGameTask.Board)
	{
		return;
	}
	if (!(*lpGameTask.currentPlayer)->CheckChangeTurn())
	{
		lpMouse.SetPos(lpGameTask.Board->SetlistSerch());
		lpMouse.SetOprtType(0);
	}


	lpMouse.SetClick(0b0001); 
	
}
