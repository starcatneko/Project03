#pragma once

// �v���C���[�̎�ޖ��ɑ���n���𔻒f�ł���
// �e�[�u�����쐬����
enum class OPRT_TYPE
{
	MAN,		// �v���C���[����
	CPU,		// CPU����
	SYS,
	MAX
};

class OPRT_State
{
public:
	virtual ~OPRT_State() = 0;
	virtual void Update() = 0;
	virtual OPRT_TYPE GetOprtType() = 0;
};