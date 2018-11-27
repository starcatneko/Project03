#include "MouseCtr.h"
#include "GameTask.h"
#include "DxLib.h"

#include "OPRT_State.h"
#include "OPRT_MAN.h"
#include "OPRT_CPU.h"
#include "OPRT_SYS.h"

std::unique_ptr<MouseCtr, MouseCtr::MouseCtrDeleter> MouseCtr::s_Instance(new MouseCtr());


// const_castÇÕê‚ëŒÇ…égÇ¡ÇƒÇÕÇ¢ÇØÇ»Ç¢

MouseCtr::MouseCtr()
{
	Init();
}
void MouseCtr::Init()
{
	oprt_tbl.resize(static_cast<int>(PIECE_ST::MAX));

	for (auto unit : PIECE_ST())
	{
		oprt_tbl[unit] = OPRT_TYPE::CPU;
		//oprt_tbl_s[unit] = ;
	}
	oprt_tbl[static_cast<int>(PIECE_ST::NON)] = OPRT_TYPE::SYS;
	//oprt_tbl[static_cast<int>(PIECE_ST::B)] = OPRT_TYPE::MAN;
	//oprt_tbl[static_cast<int>(PIECE_ST::W)] = OPRT_TYPE::MAN;
	//oprt_tbl[1] = OPRT_TYPE::MAN;
	SetOprtType(oprt_tbl[static_cast<int>(PIECE_ST::NON)]);
	waitTimer;
}

MouseCtr::~MouseCtr()
{
}


void MouseCtr::Update()
{
	if (waitTimer > 0)
	{
		waitTimer--;
		return;
	}	
	MouseCtr::oprt->Update();
	button[ST_OLD] = button[ST_NEW];
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

void MouseCtr::SetButton(int button)
{
	MouseCtr::button[ST_NEW] = button;
}
void MouseCtr::SetClick(int button)
{
	MouseCtr::button[ST_OLD] = 0b0000;
	MouseCtr::button[ST_NEW] = button;
}

VECTOR2 MouseCtr::GetPos()
{
	return { pos };
}

int MouseCtr::GetDrag()
{
	return 0;
}

void MouseCtr::SetOprtType(OPRT_TYPE type)
{
	switch (type)
	{
	case OPRT_TYPE::CPU:
		oprt = std::make_shared<OPRT_CPU>();
		break;
	case OPRT_TYPE::SYS:
	case OPRT_TYPE::MAN:
		oprt = std::make_shared<OPRT_MAN>();
		break;
	}
}
void MouseCtr::SetOprtType(int piece_st)
{
	SetOprtType(oprt_tbl[piece_st]);
}
OPRT_TYPE MouseCtr::GetOprtType()
{
	//return ;	
	return oprt->GetOprtType();

}
