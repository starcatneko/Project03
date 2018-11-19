#pragma once
#include "OPRT_Base.h"
class OPRT_SYS :
	public OPRT_Base
{
public:
	OPRT_SYS();
	~OPRT_SYS();
	void Update();
	OPRT_TYPE GetOprtType() { return OPRT_TYPE::SYS; }

};

