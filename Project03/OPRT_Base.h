#pragma once


// プレイヤーの種類毎に操作系統を判断できる
// テーブルを作成する
enum class OPRT_TYPE
{
	MAN,		// プレイヤー操作
	CPU,		// CPU操作
	SYS,
	MAX
};


class OPRT_Base
{
public:
	virtual ~OPRT_Base() = 0;
	virtual void Update() = 0;
	virtual OPRT_TYPE GetOprtType() = 0;
};