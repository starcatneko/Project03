#pragma once
#include "OPRT_Base.h"

struct OPRT_MAN:
	public OPRT_Base
{
	OPRT_MAN();
	~OPRT_MAN();
	virtual OPRT_TYPE GetType();
	virtual void Update( MouseCtr &mouse);
};