//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/componentSystem.h"
#include "./Pot/Input/input.h"
#include "./Pot/Time/time.h"

namespace cpot {


class SkyWalkComponent : public Updater {
	CPOT_TYPE(SkyWalkComponent, Updater)

public:
	SkyWalkComponent() {
		mFastMoveSpeed = 20.0f;
		mNormalMoveSpeed = 10.0f;

		mFastRotateSpeed = 90.0f;
		mNormalRotateSpeed = 45.0f;

		mMoveSpeed = mFastMoveSpeed;
		mRotateSpeed = mNormalRotateSpeed;

		mCanMove = true;
		mCanRotate = true;
	}

	//呼び出される関数
	#pragma region Event
public:
	//更新処理
	void OnUpdate() override {
		
		//回転が可能なら
		if (mCanRotate) {

			//回転速度の変更
			if (Input::GetButton(windows::cRightShift)) {
				mRotateSpeed = mFastRotateSpeed;
			}
			else {
				mRotateSpeed = mNormalRotateSpeed;
			}

			//回転
			if (Input::GetButton(windows::cLeft)) {
				GetTransform().mRotation *= Quaternion::FromAxis(Vector3::Up(), -ToRad(mRotateSpeed * DeltaTime()));
			}
			if (Input::GetButton(windows::cRight)) {
				GetTransform().mRotation *= Quaternion::FromAxis(Vector3::Up(), ToRad(mRotateSpeed * DeltaTime()));
			}
			if (Input::GetButton(windows::cUp)) {
				GetTransform().mRotation *= Quaternion::FromAxis(GetTransform().mRotation.Right(), -ToRad(mRotateSpeed * DeltaTime()));
			}
			if (Input::GetButton(windows::cDown)) {
				GetTransform().mRotation *= Quaternion::FromAxis(GetTransform().mRotation.Right(), ToRad(mRotateSpeed * DeltaTime()));
			}
		}

		//移動が可能なら
		if (mCanMove) {

			//移動速度の変更
			if (Input::GetButton(windows::cLeftShift)) {
				mMoveSpeed = mFastMoveSpeed;
			}
			else {
				mMoveSpeed = mNormalMoveSpeed;
			}

			//移動
			if (Input::GetButton(windows::cA)) {
				GetTransform().mPosition += GetTransform().mRotation.Left() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cD)) {
				GetTransform().mPosition += GetTransform().mRotation.Right() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cW)) {
				GetTransform().mPosition += GetTransform().mRotation.Forward() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cS)) {
				GetTransform().mPosition += GetTransform().mRotation.Back() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cE)) {
				GetTransform().mPosition += GetTransform().mRotation.Up() * mMoveSpeed * DeltaTime();
			}
			if (Input::GetButton(windows::cQ)) {
				GetTransform().mPosition += GetTransform().mRotation.Down() * mMoveSpeed * DeltaTime();
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

	BOOL GetCanRotate() const {
		return mCanRotate;
	}
	void SetCanRotate(BOOL aCanRotate) {
		mCanRotate = aCanRotate;
	}

	f32 GetFastRotateSpeed() const {
		return mFastRotateSpeed;
	}
	void SetFastRotateSpeed(f32 aFastRotateSpeed) {
		mFastRotateSpeed = aFastRotateSpeed;
	}
	f32 GetNormalRotateSpeed() const {
		return mNormalRotateSpeed;
	}
	void SetNormalRotateSpeed(f32 aNormalRotateSpeed) {
		mNormalRotateSpeed = aNormalRotateSpeed;
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
	f32 mRotateSpeed;
	f32 mMoveSpeed;

	f32 mFastRotateSpeed;
	f32 mNormalRotateSpeed;
	f32 mFastMoveSpeed;
	f32 mNormalMoveSpeed;

	BOOL mCanMove;
	BOOL mCanRotate;

	#pragma endregion

};
CPOT_REGIST_TYPE(SkyWalkComponent);







//これでコンポーネントを定義
class PresenComponent : public Updater {
	CPOT_TYPE(PresenComponent, Updater)

public:
	void OnUpdate() override {}
};
CPOT_REGIST_TYPE(PresenComponent);


void PresenFunc() {

	GameObject* lObject = new GameObject;
	lObject->SetName("Saito");	//ゲームオブジェクトに名前を付ける

	lObject->AddComponent<PresenComponent>();	//コンポーネントを追加
	lObject->GetComponent<PresenComponent>();	//コンポーネントを取得
	lObject->AddComponent("PresenComponent");	//文字列からでもコンポーネントを追加できる
}


	





}