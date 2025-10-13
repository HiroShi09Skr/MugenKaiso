#include "RoomBase.h"

class RoomEntrance : public RoomBase
{
public:
	RoomEntrance();				// �C���X�g���N�^
	virtual ~RoomEntrance();	// �f�X�g���N�^

	void SetSpown(Chara& chara, Camera& cam);		// �L�����E�J�����̃}�b�v�Ή�������
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	bool flgEffect;
};
