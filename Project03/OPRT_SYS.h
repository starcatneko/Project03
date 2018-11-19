#pragma once
#include "OPRT_State.h"
class OPRT_SYS :
	public OPRT_State
{
public:
	OPRT_SYS();
	~OPRT_SYS();
	void Update();
	OPRT_TYPE GetOprtType() { return OPRT_TYPE::SYS; }

};

