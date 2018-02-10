//
//	content	:	XInputでの入力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"


#ifdef CPOT_ON_WINDOWS

#define CPOT_VALID_XINPUT

#endif


//InputCodeの定義。XInputが無効でも、行う
#pragma region InputCode


namespace cpot {

namespace xInput {

//Joystickコントローラーのボタンを定義
enum CInputCode {

	cDPadLeft,
	cDPadRight,
	cDPadUp,
	cDPadDown,
	cButtonA,
	cButtonB,
	cButtonX,
	cButtonY,
	cLThumb,
	cLShoulder,
	cRThumb,
	cRShoulder,
	cStart,
	cBack,
	cLStickLeft,
	cLStickRight,
	cLStickUp,
	cLStickDown,
	cRStickLeft,
	cRStickRight,
	cRStickUp,
	cRStickDown,
	cLTrigger,
	cRTrigger,
};

//コントローラの軸を定義
enum CInputAxisCode {
	cLStickX,
	cLStickY,
	cRStickX,
	cRStickY,
	cDPadX,
	cDPadY,
};

}

}

#pragma endregion


#ifdef CPOT_VALID_XINPUT

namespace cpot {

namespace xInput {

class Input : public Singleton<Input> {
	friend Singleton<Input>;

	//初期化
	#pragma region Init

private:
	Input() {
		for (u32 i = 0; i < cControllerMaxNum; i++) {
			Reset(i);
		}
	}

	void Reset(u32 aCount) {
		mInputData[aCount].mData;
		mInputData[aCount].mBeforeData = mInputData[aCount].mData;
		mInputData[aCount].mIsValid = false;
	}

	#pragma endregion


	//更新
	#pragma region Update

public:
	//入力の更新
	void Update();

	#pragma endregion


	//取得
	#pragma region Getter

public:

	//一つのコントローラを使用する
	#pragma region Single

	static const u32 cDefaultControllerNum = 0;

	//値の取得
	f32 GetValue(CInputCode aCode) const {
		return GetValue(cDefaultControllerNum, aCode);
	}
	f32 GetValueBefore(CInputCode aCode) const {
		return GetValueBefore(cDefaultControllerNum, aCode);
	}

	//ボタンが押されているか
	BOOL GetButton(CInputCode aCode) const {
		return GetButton(cDefaultControllerNum, aCode);
	}
	BOOL GetButtonBefore(CInputCode aCode) const {
		return GetButtonBefore(cDefaultControllerNum, aCode);
	}

	//ボタンが押された瞬間か
	BOOL GetButtonDown(CInputCode aCode) const {
		return GetButtonDown(cDefaultControllerNum, aCode);
	}

	//ボタンが離された瞬間か
	BOOL GetButtonUp(CInputCode aCode) const {
		return GetButtonUp(cDefaultControllerNum, aCode);
	}

	//値の取得
	f32 GetAxis(CInputCode aMinus, CInputCode aPlus) const {
		return GetAxis(cDefaultControllerNum, aMinus, aPlus);
	}
	f32 GetAxis(CInputAxisCode aCode) const {
		return GetAxis(cDefaultControllerNum, aCode);
	}

	//コントローラが有効か
	BOOL IsValid() const {
		return IsValid(cDefaultControllerNum);
	}

	#pragma endregion


	//複数人の入力を取れる
	#pragma region Multi

	//値の取得
	f32 GetValue(u32 aControllerNum, CInputCode aCode) const;
	f32 GetValueBefore(u32 aControllerNum, CInputCode aCode) const;

	//ボタンが押されているか
	BOOL GetButton(u32 aControllerNum, CInputCode aCode) const {
		return NotZero(GetValue(aControllerNum, aCode));
	}
	BOOL GetButtonBefore(u32 aControllerNum, CInputCode aCode) const {
		return NotZero(GetValueBefore(aControllerNum, aCode));
	}

	//ボタンが押された瞬間か
	BOOL GetButtonDown(u32 aControllerNum, CInputCode aCode) const {
		if (!GetButtonBefore(aControllerNum, aCode)) {
			if (GetButton(aControllerNum, aCode)) {
				return true;
			}
		}
		return false;
	}

	//ボタンが離された瞬間か
	BOOL GetButtonUp(u32 aControllerNum, CInputCode aCode) const {
		if (GetButtonBefore(aControllerNum, aCode)) {
			if (!GetButton(aControllerNum, aCode)) {
				return true;
			}
		}
		return false;
	}

	//値の取得
	f32 GetAxis(u32 aControllerNum, CInputCode aMinus, CInputCode aPlus) const {
		return Strong(-GetValue(aMinus), GetValue(aPlus));
	}
	f32 GetAxis(u32 aControllerNum, CInputAxisCode aCode) const {
		switch (aCode)
		{
			case cLStickX:
				return GetAxis(cLStickLeft, cLStickRight);
			case cLStickY:
				return GetAxis(cLStickDown, cLStickUp);
			case cRStickX:
				return GetAxis(cRStickLeft, cRStickRight);
			case cRStickY:
				return GetAxis(cRStickDown, cRStickUp);
			case cDPadX:
				return GetAxis(cDPadLeft, cDPadRight);
			case cDPadY:
				return GetAxis(cDPadDown, cDPadUp);
		}
		return 0.0f;
	}


	//コントローラが有効か
	BOOL IsValid(u32 aControllerNum) const {
		CPOT_ASSERT(aControllerNum < cControllerMaxNum);
		return mInputData[aControllerNum].mIsValid;
	}

	#pragma endregion


	#pragma endregion


	//操作
	#pragma region Operator

public:
	//バイブレーションさせる


	#pragma endregion


	//フィールド
	#pragma region Field

private:
	static const u32 cControllerMaxNum = 4;

	struct InputData {
		BitFlag mButton;
		s16 mLeftStickX;
		s16 mLeftStickY;
		s16 mRightStickX;
		s16 mRightStickY;
		BYTE mRightTrigger;
		BYTE mLeftTrigger;
	};

	struct ControllerData {
		InputData mData;
		InputData mBeforeData;
		BOOL mIsValid;
	};

	ControllerData mInputData[cControllerMaxNum];

	#pragma endregion

private:
	static f32 GetValue(const InputData& aData, CInputCode aCode);
};


}

}

#endif