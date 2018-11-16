#pragma once

#include <memory>

class MouseCtr;

// プレイヤーの種類毎に操作系統を判断できる
// テーブルを作成する
enum class OPRT_TYPE
{
	MAN,		// プレイヤー操作
	CPU,		// CPU操作
	MAX
};

struct OPRT_Base
{
public:
	virtual ~OPRT_Base();
	virtual OPRT_TYPE GetType() = 0;
	virtual void Update( MouseCtr &mouse) = 0;
};