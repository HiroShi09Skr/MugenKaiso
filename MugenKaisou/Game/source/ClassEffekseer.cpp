#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ClassEffekseer.h"

ClassEffekseer::ClassEffekseer() {
	_effectResourceHandle = -1;
	breakFlag = 1;
	_position_x = 0;
	_position_y = 0;
	_position_z = 0;
}

ClassEffekseer::~ClassEffekseer() {
	
}
void ClassEffekseer::AddEffect(const TCHAR* EffectHandle, float x, float y, float z,int _EffectCntMax ,float Rotate, float size) {
	_effectResourceHandle = LoadEffekseerEffect(EffectHandle, size);
	_position_x = x;
	_position_y = y;
	_position_z = z;
	EffectCnt = 0;
	EffectCntMax = _EffectCntMax;
	_Rotate = Rotate;

	// �G�t�F�N�g���Đ�����B
	_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
}

void ClassEffekseer::DeleteEffect() {
	// �G�t�F�N�g���\�[�X���폜����B
	StopEffekseer3DEffect(_playingEffectHandle);
	DeleteEffekseerEffect(_effectResourceHandle);
}

void ClassEffekseer::Process() {

    if (EffectCnt % 60 == 0) {
        // �G�t�F�N�g�̈ʒu���Z�b�g����B
        SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
        SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0.0f, _Rotate, 0.0f);
		breakFlag = false;
    }

    EffectCnt++;

	if (IsEffekseer3DEffectPlaying(_playingEffectHandle) == -1) {
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
		SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0.0f, _Rotate, 0.0f);
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
	}
}

void ClassEffekseer::Render() {

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}
