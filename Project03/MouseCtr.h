#pragma once

#include "VECTOR2.h"
#include <array>
#include <vector>
#include <memory>

#include "OPRT_State.h"

#define lpMouse MouseCtr::GetInstance()
//		
//		

enum MOUSE_STATE
{
	ST_NEW,
	ST_OLD,
	ST_MAX
};
//using MOUSE_INT std::array<int, ST_MAX>

typedef std::shared_ptr<OPRT_State> OPRT_ptr;

class MouseCtr
{
public:
	static MouseCtr &GetInstance()
	{
		return *s_Instance;
	};

	MouseCtr();
	void Init();
	~MouseCtr();
	void Update();
	void SetPos(VECTOR2 pos);
	int GetButton();
	void SetButton(int button);
	// ボタン単押し処理用
	void SetClick(int button);
	VECTOR2 GetPos();

	int GetDrag();
	void SetOprtType(OPRT_TYPE type);
	void SetOprtType(int piece_st);
	OPRT_TYPE GetOprtType();

private:

	struct MouseCtrDeleter
	{
		void operator ()(MouseCtr* MouseCtr) const
		{
			delete MouseCtr;
		}
	};
	static std::unique_ptr<MouseCtr, MouseCtrDeleter> s_Instance;

	OPRT_ptr oprt;
	std::vector<OPRT_TYPE> oprt_tbl;
	std::array<int, ST_MAX> button;
	// waitTimeが0になるまで操作できない
	int waitTimer;
	VECTOR2 pos;
};

