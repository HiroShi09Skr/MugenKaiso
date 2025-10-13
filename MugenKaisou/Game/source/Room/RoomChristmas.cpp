#include "../ApplicationGlobal.h"
#include "RoomChristmas.h"
#include "../ModeTalk.h"
#include "../ModeRoomNumber.h"

RoomChristmas::RoomChristmas() {
	FullScreenFlg = TRUE;
	SaveRoot[9] = 1;
	_cgBg = LoadGraph("res/UI/kaiwapart.jpg");
	//�^�C���A�b�v�������̉�b�͂��̕����ȍ~�o���Ȃ�
	TalkFlg[3] = TRUE;
}

RoomChristmas::~RoomChristmas() {

}

void RoomChristmas::Process(Chara& chara, VECTOR& v, VECTOR oldv) {
	if (!TalkFlg[12])
	{
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/christmas.json");
		// ModeGame����̃��C���[�Ƀg�[�N��o�^����
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");

		TalkFlg[12] = TRUE;
	}
	chara._vPos = VGet(0, 2000, 0);
}

void RoomChristmas::CameraProcess(Camera& cam) {
	
}

void RoomChristmas::Render(VECTOR vPos, bool viewColl) {
	DrawGraph(0, 0, _cgBg, FALSE); //�w�i
}
