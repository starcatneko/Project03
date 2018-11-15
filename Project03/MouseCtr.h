#pragma once

#include "VECTOR2.h"
#include <array>
enum MOUSE_STATE
{
	ST_NEW,
	ST_OLD,
	ST_MAX
};


// プレイヤーの種類毎に操作系統を判断できる
// テーブルを作成する
enum class OPRT_TYPE
{
	MAN,		// プレイヤー操作
	CPU,		// CPU操作
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

	void SetType(OPRT_TYPE type);


private:
	//int button[ST_MAX];
	//std::array<int, ST_MAX> button;

	OPRT_TYPE type;
	std::array<int, ST_MAX> button;
	VECTOR2 pos;
};

