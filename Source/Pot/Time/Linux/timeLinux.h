//
//	content	:	Linuxでの時間に関するクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Time/time.h"

#include <chrono>


namespace cpot {

namespace linux {


//時間を取得
#pragma region Time

class Time : public TimeBase {

public:
	Time() {
		//開始地点
		base = std::chrono::high_resolution_clock::now();
	}


	//ユニックスタイムを取得
	UnixTimeType GetUnix() const CPOT_OR {
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();

		std::time_t t = std::chrono::system_clock::to_time_t(p);
		return t;
	}

	//細密な時間を取得
	f64 GetDetail() const CPOT_OR {
		std::chrono::high_resolution_clock::time_point p = std::chrono::high_resolution_clock::now();
		
		std::chrono::nanoseconds t = std::chrono::duration_cast<std::chrono::nanoseconds>(p - base);
		return t.count() / 1000.0f / 1000.0f / 1000.0f;
	}

private:
	std::chrono::high_resolution_clock::time_point base;
};

#pragma endregion


}


//このプログラムでは、Timeクラスはwindows::Timeを使うようにする
using Time = linux::Time;

}
