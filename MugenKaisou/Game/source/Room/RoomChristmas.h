#include "RoomBase.h"

class RoomChristmas : public RoomBase
{
public:
	RoomChristmas();				// �C���X�g���N�^
	virtual ~RoomChristmas();	// �f�X�g���N�^

	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	int _cgBg;
};
