#pragma once
#include "OPRT_Base.h"
class OPRT_MAN :
	public OPRT_Base
{
public:
	OPRT_MAN();
	~OPRT_MAN();	
	void Update();
	OPRT_TYPE GetOprtType() { return OPRT_TYPE::MAN; }

};

