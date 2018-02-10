//
//	content	:	別のスレッドで関数を実行するクラスのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"


namespace cpot {


template<typename T> using ThreadFuncTmp = void*(*)(T*);
using ThreadFunc = void*(*)(void*);

class ThreadBase {
public:
	CPOT_VI void Start(ThreadFunc aFunc, void* aData) CPOT_ZR;
	template <typename T>
	void Start(ThreadFuncTmp<T> aFunc, T* aData);
	CPOT_VI void Detach() CPOT_ZR;
	CPOT_VI void Join() CPOT_ZR;

	CPOT_VI BOOL IsStarted() CPOT_ZR;
};


}


//ThreadとMutexの宣言
#ifdef CPOT_ON_WINDOWS
#include "./Pot/Thread/Standard/threadStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Thread/Android/threadAndroid.h"
#elif defined CPOT_ON_LINUX
#include "./Pot/Thread/Standard/threadStandard.h"
#endif