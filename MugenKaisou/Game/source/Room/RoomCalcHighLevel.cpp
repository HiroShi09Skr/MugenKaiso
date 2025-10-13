#include "RoomCalcHighLevel.h"
#include "../ApplicationGlobal.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomCalcHighLevel::RoomCalcHighLevel() {
	goolDoor.SetVisible(true);
	for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
		gGlobal._vEffekseer[i].DeleteEffect();
		gGlobal._vEffekseer.erase(gGlobal._vEffekseer.begin() + i);
	}
}

RoomCalcHighLevel::~RoomCalcHighLevel() {

}

void RoomCalcHighLevel::Process(Chara& chara, VECTOR& v, VECTOR oldv) {
	if (SaveRoot[7] == 0) {
		SaveRoot[7] = 1;
		gGlobal._effekseer.AddEffect("res/Effect/doa/doa.efkefc", 5000.0f, 250.0f, -500.0f, -1, 1.6f, 50.0f);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
	}
	// �ݒu�u���b�N�ʑ���
	if (chara.jump_flg == 0) {
		if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
			chara._mapBoxType == 4 || chara._mapBoxType == 5) {
			// �x���g�R���x�A
			// �L�����ړ�
			chara._vPos = chara._oldvPos;
			beltConv.MovePos(chara._vPos, chara._mapBoxType, 32.0f);
		}
		else if (chara._hitObjType == 7 && gChangeDoor == 0) {
			// �S�[��
			chara._mapBoxType = 1;
			chara._flgExit = 1;
			RoomClear[7] = 1;
		}
		else if (chara._hitObjType == 7 && gChangeDoor == 1) {
			// �S�[��
			chara._mapBoxType = 1;
			chara._flgExit = 1;
			gGlobal.keyNextRoom = 2126;
			RoomClear[7] = 1;
			//keyRoom = 2126;
		}
	}
	
	_isCharaMove = true;	// �L�����͈ړ��������̃t���O
	chara._mapBoxType = 0;
	chara._hitObjType = 0;
	chara._vNormal.clear();
	// �}�b�v�Ƃ̏Փ˔���
	for (int i = 0; i < rData._objData.size(); i++) {
		// ��l���̍��ʒu���牺�����ւ̒���
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			// �x���g�R���x�A����
			chara._mapBoxType = rData._objData[i]._mapType;
			if (chara._mapBoxType >= 2 && chara._mapBoxType <= 5) {
				// �x���g�R���x�A��ɒ��n���Ă�����W�����v�ł��Ȃ�
				chara._isJump = false;
			}
		}
		// ��l���i�J�v�Z���j�ƕǂ̓����蔻��
		if (chara.isHitWall(rData._objData[i]._handle, rData._objData[i]._frameCollision, true)) {
			// �ǂɓ��������B
			chara._hitObjType = rData._objData[i]._objType;
			// ���̍��W�ɖ߂�
			chara._vPos = chara._oldvPos;
			// �Փˉ��
			if (chara.AvoidCollision(v, rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
				_isCharaMove = true;
			}
			else {
				_isCharaMove = false;
			}
		}
	}

	if (_isCharaMove) {
		// �J�����ړ�
		if ((chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
			chara._mapBoxType == 4 || chara._mapBoxType == 5)
			&& chara.jump_flg == 0) {
			// �x���g�R���x�A
		}
		else {
			// �ʏ�
			if (VSize(chara._vSlidePos) != 0.f) {
				// �Փ˂���������B
				chara._vSlidePos = VGet(0.f, 0.f, 0.f);
			}
			else {
				// �ǂɓ�����Ȃ������B
			}
		}
	}
	else {
		v = oldv;
	}

	// �x���g�R���x�A��ł̓A�j���[�V������WAIT�ɂ���
	if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
		chara._mapBoxType == 4 || chara._mapBoxType == 5) {
		if (chara.jump_flg == 0) {
			chara._isWait = true;
		}
	}
	else { chara._isWait = false; }

	// �h�A�؂�ւ�
	// �f�o�b�O�p
	if (gPad[0].gXTrg[XINPUT_BUTTON_X]) {
		if (gChangeDoor == 0) { gChangeDoor = 1; }
		else if (gChangeDoor == 1) { gChangeDoor = 0; }
	}
	goolDoor.ChangeDoor(gChangeDoor);
	for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
		gGlobal._vEffekseer[i].Process();
	}
}

void RoomCalcHighLevel::CameraProcess(Camera& cam) {
	// �J�����̓����蔻��
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomCalcHighLevel::Render(VECTOR vPos, bool viewColl) {
	// �}�b�v���f���`��
	for (int i = 0; i < rData._objData.size(); i++) {
		MV1SetPosition(rData._objData[i]._handle, rData._objData[i]._vPos);
		//MV1DrawModel(_objData[i]._handle);
		if (rData._objData[i]._objType == 7 || rData._objData[i]._objType == 8) {
			if (rData._objData[i]._objType == goolDoor.GetDoorType()) {
				MV1DrawModel(rData._objData[i]._handle);
			}
		}
		else {
			MV1DrawModel(rData._objData[i]._handle);
		}
	}

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer�`��
	{
		gGlobal._effekseer.Render();
	}
}
