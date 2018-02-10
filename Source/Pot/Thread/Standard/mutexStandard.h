//
//	content	:	Standard‚Å‚ÌMutex‚ÌŽÀ‘•
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Thread/mutex.h"

#include <mutex>


namespace cpot {

namespace standard {


class Mutex : public MutexBase {
public:
	void Lock() CPOT_OR {
		mMutex.lock();
	}
	void Unlock() CPOT_OR {
		mMutex.unlock();
	}

private:
	std::mutex mMutex;
};


}

using Mutex = standard::Mutex;

}

#include "./Pot/Thread/mutexLocker.h"