#include "RoomBase.h"

class RoomMuseum : public RoomBase
{
public:
	RoomMuseum();				// インストラクタ
	virtual ~RoomMuseum();	// デストラクタ

	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
private:
	bool ClearFlg;
	
};
