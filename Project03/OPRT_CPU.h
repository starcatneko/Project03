#pragma once
#include "OPRT_State.h"
class OPRT_CPU :
	public OPRT_State
{
public:
	OPRT_CPU();
	~OPRT_CPU();
	void Update();
	OPRT_TYPE GetOprtType() { return OPRT_TYPE::CPU; }
	// ëÄçÏÇÃä¥äo
	int wait;
};

