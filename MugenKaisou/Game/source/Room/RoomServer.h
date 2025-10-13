#pragma once

#include "RoomBase.h"
#include <string>

class RoomServer
{
public:
	RoomServer();			// コンストラクタ
	virtual ~RoomServer();	// デストラクタ

	void SetSpown(Chara& chara, Camera& cam);				// スポーン設定
	void Reset();											// リセット処理
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);		// 更新処理
	void CameraProcess(Camera& cam);						// カメラ更新処理
	void Render(VECTOR vPos, bool viewColl);				// 描画
	void ChangeRoom(int key);								// 部屋切り替え処理
};
