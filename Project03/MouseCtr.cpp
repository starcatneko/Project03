#include "MouseCtr.h"
#include "GameTask.h"
#include "DxLib.h"

#include "OPRT_State.h"
#include "OPRT_MAN.h"
#include "OPRT_CPU.h"
#include "OPRT_SYS.h"
#include "PIECE_ST.h"

std::unique_ptr<MouseCtr, MouseCtr::MouseCtrDeleter> MouseCtr::s_Instance(new MouseCtr());

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
	}
	oprt_tbl[static_cast<int>(PIECE_ST::NON)] = OPRT_TYPE::SYS;
	//oprt_tbl[static_cast<int>(PIECE_ST::B)] = OPRT_TYPE::MAN;
	//oprt_tbl[static_cast<int>(PIECE_ST::W)] = OPRT_TYPE::MAN;
	SetOprtType(oprt_tbl[static_cast<int>(PIECE_ST::NON)]);
}

MouseCtr::~MouseCtr()
{
}


void MouseCtr::Update()
{
	button[ST_OLD] = button[ST_NEW];
	MouseCtr::oprt->Update();
	//DrawFormatString(lpMouse.GetPos().x, lpMouse.GetPos().y, 0xFFFF00, "��������");
	
	if (GetButton() != 0)
	{
		DrawCircle(lpMouse.GetPos().x, lpMouse.GetPos().y,
			12,0xffff00, true, 3);
	}
	
	VECTOR2 mp = { 0,420 };

}

int MouseCtr::GetButton()
{
	if (button[ST_OLD] != button[ST_NEW])
	{
		//button[ST_OLD] = button[ST_NEW];
		return button[ST_NEW];
	}
	else
	{
		button[ST_OLD] = button[ST_NEW];
		return 0;
	}
}

void MouseCtr::SetClick(int button)
{
	MouseCtr::button[ST_OLD] = 0b0000;
	MouseCtr::button[ST_NEW] = button;
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
OPRT_TYPE MouseCtr::GetOprtType()
{
	return oprt->GetOprtType();
}

OPRT_TYPE MouseCtr::GetOprtTbl(PIECE_ST color)
{
	return oprt_tbl[static_cast<int>(color)];
}

void MouseCtr::ChangeOprtTbl(PIECE_ST color)
{
	int num = static_cast<int>(color);

	switch (oprt_tbl[num])
	{
	case OPRT_TYPE::CPU:
		oprt_tbl[num] = OPRT_TYPE::MAN;
		break;
	case OPRT_TYPE::MAN:
		oprt_tbl[num] = OPRT_TYPE::CPU;
		break;
	default:
		break;
	}		
	SetOprtType(oprt_tbl[num]);
}
