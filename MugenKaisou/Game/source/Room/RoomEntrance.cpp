#include "../ApplicationGlobal.h"
#include "RoomEntrance.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"
#include "../ModeEnding.h"
#include "../ModeWindow.h"

RoomEntrance::RoomEntrance() {
	SaveRoot[0] = 1;
	TalkFlg[12] = TRUE;
	goolDoor.SetVisible(false);
	flgEffect = true;
	for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
		gGlobal._vEffekseer[i].DeleteEffect();
		gGlobal._vEffekseer.erase(gGlobal._vEffekseer.begin() + i);
	}
}

RoomEntrance::~RoomEntrance() {
	
}

void RoomEntrance::SetSpown(Chara& chara, Camera& cam) {
	RoomBase::SetSpown(chara, cam);
	
	// カメラ
	// 初期カメラのみ後ろを向きたいのでZ＋800
	cam._vPos = VGet(chara._vPos.x, chara._vPos.y + 600.f, chara._vPos.z + 800.f);
	cam._oldvPos = cam._vPos;
}

void RoomEntrance::Process(Chara& chara, VECTOR& v, VECTOR oldv) {
	if (RoomClear[0] == 0 && TalkFlg[12])
	{
		TalkFlg[12] = FALSE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entrance1.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	else if (RoomClear[0] == 1 && TalkFlg[12])
	{
		TalkFlg[12] = FALSE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entranceend.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		ModeEnding* modeEnding = new ModeEnding();
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modeEnding, 150, "ending");
	}
	_isCharaMove = true;	// キャラは移動したかのフラグ
	chara._mapBoxType = 0;
	chara._vNormal.clear();
	// マップとの衝突判定
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
			chara._vSlidePos = VGet(0.f, 0.f, 0.f);
		}
		else {
			// 壁に当たらなかった。
		}
	}
	else {
		v = oldv;
	}

	if (TalkFlg[10] && !TalkFlg[11]) {
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		TalkFlg[11] = TRUE;
		FullScreenFlg = FALSE;
		ModeWindow* modewindow = new ModeWindow();
		// ModeGameより上のレイヤーにウィンドウを登録する
		ModeServer::GetInstance()->Add(modewindow, 100, "window");
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entrance3.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");

		gGlobal._effekseer.AddEffect("res/Effect/doa/doa.efkefc", 0.0f, 1250.0f, 3200.0f, -1, 1.6f, 50.0f);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
	}

	// タブレット獲得
	if (mymath.IsHitPointBox(chara._vPos, 0.0f, 0.0f, 200.f, 200.f) && !TalkFlg[10]) {

		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entrance2.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		TalkFlg[10] = TRUE;
		goolDoor.SetVisible(true);
		for (int i = 0; i < gGlobal._vEffekseer.size(); i++) {
			gGlobal._vEffekseer.erase(gGlobal._vEffekseer.begin() + i);
		}
	}

	// ゴール
	if (chara._hitObjType == 7 && goolDoor.GetVisible()) {
		chara._mapBoxType = 1;
		chara._flgExit = 1;
		RoomClear[0] = 1;
	}

	if (flgEffect) {
		gGlobal._effekseer.AddEffect("res/Effect/hikari/sekibannohikari.efkefc", 0.0f, 0.0f, 0.0f, -1);
		gGlobal._vEffekseer.push_back(gGlobal._effekseer);
		flgEffect = 0;
	}
}

void RoomEntrance::CameraProcess(Camera& cam) {
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

void RoomEntrance::Render(VECTOR vPos, bool viewColl) {
	// マップモデル描画
	RenderObjectModel();
	//effekseer描画
	{
		gGlobal._effekseer.Render();
	}
	//MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	//MV1DrawModel(rData._handleSkySphere);
}
