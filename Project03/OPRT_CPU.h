#pragma once

#include "OPRT_Base.h"

struct OPRT_CPU :
	public OPRT_Base
{
	OPRT_CPU();
	~OPRT_CPU();
	virtual OPRT_TYPE GetType();
	virtual void Update( MouseCtr &mouse);

};