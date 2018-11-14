#pragma once
#include "VECTOR2.h"
#include <array>
enum MOUSE_STATE
{
	ST_NEW,
	ST_OLD,
	ST_MAX
};

enum class OPRT_TYPE
{
	OPRT_MAN,		// �v���C���[����
	OPRT_CPU,		// CPU����
	OPRT_MAX
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

	void SetType(OPRT_TYPE type);


private:
	//int button[ST_MAX];
	//std::array<int, ST_MAX> button;

	OPRT_TYPE type;

	std::array<int, ST_MAX> button;
	VECTOR2 pos;
};

