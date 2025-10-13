#include "RoomCalcLabyrinth.h"
#include "../ApplicationGlobal.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomCalcLabyrinth::RoomCalcLabyrinth() {
	goolDoor.SetVisible(true);
	//����Ȃ����H
	for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
		gGlobal._vEffekseer[i].DeleteEffect();
		gGlobal._vEffekseer.erase(gGlobal._vEffekseer.begin() + i);
	}
}

RoomCalcLabyrinth::~RoomCalcLabyrinth() {
	
}

void RoomCalcLabyrinth::SetSpown(Chara& chara, Camera& cam) {
	RoomBase::SetSpown(chara, cam);

	// �J����
	cam._vPos = VGet(chara._vPos.x - 800.f, chara._vPos.y + 600.f, chara._vPos.z);
	cam._oldvPos = cam._vPos;
}

void RoomCalcLabyrinth::Process(Chara& chara, VECTOR& v, VECTOR oldv) {
	if (SaveRoot[2] == 0)
	{
		SaveRoot[2] = 1;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/calculation1.json");
		// ModeGame����̃��C���[�Ƀg�[�N��o�^����
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		gGlobal._effekseer.AddEffect("res/Effect/doa/doa.efkefc", 10500.0f, 250.0f, -5750.0f, -1, 0.0f, 50.0f);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
	}
	
	_isCharaMove = true;	// �L�����͈ړ��������̃t���O
	chara._mapBoxType = 0;
	chara._hitObjType = 0;
	chara._vNormal.clear();
	// �}�b�v�Ƃ̏Փ˔���
	for (int i = 0; i < rData._objData.size(); i++) {
		// ��l���̍��ʒu���牺�����ւ̒���
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			chara._mapBoxType = rData._objData[i]._mapType;
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

	// �S�[��
	if (chara._hitObjType == 7) {
		chara._mapBoxType = 1;
		chara._flgExit = 1;
		if (keyRoom == 311) {
			RoomClear[2] = 1;
			//ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/calculation2.json");
			//// ModeGame����̃��C���[�Ƀg�[�N��o�^����
			//ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		}
	}

	for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
		gGlobal._vEffekseer[i].Process();
	}
}

void RoomCalcLabyrinth::CameraProcess(Camera& cam) {
	// �J�����̓����蔻��
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomCalcLabyrinth::Render(VECTOR vPos, bool viewColl) {
	// �}�b�v���f���`��
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer�`��
	{
		gGlobal._effekseer.Render();
	}
}
