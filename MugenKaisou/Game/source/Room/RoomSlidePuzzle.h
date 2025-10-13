#include "RoomBase.h"

class RoomSlidePuzzle : public RoomBase
{
public:
	RoomSlidePuzzle();				// インストラクタ
	virtual ~RoomSlidePuzzle();	// デストラクタ

	void SetSpown(Chara& chara, Camera& cam);		// キャラ・カメラのマップ対応初期化
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	// ずらせるブロックとオブジェクト
	ShiftBlock _shiftBlock;
	std::vector<ShiftBlock> _vShiftBlock;
};
