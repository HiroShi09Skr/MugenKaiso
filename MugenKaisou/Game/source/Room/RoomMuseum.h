#include "RoomBase.h"

class RoomMuseum : public RoomBase
{
public:
	RoomMuseum();				// �C���X�g���N�^
	virtual ~RoomMuseum();	// �f�X�g���N�^

	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
private:
	bool ClearFlg;
	
};
