#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// 計算用マクロ
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

#define ANIMMAX	(6)		// 3Dモデルアニメーション最大数

// キャラクター
class Chara {
public:
	// 変数
	//---------------------------------------------------------------------------------------------------------------
	int _handle;					// 3Dモデル描画用
	VECTOR _vPos;					// 位置
	VECTOR _oldvPos;				// 移動前の位置
	VECTOR _vResPos;				// リスポーン位置
	VECTOR _vDir;					// 向き
	float _colSubY;					// コリジョン判定時のY補正(腰位置）
	
	// 3Dモデルコリジョン用カプセル
	float _collLower, _collUpper;	// カプセルの下端点と上端点のY補正
	float _CapsuleR;				// カプセルの幅（半径）
	int CntHitCapsule;				// カプセルと衝突したポリゴン数
	std::vector<VECTOR> _vNormal;	// カプセルと衝突したポリゴンの法線ベクトル
	VECTOR _vSlidePos;				// 衝突回避時の移動量
	
	// キャラクター状態
	enum class STATUS {
		NONE,						// なし
		WAIT,						// 待機（アイドル状態）
		WALK,						// 歩行
		JUMP_START,					// ジャンプ開始
		JUMP_LOOP,					// ジャンプ中（ループ）
		JUMP_DOWN,					// ジャンプ降下
		_EOT_
	};
	STATUS _status;					//	アニメーション状態
	bool _isWait;					// 待機状態か（tureの場合、アニメーション状態はWAIT）
	bool _isDead;					// 死亡したか
	int _flgExit;					// 出口に到着したか
	int _mapBoxType;				// 当たっている床のタイプ
	int _hitObjType;				// 当たっているオブジェクトタイプ

	// ジャンプ用
	int jump_flg;					// ジャンプ状態フラグ（0:ジャンプしていない, 1:ジャンプしている）
	bool _isLanded;					// 着陸してるか
	float _jumpMove;				// ジャンプ移動量
	bool _isJump;					// 着地中、ジャンプできるか
	float gravity;					//重力

	// 3Dモデルアニメーション用
	int _handleAnim[ANIMMAX];		// アニメーション
	int _flgJumpAnim;				// ジャンプアニメーション状態フラグ（0：開始, 1：ループ, 2：降下）
	// アニメーション複数管理クラス
	class Animation {
	public:
		Animation() {}
		virtual ~Animation() {}

		int _attach_index = 0;				// アタッチするアニメーション番号
		float _total_time = 0.0f;			// 総再生時間
		float _play_time = 0.0f;			// 再生時間
		// モーションブレンド用
		float _start_total_time = 6.0f;
		float _start_time = 0.0f;
		float _close_total_time = 0.0f;		// 総閉じ時間
		float _close_time = 0.0f;			// 閉じ時間
	};
	std::vector<Animation*> _vAnim;

	// 関数
	//---------------------------------------------------------------------------------------------------------------
	void Init();																// 初期化
	void Spown(bool flgRespown);												// スポーン設定
	bool isHitWall(int handleMap, int frameMapCollision, bool flgCntNormal);	// 壁との当たり判定
	bool isHitGround(int handleMap, int frameMapCollision);						// 床との当たり判定
	bool AvoidCollision(VECTOR v, int handle, int frameCollision);				// 壁との衝突回避処理
	void CheckStuck(int num);													// キャラが挟まった確認
	void ChangeStatus(VECTOR v);												// キャラクターステータス更新
	void ChangeCharaAnim(STATUS oldStatus);										// キャラクターアニメーション更新
	void Jump();																// ジャンプ処理
	void Render();																// 描画
};
