#pragma once
#include "OPRT_State.h"
class OPRT_MAN :
	public OPRT_State
{
public:
	OPRT_MAN();
	~OPRT_MAN();	
	void Update();
	OPRT_TYPE GetOprtType() { return OPRT_TYPE::MAN; }

};

