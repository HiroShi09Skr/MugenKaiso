#include "RoomBase.h"

class RoomCalcLabyrinth : public RoomBase
{
public:
	RoomCalcLabyrinth();			// コンストラクタ
	virtual ~RoomCalcLabyrinth();	// デストラクタ

	void SetSpown(Chara& chara, Camera& cam);		// キャラ・カメラのマップ対応初期化
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	
};
