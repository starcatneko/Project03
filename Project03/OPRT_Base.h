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


class OPRT_Base
{
public:
	virtual ~OPRT_Base() = 0;
	virtual void Update() = 0;
	virtual OPRT_TYPE GetOprtType() = 0;
};