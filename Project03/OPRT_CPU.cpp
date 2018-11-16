#include "OPRT_CPU.h"
#include "MouseCtr.h"
#include "GameTask.h"
OPRT_CPU::OPRT_CPU()
{
}

OPRT_CPU::~OPRT_CPU()
{
}

OPRT_TYPE OPRT_CPU::GetType()
{
	return OPRT_TYPE::CPU;
}

void OPRT_CPU::Update(MouseCtr &mouse)
{
	if (!lpGameTask.Board)
	{
		return;
	}
	mouse.SetPos(lpGameTask.Board->SetListSerch(PIECE_ST::W));
	mouse.SetButton(ST_OLD, 0b0000);
	mouse.SetButton(ST_NEW, 0b0001);



	return ;
}
