#pragma once

#include "RoomBase.h"
#include <string>

class RoomServer
{
public:
	RoomServer();			// �R���X�g���N�^
	virtual ~RoomServer();	// �f�X�g���N�^

	void SetSpown(Chara& chara, Camera& cam);				// �X�|�[���ݒ�
	void Reset();											// ���Z�b�g����
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);		// �X�V����
	void CameraProcess(Camera& cam);						// �J�����X�V����
	void Render(VECTOR vPos, bool viewColl);				// �`��
	void ChangeRoom(int key);								// �����؂�ւ�����
};
