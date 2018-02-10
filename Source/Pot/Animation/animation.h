//
//	content	:	Animationクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Out/out.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/singleton.h"


namespace cpot {


//値の補間に使う関数群
#pragma region Interpolation


//デフォルト
template<typename T>
inline T Interpolation(const T& aStart, const T& aEnd, f32 aRate) {
	return Lerp(aStart, aEnd, aRate);
}

//ポインタ
template<typename T>
inline T* Interpolation(T* aStart, T* aEnd, f32 aRate) {
	if (aRate >= 1.0f) {
		return aEnd;
	}
	return aStart;
}

//クォータニオン
template<>
inline Quaternion Interpolation(const Quaternion& aStart, const Quaternion& aEnd, f32 aRate) {
	return SLerp(aStart, aEnd, aRate);
}


#pragma endregion



//アニメーションのキーフレーム
#pragma region KeyFrame

template <typename T>
struct KeyFrame {
	KeyFrame(f32 aTime, const T& aValue) : mTime(aTime), mValue(aValue) {}
	KeyFrame(f32 aTime) : mTime(aTime) {}
	KeyFrame() {}
	f32 mTime;
	T mValue;

	BOOL operator <(const KeyFrame& v) const {
		return mTime < v.mTime;
	}
	BOOL operator ==(const KeyFrame& v) const {
		return IsEqual(mTime, v.mTime);
	}
};

#pragma endregion



//アニメーション
#pragma region Animation


template <typename T>
class Animation {

public:
	Animation() {
		mTime = 0.0f;
		mIsLoop = false;
		Add(0.0f, mDefault);
	}

	//追加
	#pragma region Add

public:
	void Add(f32 aTime, const T& aValue) {
		Remove(aTime);
		mKeyFrames.PushBack(KeyFrame<T>(aTime, aValue));
		Sort();
		mEndTime = mKeyFrames[GetKeyFrameNum() - 1].mTime;
	}

	#pragma endregion


	//削除
	#pragma region Remove

public:
	void Remove(f32 aTime) {
		mKeyFrames.Remove(KeyFrame<T>(aTime));
	}

	#pragma endregion


	//取得
	#pragma region Getter

	//値の取得
	#pragma region Value

public:
	T Get(f32 aTime) {
		s32 lBeginIndex = GetKeyFrameIndex(aTime);
		s32 lEndIndex = lBeginIndex + 1;

		if (lBeginIndex < 0) {
			return mKeyFrames[0].mValue;
		}
		else if (lEndIndex >= GetKeyFrameNum()) {
			return mKeyFrames[GetKeyFrameNum() - 1].mValue;
		}
		else {
			f32 lTimeBegin = mKeyFrames[lBeginIndex].mTime;
			f32 lTimeEnd = mKeyFrames[lEndIndex].mTime;

			f32 lLerpRate = (aTime - lTimeBegin) / (lTimeEnd - lTimeBegin);

			return Interpolation(mKeyFrames[lBeginIndex].mValue, mKeyFrames[lEndIndex].mValue, lLerpRate);
		}
	}
	T Get() {
		return Get(mTime);
	}

	#pragma endregion


	//時間によって使用するキーフレームの、インデックス
	#pragma region Index

private:
	s32 GetKeyFrameIndex(f32 aTime) {
		s32 aIdx = -1;
		for (u32 i = 0; i < mKeyFrames.GetSize(); i++) {
			if (mKeyFrames[i].mTime <= aTime) {
				aIdx = i;
			}
			else {
				break;
			}
		}
		return aIdx;
	}
	s32 GetKeyFrameIndex() {
		return GetKeyFrameIndex(GetTime());
	}

	#pragma endregion

	
	//時間
	#pragma region Time

public:
	//現在時間
	f32 GetTime() const {
		return mTime;
	}
	//終了時間
	f32 GetEndTime() const {
		return mEndTime;
	}

	#pragma endregion


public:
	BOOL GetIsLoop() const {
		return mIsLoop;
	}

public:
	u32 GetKeyFrameNum() const {
		return mKeyFrames.GetSize();
	}

	#pragma endregion


	//設定
	#pragma region Setter

public:
	//現在の時間を設定
	void SetTime(f32 aTime) {
		mTime = aTime;
		TimeInRange();
	}

	#pragma endregion


	//操作
	#pragma region Operate

public:
	//並び変える
	void Sort() {
		mKeyFrames.Sort();
	}

	//時間
	#pragma region Time

public:
	//現在の時間を進める
	void ForwardTime(f32 aTime) {
		mTime += aTime;
		TimeInRange();
	}
	void BackTime(f32 aTime) {
		ForwardTime(-aTime);
	}

private:
	void TimeInRange() {
		if (GetIsLoop()) {
			mTime = Wrap(mTime, GetEndTime());
		}
		else {
			mTime = Clamp(mTime, GetEndTime());
		}
	}

	#pragma endregion

public:
	void SetIsLoop(BOOL aIsLoop) {
		mIsLoop = aIsLoop;
	}

	#pragma endregion




	//フィールド
	#pragma region Field

private:
	Vector<KeyFrame<T>> mKeyFrames;
	f32 mTime;
	f32 mEndTime;
	BOOL mIsLoop;

	static T mDefault;	//最初に0.0fに追加しておく、デフォルトの値

	#pragma endregion
};

template <typename T>
T Animation<T>::mDefault;


#pragma endregion

}