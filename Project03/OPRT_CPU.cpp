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
	lpGameTask.Mouse->SetPos(lpGameTask.Board->SetlistSerch());
	
	lpGameTask.Mouse->SetClick(0b0001); lpGameTask.Mouse->SetButton(0b0001);


}
