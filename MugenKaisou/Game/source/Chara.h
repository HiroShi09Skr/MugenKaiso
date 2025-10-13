#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// �v�Z�p�}�N��
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

#define ANIMMAX	(6)		// 3D���f���A�j���[�V�����ő吔

// �L�����N�^�[
class Chara {
public:
	// �ϐ�
	//---------------------------------------------------------------------------------------------------------------
	int _handle;					// 3D���f���`��p
	VECTOR _vPos;					// �ʒu
	VECTOR _oldvPos;				// �ړ��O�̈ʒu
	VECTOR _vResPos;				// ���X�|�[���ʒu
	VECTOR _vDir;					// ����
	float _colSubY;					// �R���W�������莞��Y�␳(���ʒu�j
	
	// 3D���f���R���W�����p�J�v�Z��
	float _collLower, _collUpper;	// �J�v�Z���̉��[�_�Ə�[�_��Y�␳
	float _CapsuleR;				// �J�v�Z���̕��i���a�j
	int CntHitCapsule;				// �J�v�Z���ƏՓ˂����|���S����
	std::vector<VECTOR> _vNormal;	// �J�v�Z���ƏՓ˂����|���S���̖@���x�N�g��
	VECTOR _vSlidePos;				// �Փˉ�����̈ړ���
	
	// �L�����N�^�[���
	enum class STATUS {
		NONE,						// �Ȃ�
		WAIT,						// �ҋ@�i�A�C�h����ԁj
		WALK,						// ���s
		JUMP_START,					// �W�����v�J�n
		JUMP_LOOP,					// �W�����v���i���[�v�j
		JUMP_DOWN,					// �W�����v�~��
		_EOT_
	};
	STATUS _status;					//	�A�j���[�V�������
	bool _isWait;					// �ҋ@��Ԃ��iture�̏ꍇ�A�A�j���[�V������Ԃ�WAIT�j
	bool _isDead;					// ���S������
	int _flgExit;					// �o���ɓ���������
	int _mapBoxType;				// �������Ă��鏰�̃^�C�v
	int _hitObjType;				// �������Ă���I�u�W�F�N�g�^�C�v

	// �W�����v�p
	int jump_flg;					// �W�����v��ԃt���O�i0:�W�����v���Ă��Ȃ�, 1:�W�����v���Ă���j
	bool _isLanded;					// �������Ă邩
	float _jumpMove;				// �W�����v�ړ���
	bool _isJump;					// ���n���A�W�����v�ł��邩
	float gravity;					//�d��

	// 3D���f���A�j���[�V�����p
	int _handleAnim[ANIMMAX];		// �A�j���[�V����
	int _flgJumpAnim;				// �W�����v�A�j���[�V������ԃt���O�i0�F�J�n, 1�F���[�v, 2�F�~���j
	// �A�j���[�V���������Ǘ��N���X
	class Animation {
	public:
		Animation() {}
		virtual ~Animation() {}

		int _attach_index = 0;				// �A�^�b�`����A�j���[�V�����ԍ�
		float _total_time = 0.0f;			// ���Đ�����
		float _play_time = 0.0f;			// �Đ�����
		// ���[�V�����u�����h�p
		float _start_total_time = 6.0f;
		float _start_time = 0.0f;
		float _close_total_time = 0.0f;		// ��������
		float _close_time = 0.0f;			// ������
	};
	std::vector<Animation*> _vAnim;

	// �֐�
	//---------------------------------------------------------------------------------------------------------------
	void Init();																// ������
	void Spown(bool flgRespown);												// �X�|�[���ݒ�
	bool isHitWall(int handleMap, int frameMapCollision, bool flgCntNormal);	// �ǂƂ̓����蔻��
	bool isHitGround(int handleMap, int frameMapCollision);						// ���Ƃ̓����蔻��
	bool AvoidCollision(VECTOR v, int handle, int frameCollision);				// �ǂƂ̏Փˉ������
	void CheckStuck(int num);													// �L���������܂����m�F
	void ChangeStatus(VECTOR v);												// �L�����N�^�[�X�e�[�^�X�X�V
	void ChangeCharaAnim(STATUS oldStatus);										// �L�����N�^�[�A�j���[�V�����X�V
	void Jump();																// �W�����v����
	void Render();																// �`��
};
