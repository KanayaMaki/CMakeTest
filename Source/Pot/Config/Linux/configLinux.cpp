//
//	content	:	ゲームのコンフィグのLinux環境
//	author	:	SaitoYoshiki
//

#include "./Pot/Config/Linux/configLinux.h"


namespace cpot {

namespace linux {


void Config::SetTitle(const CHAR* aTitle) {
	MutexLocker m(mTitleMutex);
	mTitle = aTitle;

}


}

}