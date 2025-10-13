#include "appframe.h"

#include "Fade.h"
#include <string>
#include <vector>

// �t�F�[�h���ʗp���[�h
class ModeFade : public ModeBase
{
	typedef ModeBase base;
public:
	ModeFade(std::string type, bool skip);
	~ModeFade();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
protected:
	int _step;					// �t�F�[�h���ʃX�e�b�v
	std::string _fadeType;		// �t�F�[�h���ʃ^�C�v
	bool _flgSkip;				// ���̃��C���[��Process()���X�L�b�v���邩�ǂ���

	Fade gFade;
};
