#include "RoomBase.h"

class RoomGrave : public RoomBase
{
public:
	RoomGrave();				// �C���X�g���N�^
	virtual ~RoomGrave();	// �f�X�g���N�^

	void SetSpown(Chara& chara, Camera& cam);		// �L�����E�J�����̃}�b�v�Ή�������
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	bool flgEffect;

	// �s�U
	Pizza pizza;
	std::vector<Pizza> _vPizza;
};
