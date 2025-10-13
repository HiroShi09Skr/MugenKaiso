#include "../ApplicationGlobal.h"
#include "RoomMuseum.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomMuseum::RoomMuseum() {
	goolDoor.SetVisible(false);
	SaveRoot[5] = 1;
	for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
		gGlobal._vEffekseer[i].DeleteEffect();
		gGlobal._vEffekseer.erase(gGlobal._vEffekseer.begin() + i);
	}

	ClearFlg = false;
}

RoomMuseum::~RoomMuseum() {

}

void RoomMuseum::Process(Chara& chara, VECTOR& v, VECTOR oldv) {
	if (!TalkFlg[13])
	{
		TalkFlg[13] = true;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/museum1.json");
		// ModeGame����̃��C���[�Ƀg�[�N��o�^����
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}

	_isCharaMove = true;	// �L�����͈ړ��������̃t���O
	chara._mapBoxType = 0;
	chara._vNormal.clear();
	// �}�b�v�Ƃ̏Փ˔���
	// ��l���̍��ʒu���牺�����ւ̒���
	for (int i = 0; i < rData._objData.size(); i++) {
		if (rData._objData[i]._objType == 7 && !goolDoor.GetVisible()) { continue; }
		
		// ��l���̍��ʒu���牺�����ւ̒���
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			chara._mapBoxType = 1;
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
		if (VSize(chara._vSlidePos) != 0.f) {
			// �Փ˂���������B
			chara._vSlidePos = VGet(0.f, 0.f, 0.f);
		}
		else {
			// �ǂɓ�����Ȃ������B
		}
	}
	else {
		v = oldv;
	}

	// ������N���A
	if ((CheckHitKey(KEY_INPUT_2)) && gPad[0].gXKey[XINPUT_BUTTON_B] && !ClearFlg)
	{
		ClearFlg = true;
		goolDoor.SetVisible(true);
		gGlobal._effekseer.AddEffect("res/Effect/smoke/smoke.efkefc", 0.0f, 0.0f, 1600.0f, 100, 0.0f);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
		gGlobal._effekseer.AddEffect("res/Effect/doa/doa.efkefc", 0.0f, 250.0f, 1600.0f, -1, 1.6f, 50.0f);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
	}

	// �S�[��
	if (chara._hitObjType == 7 && goolDoor.GetVisible()) {
		chara._mapBoxType = 1;
		chara._flgExit = 1;
		RoomClear[5] = 1;
	}

	for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
		gGlobal._vEffekseer[i].Process();
	}
}

void RoomMuseum::CameraProcess(Camera& cam) {
	// �J�����̓����蔻��
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	// �}�b�v�I�u�W�F�N�g
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomMuseum::Render(VECTOR vPos, bool viewColl) {
	// �}�b�v���f���`��
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer�`��
	{
		gGlobal._effekseer.Render();
	}
}
