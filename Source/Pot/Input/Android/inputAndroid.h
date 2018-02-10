//
//	content	:	Windowsでの入力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"


#ifdef CPOT_ON_ANDROID

#define CPOT_VALID_INPUT_ANDROID

#endif


#pragma region InputCode

namespace cpot {

namespace android {

enum CInputCode {
	cTouch,
	cTouchPosX,
	cTouchPosY,
	cMax,
};


}

}

#pragma endregion


//Androidでの入力が有効なら
#ifdef CPOT_VALID_INPUT_ANDROID

#include "./Pot/Application/Android/android_native_app_glue.h"
#include "./Pot/Application/Android/applicationAndroid.h"


namespace cpot {

namespace android {

namespace device {

class Input : public Singleton<Input> {
	friend class Singleton<Input>;

public:
	void Reset();

public:
	Vector2 mTouchPos;
	BOOL mIsTouch;

public:
	static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);
};

}


class Input : public Singleton<Input> {
	friend Singleton<Input>;

	//初期化
	#pragma region Init

private:
	Input();

public:
	void Init();

	#pragma endregion


	//終了
	#pragma region Final

public:
	~Input();

	#pragma endregion


	//更新
	#pragma region Update

public:
	//デバイスごとの入力状態を更新
	void Update();

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//入力された値
	f32 GetValue(CInputCode aCode) const {
		if (aCode <= CInputCode::cTouch) {
			return mData.mButton.IsStand(aCode) ? 1.0f : 0.0f;
		}
		else if (aCode == CInputCode::cTouchPosX) {
			return GetTouchPosX();
		}
		else if (aCode == CInputCode::cTouchPosY) {
			return GetTouchPosY();
		}
		else {
			return 0.0f;
		}
	}
	f32 GetValueBefore(CInputCode aCode) const {
		if (aCode <= CInputCode::cTouch) {
			return mBeforeData.mButton.IsStand(cTouch) ? 1.0f : 0.0f;
		}
		else if (aCode == CInputCode::cTouchPosX) {
			return GetTouchBeforePos().y;
		}
		else if (aCode == CInputCode::cTouchPosY) {
			return GetTouchBeforePos().x;
		}
		else {
			return 0.0f;
		}
	}

	BOOL GetButton(CInputCode aCode) const {
		return NotZero(GetValue(aCode));
	}
	BOOL GetButtonBefore(CInputCode aCode) const {
		return NotZero(GetValueBefore(aCode));
	}
	BOOL GetButtonDown(CInputCode aCode) const {
		if (!GetButtonBefore(aCode)) {
			if (GetButton(aCode)) {
				return true;
			}
		}
		return false;
	}
	BOOL GetButtonUp(CInputCode aCode) const {
		if (GetButtonBefore(aCode)) {
			if (!GetButton(aCode)) {
				return true;
			}
		}
		return false;
	}

	f32 GetTouchPosX() const {
		return GetTouchPos().y;
	}
	f32 GetTouchPosY() const {
		return GetTouchPos().x;
	}
	Vector2 GetTouchPos() const {
		return mData.mTouchPos[0];
	}
	Vector2 GetTouchBeforePos() const {
		return mBeforeData.mTouchPos[0];
	}
	Vector2 GetTouchMove() const {
		return GetTouchPos() - GetTouchBeforePos();
	}

	//使用可能かどうか
	BOOL IsValid() const;

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	struct InputData {
		Vector2 mTouchPos[10];
		BitFlag mButton;
	};

	//入力された値を格納する
	InputData mData;
	InputData mBeforeData;

	#pragma endregion

};


}

}


#endif
