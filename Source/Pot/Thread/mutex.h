//
//	content	:	スレッド間での排他制御を可能にするクラスのインターフェース
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"


namespace cpot {


class MutexBase {
public:
	CPOT_VI void Lock() CPOT_ZR;
	CPOT_VI void Unlock() CPOT_ZR;
};


}


//デバイスごとのMutexの宣言
#ifdef CPOT_ON_WINDOWS
#include "./Pot/Thread/Standard/mutexStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Thread/Android/mutexAndroid.h"
#elif defined CPOT_ON_LINUX
#include "./Pot/Thread/Standard/mutexStandard.h"
#endif