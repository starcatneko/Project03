#pragma once
#include "VECTOR2.h"
#include <array>
enum MOUSE_STATE
{
	ST_NEW,
	ST_OLD,
	ST_MAX
};
//using MOUSE_INT std::array<int, ST_MAX>

class MouseCtr
{
public:
	MouseCtr();
	~MouseCtr();
	void Update();
	int GetButton();
	VECTOR2 GetPos();
	int GetButton()	 const;
	VECTOR2 GetPos() const;
	int GetDrag();


private:
	//int button[ST_MAX];
	//std::array<int, ST_MAX> button;
	std::array<int, ST_MAX> button;
	VECTOR2 pos;
};

