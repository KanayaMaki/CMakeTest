//
//	一定時間スレッドを止める、スリープクラスの実装
//

#pragma once

#include "./Pot/Sleep/sleep.h"
#include "./Pot/Usefull/singleton.h"

#include <unistd.h>

namespace cpot {

namespace linux {


//	スリープの機能を提供するクラス
class SleepDevice : public Singleton<SleepDevice> {

public:
	void SleepSecond(f32 aSecond) {
		timespec t;

		u64 lNanoSec = aSecond * 1000.0f * 1000.0f * 1000.0f;
		t.tv_sec = lNanoSec / 1000000000;
		t.tv_nsec = lNanoSec % 1000000000;
		::nanosleep(&t, nullptr);
	}
};


//	スリープクラス
class Sleep : public SleepBase {

public:
	void SleepSecond(f32 aSecond) override {
		SleepDevice::S().SleepSecond(aSecond);
	}
};


}

//	プログラム中では、このSleepを使用する
using Sleep = linux::Sleep;

}