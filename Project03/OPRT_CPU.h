#pragma once
#include "OPRT_Base.h"
class OPRT_CPU :
	public OPRT_Base
{
public:
	OPRT_CPU();
	~OPRT_CPU();
	void Update();
	OPRT_TYPE GetOprtType() { return OPRT_TYPE::CPU; }
};

