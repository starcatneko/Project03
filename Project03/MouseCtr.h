#pragma once

#include "VECTOR2.h"
#include <array>
enum MOUSE_STATE
{
	ST_NEW,
	ST_OLD,
	ST_MAX
};


// �v���C���[�̎�ޖ��ɑ���n���𔻒f�ł���
// �e�[�u�����쐬����
enum class OPRT_TYPE
{
	MAN,		// �v���C���[����
	CPU,		// CPU����
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

