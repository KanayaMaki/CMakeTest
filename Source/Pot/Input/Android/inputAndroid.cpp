//
//	content	:	Androidでの入力
//	author	:	SaitoYoshiki
//

#include "./Pot/Input/Android/inputAndroid.h"

#ifdef CPOT_VALID_INPUT_ANDROID


namespace cpot {

namespace android {

namespace device {

void Input::Reset() {
	mTouchPos = Vector2(0.0f, 0.0f);
	mIsTouch = false;
}

int32_t Input::engine_handle_input(struct android_app* app, AInputEvent* event) {
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		S().mTouchPos.x = AMotionEvent_getX(event, 0);
		S().mTouchPos.y = AMotionEvent_getY(event, 0);
		S().mIsTouch = true;
		return 1;
	}
	return 0;
}

}


//初期化
#pragma region Init


Input::Input() {

}

void Input::Init() {
	Application::S().GetState()->onInputEvent = device::Input::engine_handle_input;
}


#pragma endregion



//終了処理
#pragma region Final

Input::~Input() {
	
}


#pragma endregion



//更新
#pragma region Update


void Input::Update() {

	mBeforeData = mData;

	mData.mTouchPos[0] = device::Input::S().mTouchPos;
	mData.mButton.Flag(cTouch, device::Input::S().mIsTouch);

	device::Input::S().Reset();
}

#pragma endregion



BOOL Input::IsValid() const {
	return true;
}


}

}

#endif