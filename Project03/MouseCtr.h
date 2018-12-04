#pragma once

#include "VECTOR2.h"
#include <array>
#include <vector>
#include <memory>

#include "OPRT_State.h"

#define lpMouse MouseCtr::GetInstance()
//		
//		
enum class PIECE_ST;

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
	~MouseCtr();
	void Init();
	void Update();
	void SetPos(VECTOR2 pos)	{ MouseCtr::pos = pos;}
	VECTOR2 GetPos()	{ return { pos };}

	int GetButton();
	void SetButton(int button)	{ MouseCtr::button[ST_NEW] = button;}
	// ボタン単押し処理用
	void SetClick(int button);
	void SetOprtType(OPRT_TYPE type);
	void SetOprtType(int piece_st)	{ SetOprtType(oprt_tbl[piece_st]);}
	OPRT_TYPE GetOprtType();
	// 引数colorに対応したoprt_tblの値を返す
	OPRT_TYPE GetOprtTbl(PIECE_ST color);

	void ChangeOprtTbl(PIECE_ST color);

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
	VECTOR2 pos;
};

