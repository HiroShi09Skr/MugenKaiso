#include "RoomBase.h"

class RoomCalcLabyrinth : public RoomBase
{
public:
	RoomCalcLabyrinth();			// �R���X�g���N�^
	virtual ~RoomCalcLabyrinth();	// �f�X�g���N�^

	void SetSpown(Chara& chara, Camera& cam);		// �L�����E�J�����̃}�b�v�Ή�������
	void Process(Chara& chara, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	
};
