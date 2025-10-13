
#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>
#include "ModeMenu.h"
#include "ModeGameOver.h"
#include "ModeEffekseer.h"
#include "ModeWindow.h"
#include "ModeTalk.h"
#include "ModeRoomNumber.h"
#include "ModeEnding.h"
#include "Room/RoomServer.h"
#include "Sound.h"

// ���[�h
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	// �f�o�b�O�p
	// �R���W����
	bool GetDebugViewColloion() { return _bViewCollision; }
	void SetDebugViewColloion(bool b) { _bViewCollision = b; }
	// �f�o�b�O���
	bool GetDebugViewInfo() { return _bViewInfo; }
	void SetDebugViewInfo(bool b) { _bViewInfo = b; }
	// ���ԕύX1000�b
	int GetDebugTime() { return 60000; }
	void SetDebugTime(int b) { gamecntdown = b; }
	// �����X�L�b�v
	int GetDebugSkip() { return 0; }
	void SetDebugSkip(int b) { gamecntdown = b; }

protected:
	// �C���X�^���X
	//-----------------------------------------------------------------
	Camera	_cam;						// �J����
	Chara _chara;						// �L�����N�^
	RoomServer* Rooms;					// �����i�}�b�v�j
	Sound _sound;						// �T�E���h�iBGM�ESE�j

	Useful USEFUL;
	MyMath mymath;

	// �ϐ�
	//-----------------------------------------------------------------
	int render_texture_handle = -1;		// �e�N�X�`�������_�����O�p
	bool _flgPlay;						// ����\�t���O�iture�F����\, false�F����s�\�j
	bool _flgEffect;					// �G�t�F�N�g�t���O
	int clear_cnt;						// �N���A���J�E���g
	int cgUI;							// UI�摜
	// �������ԉ摜
	int cg_timebg;
	int cg_countNum[10];				//�����̉摜
	int cg_countNum_y[10];				//���F�̐���
	int cgRoomNumber[10];				//�����ԍ�
	//���f��
	// 0:move 1:electsound1
	int se[4];

	// �f�o�b�O�p
	//-----------------------------------------------------------------
	bool _bViewCollision;				// �R���W�����\���E��\��
	bool _bViewInfo;					// �f�o�b�O���\���E��\��
}; 
