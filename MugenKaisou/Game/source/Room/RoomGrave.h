#include "RoomBase.h"

class RoomGrave : public RoomBase
{
public:
	RoomGrave();				// インストラクタ
	virtual ~RoomGrave();	// デストラクタ

	void SetSpown(Chara& chara, Camera& cam);		// キャラ・カメラのマップ対応初期化
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	bool flgEffect;

	// ピザ
	Pizza pizza;
	std::vector<Pizza> _vPizza;
};
