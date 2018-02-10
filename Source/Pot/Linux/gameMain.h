//
//	content	:	エントリーポイント
//	author	:	SaitoYoshiki
//

#include "./Pot/Atom/atom.h"

namespace cpot {

class GameBase;

class GameMain {
public:
	static GameBase* mGame;

public:
	static void Setting();

	static void GameInit();
	static void GameUpdate();
	static void GameRender();
	static void GameFinal();
};

}
