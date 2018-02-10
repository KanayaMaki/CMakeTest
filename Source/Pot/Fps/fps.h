#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Sleep/sleep.h"
#include "./Pot/Time/time.h"

#include "./Pot/Usefull/singleton.h"


namespace cpot {


class Fps : public Singleton<Fps> {

public:
	void Init(Time* aTime, Sleep* aSleep, f32 aTargetFps, s32 aSampleNum = 60);
	void Reset(f32 aTargetFps, s32 aSampleNum);
	void Restart();

public:
	void Update();
private:
	void Wait();	//内部で時間を計算し待つ

public:
	f32 MaxFps() const { return mMaxFps; }
	f32 NowFps() const { return mNowFps; }
	f64 DeltaTime() const { return mDeltaTime; }

	BOOL OverTime() const { return mOverTime; }
	BOOL CanRender() const {
		if (!mBeforeOverTime) {
			if (mOverTime) {
				return false;
			}
		}
		return true;
	}


private:
	Time* mTime;
	Sleep* mSleep;

private:
	f32 mTargetFps;	//fpsがこの数になるように処理
	s32 mSampleNum;	//何回のループをもとにfpsを計算するか

	f64 mBeforeTime;	//以前の時間を格納
	f64 mStartTime;	//開始した時間を格納

	f32 mNowFps;	//計算して求めたfps値を格納。値は、countの一周期ごとに更新
	s32 mCount;	//現在何回目か。NUM_OF_SAMPLE周期で回る

	f64 mDeltaTime;	//前回から経過した時間
	BOOL mOverTime;	//処理に１フレームの時間以上かかったかどうか
	BOOL mBeforeOverTime;	//前のフレームで、処理に１フレームの時間以上かかったかどうか

	f64 mTotalWaitTime;	//numOfSample_m周期で、待機した時間を足していく
	f32 mMaxFps;	//待機が無かった時にどれほどのfpsが出たか
};


}
