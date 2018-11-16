#pragma once

#include <memory>

class MouseCtr;

// �v���C���[�̎�ޖ��ɑ���n���𔻒f�ł���
// �e�[�u�����쐬����
enum class OPRT_TYPE
{
	MAN,		// �v���C���[����
	CPU,		// CPU����
	MAX
};

struct OPRT_Base
{
public:
	virtual ~OPRT_Base();
	virtual OPRT_TYPE GetType() = 0;
	virtual void Update( MouseCtr &mouse) = 0;
};