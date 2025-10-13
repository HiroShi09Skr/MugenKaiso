
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeFade.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	cg_bg[0] = LoadGraph("res/UI/Title/cg_title.png");
	cg_bg[1] = LoadGraph("res/UI/Title/cg_title_book.png");
	cg_bg[2] = LoadGraph("res/UI/Title/cg_title_number.png");
	cg_bg[3] = LoadGraph("res/UI/Title/cg_title_press.png");
	cg_bg[4] = LoadGraph("res/UI/Title/cg_title_undertitle.png");
	cg_bg[5] = LoadGraph("res/UI/Title/cg_title_title.png");
	BGM_handle = LoadSoundMem("res/sound/BGM/start.mp3");
	PlaySoundMem(BGM_handle, DX_PLAYTYPE_LOOP);
	bookY = 0;
	bookSaveY = 0.5;
	buttonSaveY = 1;
	for (int i = 0; i < 10; i++) {
		SaveRoot[i] = 0;
		RoomClear[i] = 0;
	}
	for (int i = 0; i < 99; i++) {
		TalkFlg[i] = 0;
	}
	flgGameStart = true;
	ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));
	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (GetModeCount() % 3 == 0)
	{
		// bookY�𓙑���10��-10�̊Ԃœ�����
		if (bookY >= 20 || bookY <= -10) {
			bookSaveY = -bookSaveY;
		}
		bookY += bookSaveY;
	}

	// ESC�L�[�AA�{�^���AB�{�^���Ń��j���[�����GetId
	if ((trg & PAD_INPUT_1 || trg & PAD_INPUT_2 || trg & PAD_INPUT_9) && flgGameStart) {
		// �t�F�[�h�C���A�E�g
		ModeServer::GetInstance()->Add(new ModeFade("OUTIN", false), 999, "fade");
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
		flgGameStart = false;
	}

	if (gGlobal._isFinishFadeOut) {
		StopSoundMem(BGM_handle);
		DeleteSoundMem(BGM_handle);
		// ���̃��[�h���폜����
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();
	int Font = GetFontSize();

	//�w�i
	DrawGraph(0, 0, cg_bg[0], TRUE);

	//�{
	DrawGraph(0, bookY, cg_bg[1], TRUE);

	//����
	DrawGraph(0, 0, cg_bg[2], TRUE);


	//�{�^��
	DrawGraph(0, 0, cg_bg[3], TRUE);

	//����當��
	for (int i = 0; i < 1080; i++) {
		SetDrawArea(0, i, 1920, i + 1);
		DrawGraph(10 * sin(PI * 2 * ((int)(GetModeCount() / 3 + i / 0.8) % 200) / 200), 0, cg_bg[4], TRUE);
	}

	SetDrawArea(0, 0, 1920, 1080);

	DrawGraph(0, 0, cg_bg[5], TRUE);

	
	SetFontSize(Font);

	return true;
}

