//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#include "././Pot/Game/updater.h"

namespace cpot {


Updater::Updater() {
	UpdaterManager::S().Regist(this);
}

Updater::~Updater() {
	UpdaterManager::S().Remove(this);
}


}