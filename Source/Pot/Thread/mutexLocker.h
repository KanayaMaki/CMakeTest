//
//	content	:	Mutexを安全に使用できるクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Thread/mutex.h"

namespace cpot {

class MutexLocker {
public:
	MutexLocker(Mutex& aMutex) : mMutex(aMutex) {
		mMutex.Lock();
	}
	~MutexLocker() {
		mMutex.Unlock();
	}

	Mutex& mMutex;
};

}