//
//	content	:	Windowsでの入力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"


#ifdef CPOT_ON_WINDOWS

#define CPOT_VALID_INPUT_WINDOWS

#endif


#pragma region InputCode

namespace cpot {

namespace windows {

enum CInputCode {
	c0,
	c1,
	c2,
	c3,
	c4,
	c5,
	c6,
	c7,
	c8,
	c9,
	cA,
	cB,
	cC,
	cD,
	cE,
	cF,
	cG,
	cH,
	cI,
	cJ,
	cK,
	cL,
	cM,
	cN,
	cO,
	cP,
	cQ,
	cR,
	cS,
	cT,
	cU,
	cV,
	cW,
	cX,
	cY,
	cZ,
	cLeft,
	cRight,
	cUp,
	cDown,
	cSpace,
	cEnter,
	cLeftCtrl,
	cRightCtrl,
	cLeftAlt,
	cRightAlt,
	cLeftShift,
	cRightShift,
	cEsc,
	cF1,
	cF2,
	cF3,
	cF4,
	cF5,
	cF6,
	cF7,
	cF8,
	cF9,
	cF10,
	cF11,
	cF12,
	cMouseCursorX,
	cMouseCursorY,
	cMouseCursorXDelta,
	cMouseCursorYDelta,
	cMouseWheel,
	cMouseButton1,
	cMouseButton2,
	cMouseButton3,
	cMouseButton4,
	cNull,	//何もないキー
	cMax,
};


enum CInputAxisCode {
	cAD,
	cWS,
	cCrossX,
	cCrossY
};


}

}

#pragma endregion


//Windowsでの入力が有効なら
#ifdef CPOT_VALID_INPUT_WINDOWS

#include <dinput.h>
#include "./Pot/Config/config.h"

namespace cpot {

namespace windows {


//InputCodeからDirectXのコードに変換する
const u8 TransList[]{
	DIK_0,
	DIK_1,
	DIK_2,
	DIK_3,
	DIK_4,
	DIK_5,
	DIK_6,
	DIK_7,
	DIK_8,
	DIK_9,
	DIK_A,
	DIK_B,
	DIK_C,
	DIK_D,
	DIK_E,
	DIK_F,
	DIK_G,
	DIK_H,
	DIK_I,
	DIK_J,
	DIK_K,
	DIK_L,
	DIK_M,
	DIK_N,
	DIK_O,
	DIK_P,
	DIK_Q,
	DIK_R,
	DIK_S,
	DIK_T,
	DIK_U,
	DIK_V,
	DIK_W,
	DIK_X,
	DIK_Y,
	DIK_Z,
	DIK_LEFT,
	DIK_RIGHT,
	DIK_UP,
	DIK_DOWN,
	DIK_SPACE,
	DIK_RETURN,
	DIK_LCONTROL,
	DIK_RCONTROL,
	DIK_LALT,
	DIK_RALT,
	DIK_LSHIFT,
	DIK_RSHIFT,
	DIK_ESCAPE,
	DIK_F1,
	DIK_F2,
	DIK_F3,
	DIK_F4,
	DIK_F5,
	DIK_F6,
	DIK_F7,
	DIK_F8,
	DIK_F9,
	DIK_F10,
	DIK_F11,
	DIK_F12,
};


class Input : public Singleton<Input> {
	friend Singleton<Input>;

	//初期化
	#pragma region Init

private:
	Input();

public:
	void Init(HINSTANCE aHInstance, HWND aHwnd);

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

private:
	void UpdateKeyboard();
	void UpdateMouse();

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//入力された値
	f32 GetValue(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mData.mKey.IsStand(TransList[aCode]) ? 1.0f : 0.0f;
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return GetMouseLocY();
		}
		else if (aCode == CInputCode::cMouseCursorXDelta) {
			return GetMouseMove().x;
		}
		else if (aCode == CInputCode::cMouseCursorYDelta) {
			return GetMouseMove().y;
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mData.mMouseButton.IsStand(aCode - cMouseButton1) ? 1.0f : 0.0f;
		}
		else {
			return 0.0f;
		}
	}
	f32 GetValueBefore(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mBeforeData.mKey.IsStand(TransList[aCode]) ? 1.0f : 0.0f;
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetBeforeMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return  GetBeforeMouseLocY();
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mBeforeData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mBeforeData.mMouseButton.IsStand(aCode - cMouseButton1) ? 1.0f : 0.0f;
		}
		else {
			return 0.0f;
		}
	}

	BOOL GetButton(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mData.mKey.IsStand(TransList[aCode]);
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return GetMouseLocY();
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mData.mMouseButton.IsStand(aCode - cMouseButton1);
		}
		else {
			return false;
		}
	}
	BOOL GetButtonBefore(CInputCode aCode) const {
		if (aCode <= CInputCode::cF12) {
			return mBeforeData.mKey.IsStand(TransList[aCode]);
		}
		else if (aCode == CInputCode::cMouseCursorX) {
			return GetBeforeMouseLocX();
		}
		else if (aCode == CInputCode::cMouseCursorY) {
			return GetBeforeMouseLocY();
		}
		else if (aCode == CInputCode::cMouseWheel) {
			return mBeforeData.mMouseWheel;
		}
		else if (aCode <= CInputCode::cMouseButton4) {
			return mBeforeData.mMouseButton.IsStand(aCode - cMouseButton1);
		}
		else {
			return false;
		}
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

	f32 GetAxis(CInputCode aMinus, CInputCode aPlus) const {
		return Strong(-GetValue(aMinus), GetValue(aPlus));
	}
	f32 GetAxis(CInputAxisCode aAxis) const {
		switch (aAxis) {
			case CInputAxisCode::cAD:
				return GetAxis(cA, cD);
			case CInputAxisCode::cWS:
				return GetAxis(cS, cW);
			case CInputAxisCode::cCrossX:
				return GetAxis(cLeft, cRight);
			case CInputAxisCode::cCrossY:
				return GetAxis(cDown, cUp);
		}
	}
	

	f32 GetMouseLocX() const {
		return mData.mMouseX;
	}
	f32 GetMouseLocY() const {
		return Config::S().GetScreenSize().y - mData.mMouseY;
	}
	Vector2 GetMouseLoc() const {
		return Vector2(GetMouseLocX(), GetMouseLocY());
	}

	f32 GetBeforeMouseLocX() const {
		return mBeforeData.mMouseX;
	}
	f32 GetBeforeMouseLocY() const {
		return Config::S().GetScreenSize().y - mBeforeData.mMouseY;
	}
	Vector2 GetBeforeMouseLoc() const {
		return Vector2(GetBeforeMouseLocX(), GetBeforeMouseLocY());
	}

	Vector2 GetMouseMove() const {
		return GetMouseLoc() - GetBeforeMouseLoc();
	}
	f32 GetMouseWheel() const {
		return mData.mMouseWheel;
	}

	//使用可能かどうか
	BOOL IsValid() const;

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	struct InputData {
		BitFlagLarge<256> mKey;
		f32 mMouseX, mMouseY;
		f32 mMouseWheel;
		BitFlag mMouseButton;
	};

	//入力された値を格納する
	InputData mData;
	InputData mBeforeData;

	//DirectInputを使うのに必要な変数
	#pragma region DirectInput

	IDirectInput8A* mInput;	//DirectInput全体のデバイス
	IDirectInputDevice8A* mMouseDevice;
	IDirectInputDevice8A* mKeyboardDevice;

	HWND mHwnd;
	HINSTANCE mHInstance;

	#pragma endregion

	#pragma endregion

};


}

}


#endif
