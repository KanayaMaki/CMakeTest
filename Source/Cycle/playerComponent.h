//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/componentSystem.h"
#include "./Pot/Game/cameraComponent.h"
#include "./Pot/Input/input.h"
#include "./Pot/Time/time.h"

namespace cpot {

class PlayerComponent : public Updater {
	CPOT_TYPE(PlayerComponent, Updater)

public:
	PlayerComponent() {
		mFastMoveSpeed = 20.0f;
		mNormalMoveSpeed = 10.0f;

		mMoveSpeed = mFastMoveSpeed;
		mCanMove = true;
	}

	//呼び出される関数
	#pragma region Event
public:
	//更新処理
	void OnUpdate() override {
	
		//移動が可能なら
		if (mCanMove) {

			//移動速度の変更
			if (Input::GetButton(windows::cLeftShift)) {
				mMoveSpeed = mFastMoveSpeed;
			}
			else {
				mMoveSpeed = mNormalMoveSpeed;
			}

			CameraComponent* lCamera = CameraComponentManager::S().Get(0);
			
			Quaternion lCameraRotation;
			if (lCamera) {
				lCameraRotation = lCamera->GetTransform().mRotation;
			}

			//移動
			Vector3 lSpeed;

			if (Input::GetButton(windows::cA)) {
				lSpeed += lCameraRotation.Left().Y(0.0f) * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cD)) {
				lSpeed += lCameraRotation.Right().Y(0.0f) * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cW)) {
				lSpeed += lCameraRotation.Forward().Y(0.0f) * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cS)) {
				lSpeed += lCameraRotation.Back().Y(0.0f) * mMoveSpeed * DeltaTime();
			}

			GetTransform().mPosition += lSpeed;
			if (NotZero(lSpeed.Len())) {
				Quaternion lTargetRotation = Quaternion::BetweenVector(Vector3::Forward(), lSpeed);
				GetTransform().mRotation = SLerpLimit(GetTransform().mRotation, lTargetRotation, ToRad(90.0f) * DeltaTime());
				//CPOT_LOG(BetweenAngle(GetTransform().mRotation, lTargetRotation));
			}
		}
	}

	#pragma endregion


	//優先度
	#pragma region Priority
public:
	s32 GetPriority() override {
		return 0;
	}

	#pragma endregion


	//プロパティ
	#pragma region Property

public:
	BOOL GetCanMove() const {
		return mCanMove;
	}
	void SetCanMove(BOOL aCanMove) {
		mCanMove = aCanMove;
	}

	f32 GetFastMoveSpeed() const {
		return mFastMoveSpeed;
	}
	void SetFastMoveSpeed(f32 aFastMoveSpeed) {
		mFastMoveSpeed = aFastMoveSpeed;
	}
	f32 GetNormalMoveSpeed() const {
		return mNormalMoveSpeed;
	}
	void SetNormalMoveSpeed(f32 aNormalMoveSpeed) {
		mNormalMoveSpeed = aNormalMoveSpeed;
	}

	#pragma endregion


	//フィールド
	#pragma region Field


private:
	f32 mMoveSpeed;

	f32 mFastMoveSpeed;
	f32 mNormalMoveSpeed;

	BOOL mCanMove;

	#pragma endregion

};
CPOT_REGIST_TYPE(PlayerComponent);

}