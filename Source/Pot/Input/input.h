//
//	content	:	入力
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Config/config.h"

#include "./Pot/Input/Windows/inputWindows.h"
#include "./Pot/Input/XInput/inputXInput.h"
#include "./Pot/Input/Android/inputAndroid.h"


namespace cpot {

class Input {

	//Windowsの入力を担当する
	#pragma region Windows
	
	//Windowsの入力が有効なら
	#ifdef CPOT_VALID_INPUT_WINDOWS

public:
	static f32 GetValue(windows::CInputCode aCode) {
		return windows::Input::S().GetValue(aCode);
	}
	static BOOL GetButton(windows::CInputCode aCode) {
		return windows::Input::S().GetButton(aCode);
	}
	static BOOL GetButtonDown(windows::CInputCode aCode) {
		return windows::Input::S().GetButtonDown(aCode);
	}
	static BOOL GetButtonUp(windows::CInputCode aCode) {
		return windows::Input::S().GetButtonUp(aCode);
	}
	static f32 GetAxis(windows::CInputAxisCode aCode) {
		return windows::Input::S().GetAxis(aCode);
	}

	//Windowsの入力が無効なら、入力無し
	#else

public:
	static f32 GetValue(windows::CInputCode aCode) {
		return 0.0f;
}
	static BOOL GetButton(windows::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonDown(windows::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonUp(windows::CInputCode aCode) {
		return false;
	}
	static f32 GetAxis(windows::CInputAxisCode aCode) {
		return 0.0f;
	}

	#endif

	#pragma endregion


	//XInputの入力を担当する
	#pragma region XInput

public:
	//１番目のプレイヤーのコントローラを使用
	static f32 GetValue(xInput::CInputCode aCode) {
		return GetValue(0, aCode);
	}
	static BOOL GetButton(xInput::CInputCode aCode) {
		return GetButton(0, aCode);
	}
	static BOOL GetButtonDown(xInput::CInputCode aCode) {
		return GetButtonDown(0, aCode);
	}
	static BOOL GetButtonUp(xInput::CInputCode aCode) {
		return GetButtonUp(0, aCode);
	}
	static f32 GetAxis(xInput::CInputAxisCode aCode) {
		return GetAxis(0, aCode);
	}

	//XInputが有効な時
	#ifdef CPOT_VALID_XINPUT

public:
	static f32 GetValue(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetValue(aControllerNum, aCode);
	}
	static BOOL GetButton(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetButton(aControllerNum, aCode);
	}
	static BOOL GetButtonDown(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetButtonDown(aControllerNum, aCode);
	}
	static BOOL GetButtonUp(u32 aControllerNum, xInput::CInputCode aCode) {
		return xInput::Input::S().GetButtonUp(aControllerNum, aCode);
	}
	static f32 GetAxis(u32 aControllerNum, xInput::CInputAxisCode aCode) {
		return xInput::Input::S().GetAxis(aControllerNum, aCode);
	}

	//XInputが無効な時
	#else

public:
	//入力無しの状態の値を返す
	static f32 GetValue(u32 aControllerNum, xInput::CInputCode aCode) {
		return 0.0f;
	}
	static BOOL GetButton(u32 aControllerNum, xInput::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonDown(u32 aControllerNum, xInput::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonUp(u32 aControllerNum, xInput::CInputCode aCode) {
		return false;
	}
	static f32 GetAxis(u32 aControllerNum, xInput::CInputAxisCode aCode) {
		return 0.0f;
	}

	#endif

	#pragma endregion



	//Androidの入力を担当する
	#pragma region Android

	//Windowsの入力が有効なら
	#ifdef CPOT_VALID_INPUT_ANDROID

public:
	static f32 GetValue(android::CInputCode aCode) {
		return android::Input::S().GetValue(aCode);
	}
	static BOOL GetButton(android::CInputCode aCode) {
		return android::Input::S().GetButton(aCode);
	}
	static BOOL GetButtonDown(android::CInputCode aCode) {
		return android::Input::S().GetButtonDown(aCode);
	}
	static BOOL GetButtonUp(android::CInputCode aCode) {
		return android::Input::S().GetButtonUp(aCode);
	}

	//Windowsの入力が無効なら、入力無し
	#else

public:
	static f32 GetValue(android::CInputCode aCode) {
		return 0.0f;
	}
	static BOOL GetButton(android::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonDown(android::CInputCode aCode) {
		return false;
	}
	static BOOL GetButtonUp(android::CInputCode aCode) {
		return false;
	}
	#endif

	#pragma endregion
};

}
