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
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}

	_isCharaMove = true;	// キャラは移動したかのフラグ
	chara._mapBoxType = 0;
	chara._vNormal.clear();
	// マップとの衝突判定
	// 主人公の腰位置から下方向への直線
	for (int i = 0; i < rData._objData.size(); i++) {
		if (rData._objData[i]._objType == 7 && !goolDoor.GetVisible()) { continue; }
		
		// 主人公の腰位置から下方向への直線
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			chara._mapBoxType = 1;
		}
		// 主人公（カプセル）と壁の当たり判定
		if (chara.isHitWall(rData._objData[i]._handle, rData._objData[i]._frameCollision, true)) {
			// 壁に当たった。
			chara._hitObjType = rData._objData[i]._objType;
			// 元の座標に戻す
			chara._vPos = chara._oldvPos;
			// 衝突回避
			if (chara.AvoidCollision(v, rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
				_isCharaMove = true;
			}
			else {
				_isCharaMove = false;
			}
		}
	}

	if (_isCharaMove) {
		// カメラ移動
		if (VSize(chara._vSlidePos) != 0.f) {
			// 衝突を回避した。
			chara._vSlidePos = VGet(0.f, 0.f, 0.f);
		}
		else {
			// 壁に当たらなかった。
		}
	}
	else {
		v = oldv;
	}

	// 謎解きクリア
	if ((CheckHitKey(KEY_INPUT_2)) && gPad[0].gXKey[XINPUT_BUTTON_B] && !ClearFlg)
	{
		ClearFlg = true;
		goolDoor.SetVisible(true);
		gGlobal._effekseer.AddEffect("res/Effect/smoke/smoke.efkefc", 0.0f, 0.0f, 1600.0f, 100, 0.0f);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
		gGlobal._effekseer.AddEffect("res/Effect/doa/doa.efkefc", 0.0f, 250.0f, 1600.0f, -1, 1.6f, 50.0f);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
	}

	// ゴール
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
	// カメラの当たり判定
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	// マップオブジェクト
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomMuseum::Render(VECTOR vPos, bool viewColl) {
	// マップモデル描画
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer描画
	{
		gGlobal._effekseer.Render();
	}
}
