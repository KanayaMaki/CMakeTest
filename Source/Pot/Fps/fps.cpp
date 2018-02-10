#include "./Pot/Fps/fps.h"


namespace cpot {


void Fps::Init(Time* aTime, Sleep* aSleep, f32 aTargetFps, s32 aSampleNum) {
	mTime = aTime;
	mSleep = aSleep;

	Reset(aTargetFps, aSampleNum);
}


void Fps::Reset(f32 aTargetFps, s32 aSampleNum) {

	mTargetFps = aTargetFps;
	mSampleNum = aSampleNum;
	mNowFps = mTargetFps;
	mCount = 0L;
	mOverTime = false;
	mBeforeOverTime = false;
	mMaxFps = mTargetFps;
	mTotalWaitTime = 0.0;
}

void Fps::Restart() {
	mStartTime = mTime->GetDetail();
	mBeforeTime = mTime->GetDetail();
}



void Fps::Update() {

	Wait();	//60fpsを保つために待つ

	//もしカウントが同じになったら
	if (mCount == mSampleNum) {
		f64 lEndTime = mTime->GetDetail();

		f64 lRealTakeTime = lEndTime - mStartTime;	//実際にかかった処理時間
		f64 lTargetTakeTime = ((f64)mSampleNum * cTickUnit) / mTargetFps;	//サンプル時間で、本来ならかかるTick数
		mNowFps = lTargetTakeTime / lRealTakeTime * mTargetFps;

		if (mTotalWaitTime >= 0) {
			u64 lTrueRealTakeTime = lRealTakeTime - mTotalWaitTime;
			mMaxFps = lTargetTakeTime / lTrueRealTakeTime * mTargetFps;
		}
		else {
			mMaxFps = mNowFps;
		}
		mStartTime = lEndTime;
		mCount = 0;
		mTotalWaitTime = 0;
	}
}


void Fps::Wait() {

	mCount++;	//フレーム数を増やす

	f64 lNowTime = mTime->GetDetail();	//現在の時間の取得

	f64 lTakeTime = (lNowTime - mStartTime);	//処理にかかった時間を計算
	f64 lWaitTime = 1.0f / mTargetFps * mCount - lTakeTime;	//Sleepすべき時間を計算

	//フィールドにデータを保存
	mDeltaTime = lNowTime - mBeforeTime;
	mBeforeTime = lNowTime;

	mBeforeOverTime = mOverTime;

	//Sleep
	if (lWaitTime > 0) {
		mSleep->SleepSecond(lWaitTime);
		mOverTime = false;
	}
	else {
		mOverTime = true;
	}
	mTotalWaitTime += lWaitTime;


	//DeltaTimeの設定
	SetDeltaTime(mDeltaTime);
}

}