#pragma once

#include "VECTOR2.h"
#include "OPRT_Base.h"
#include <memory>
#include <array>

struct OPRT_Base;

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
	void SetButton(MOUSE_STATE button,int flg);
	VECTOR2 GetPos();
	int GetButton()	 const;
	VECTOR2 GetPos() const;

	OPRT_TYPE GetOprtType();
	void SetOprtType(OPRT_TYPE type);

	int GetDrag();


private:
	//int button[ST_MAX];
	//std::array<int, ST_MAX> button;

	//OPRT_TYPE type;
	std::array<int, ST_MAX> button;
	std::unique_ptr<OPRT_Base> oprt_state;

	VECTOR2 pos;
};

