//
//	content	:	StandardでのThreadの実装
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Thread/thread.h"

#include <thread>


namespace cpot {

namespace standard {


class Thread : public ThreadBase {
public:
	Thread() {
		mIsStarted = false;
	}

public:
	void Start(ThreadFunc aFunc, void* aData) CPOT_OR {
		if (IsStarted()) {
			return;
		}
		mThread = std::thread(aFunc, aData);
		mIsStarted = true;
	}
	template <typename T>
	void Start(ThreadFuncTmp<T> aFunc, T* aData) {
		Start((ThreadFunc)aFunc, (void*)aData);
	}
	template <typename T>
	void Start(ThreadFuncTmp<T> aFunc, std::nullptr_t aNull) {
		Start((ThreadFunc)aFunc, (void*)aNull);
	}

	void Detach() CPOT_OR {
		if (!IsStarted()) {
			return;
		}
		mThread.detach();
		mIsStarted = false;
	}
	void Join() CPOT_OR {
		if (!IsStarted()) {
			return;
		}
		mThread.join();
		mIsStarted = false;
	}

	BOOL IsStarted() CPOT_OR {
		return mIsStarted;
	}

public:
	std::thread mThread;
	BOOL mIsStarted;
};


}

//デフォルトでは、StandardのThreadを使用
using Thread = standard::Thread;

}