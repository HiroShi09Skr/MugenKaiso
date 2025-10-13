#include "RoomBase.h"

class RoomCalcHighLevel : public RoomBase
{
public:
	RoomCalcHighLevel();			// �C���X�g���N�^
	virtual ~RoomCalcHighLevel();	// �f�X�g���N�^

	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	// �x���g�R���x�A
	BeltConveyor beltConv;
};
