#include "appframe.h"

#include "Fade.h"
#include <string>
#include <vector>

// フェード効果用モード
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
	int _step;					// フェード効果ステップ
	std::string _fadeType;		// フェード効果タイプ
	bool _flgSkip;				// 下のレイヤーでProcess()をスキップするかどうか

	Fade gFade;
};
