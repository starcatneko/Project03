#pragma once

#include "VECTOR2.h"
#include <array>
#include <memory>

#include "OPRT_State.h"

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
	std::shared_ptr<OPRT_State> oprt;

	std::array<int, ST_MAX> button;
	VECTOR2 pos;
};

