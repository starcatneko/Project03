#pragma once

// vC[ÌíÞÉìnð»fÅ«é
// e[uðì¬·é
enum class OPRT_TYPE
{
	MAN,		// vC[ì
	CPU,		// CPUì
	SYS,
	MAX
};

class OPRT_State
{
public:
	virtual ~OPRT_State() = 0;
	virtual void Update() = 0;
	virtual OPRT_TYPE GetOprtType() = 0;
};