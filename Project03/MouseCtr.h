#pragma once

#include "VECTOR2.h"
#include <array>
enum MOUSE_STATE
{
	ST_NEW,
	ST_OLD,
	ST_MAX
};


// vC[ÌíÞÉìnð»fÅ«é
// e[uðì¬·é
enum class OPRT_TYPE
{
	MAN,		// vC[ì
	CPU,		// CPUì
	MAX
};



//using MOUSE_INT std::array<int, ST_MAX>

class MouseCtr
{
public:
	MouseCtr();
	~MouseCtr();
	void Update();
	void Update(OPRT_TYPE oprt);
	void SetPos(VECTOR2 pos);
	int GetButton();
	VECTOR2 GetPos();

	int GetButton()	 const;
	VECTOR2 GetPos() const;
	int GetDrag();

	void SetOprtType(OPRT_TYPE type);
	OPRT_TYPE GetOprtType();


private:
	//int button[ST_MAX];
	//std::array<int, ST_MAX> button;

	std::array<int, ST_MAX> button;
	VECTOR2 pos;
};

