#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

inline Matrix4x4 CreatePerspectiveProjectionMatrix(f32 aViewAngle, f32 aAspectRatio, f32 aNearClipLen, f32 aFarClipLen) {

	Matrix4x4 myMat;
	myMat._11 /= aAspectRatio;

	f32 rad = ToRad(aViewAngle);
	f32 sy = Sin(rad / 2) / Cos(rad / 2);
	myMat._11 *= 1.0f / sy;
	myMat._22 *= 1.0f / sy;
	myMat *= Matrix4x4::FromTransform(Vector3(0.0f, 0.0f, -aNearClipLen));

	myMat._44 = 0.0f;
	myMat._34 = 1.0f;

	//myMat *= Matrix4x4::FromScale(Vector3::One().Z(1.0f / (aFarClipLen - aNearClipLen)));
	myMat *= Matrix4x4::FromScale(Vector3::One().Z(aFarClipLen / (aFarClipLen - aNearClipLen)));

	return myMat;
}

inline Matrix4x4 CreateViewMatrix(const Vector3& aLoc, const Quaternion& aRot) {

	//逆向きに変換していく
	Matrix4x4 lRes;

	//移動の逆向きの変換
	lRes *= Matrix4x4::FromTransform(-aLoc);

	//回転の逆向きの変換
	lRes *= Matrix4x4::FromRotate(-aRot);

	return lRes;
}


class Camera {
public:
	virtual ~Camera() {}

	virtual Matrix4x4 GetViewMatrix() const = 0;
	virtual Matrix4x4 GetProjectionMatrix() const = 0;

	virtual void SetLocation(const Vector3& aLocation) = 0;
	virtual void SetRotation(const Quaternion& aRotation) = 0;

	virtual Vector3 GetLocation() const = 0;
	virtual Quaternion GetRotation() const = 0;
};

class CameraView {
public:
	CameraView() {
		Reset();
	}

	void Reset() {
		mLocation = Vector3::Zero();
		mRotation = Quaternion::Unit();
		Change();
	}

public:
	BOOL IsChanged() const { return mChanged; }
	void Change() { mChanged = true; }
private:
	void UnChange() const { mChanged = false; }

public:
	void SetLocation(const Vector3& aLocation) {
		if (mLocation != aLocation) {
			mLocation = aLocation;
			Change();
		}
	}
	void SetRotation(const Quaternion& aRotation) {
		if (mRotation != aRotation) {
			mRotation = aRotation;
			Change();
		}
	}

	Vector3 GetLocation() const {
		return mLocation;
	}
	Quaternion GetRotation() const {
		return mRotation;
	}

	Matrix4x4 GetMatrix() const {
		if (IsChanged()) {
			CalculateMatrix();
		}
		return mMatrix;
	}

public:
	void CalculateMatrix() const {
		mMatrix = CreateViewMatrix(mLocation, mRotation);
		UnChange();
	}


private:
	mutable Matrix4x4 mMatrix;
	Vector3 mLocation;
	Quaternion mRotation;

	mutable BOOL mChanged;	//行列を更新する必要があるか
};

class CameraProjection {
public:
	CameraProjection() {
		Reset();
	}

	void Reset() {
		mAspectRatio = 1.0f;
		mNearClipLen = 0.01f;
		mFarClipLen = 10000.0f;
		Change();
	}

public:
	BOOL IsChanged() const { return mChanged; }
	void Change() { mChanged = true; }
protected:
	void UnChange() const { mChanged = false; }

public:
	f32 GetAspectRatio() const { return mAspectRatio; }
	void SetAspectRatio(f32 aWidth, f32 aHeight) {
		f32 lAspectRatio = aWidth / aHeight;
		if (mAspectRatio != lAspectRatio) {
			mAspectRatio = lAspectRatio;
			Change();
		}
	}

	f32 GetNearClipLen() const { return mNearClipLen; }
	void SetNearClipLen(f32 aNearClipLen) {
		if (mNearClipLen != aNearClipLen) {
			mNearClipLen = aNearClipLen;
			Change();
		}
	}

	f32 GetFarClipLen() const { return mFarClipLen; }
	void SetFarClipLen(f32 aFarClipLen) {
		if (mFarClipLen != aFarClipLen) {
			mFarClipLen = aFarClipLen;
			Change();
		}
	}


protected:
	mutable Matrix4x4 mMatrix;
	f32 mAspectRatio;	//アスペクト比
	f32 mNearClipLen;	//近いクリップ面までの距離
	f32 mFarClipLen;	//遠いクリップ面までの距離

	mutable BOOL mChanged;	//行列を更新する必要があるか
};

class CameraPersProjection : public CameraProjection {
public:
	CameraPersProjection() {
		Reset();
	}

	void Reset() {
		CameraProjection::Reset();
		mViewAngle = 45.0f;
		Change();
	}

public:
	Matrix4x4 GetMatrix() const {
		if (IsChanged()) {
			CalculateMatrix();
		}
		return mMatrix;
	}

public:
	void CalculateMatrix() const {
		mMatrix = CreatePerspectiveProjectionMatrix(mViewAngle, GetAspectRatio(), GetNearClipLen(), GetFarClipLen());
		UnChange();
	}

public:
	f32 GetViewAngle() { return mViewAngle; }
	void SetViewAngle(f32 aViewAngle) {
		if (mViewAngle != aViewAngle) {
			mViewAngle = aViewAngle;
			Change();
		}
	}

private:
	f32 mViewAngle;	//視野角

};

class PersCamera : public Camera {
public:
	PersCamera() {
		Reset();
	}

public:
	void Reset() {
		mProjection.Reset();
		mView.Reset();
	}


	#pragma region Setter
public:
	void SetLocation(const Vector3& aLocation) {
		mView.SetLocation(aLocation);
	}
	void SetRotation(const Quaternion& aRotation) {
		mView.SetRotation(aRotation);
	}

	void SetAspectRatio(f32 aWidth, f32 aHeight) {
		mProjection.SetAspectRatio(aWidth, aHeight);
	}
	void SetViewAngle(f32 aViewAngle) {
		mProjection.SetViewAngle(aViewAngle);
	}

	#pragma endregion


	#pragma region Getter
public:
	Matrix4x4 GetViewMatrix() const override {
		return mView.GetMatrix();
	}
	Matrix4x4 GetProjectionMatrix() const override {
		return mProjection.GetMatrix();
	}

	Vector3 GetLocation() const override {
		return mView.GetLocation();
	}
	Quaternion GetRotation() const override {
		return mView.GetRotation();
	}

	f32 GetAspectRatio() const { return mProjection.GetAspectRatio(); }
	f32 GetViewAngle() { return mProjection.GetViewAngle(); }

	#pragma endregion


	//フィールド
	#pragma region Field
public:
	CameraPersProjection mProjection;
	CameraView mView;

	#pragma endregion
};


class CameraManager : public Singleton<CameraManager> {
	friend class Singleton<CameraManager>;

private:
	CameraManager() {
		Reset();
	}

public:
	void Reset() {
		for (u32 i = 0; i < cCameraMaxNum; i++) {
			mCamera[i] = nullptr;
		}
	}

public:
	static const u32 cCameraMaxNum = 16;

	Camera* GetCamera() const {
		for (u32 i = 0; i < cCameraMaxNum; i++) {
			if (mCamera[i] != nullptr) {
				return mCamera[i];
			}
		}
		return nullptr;
	}
	Camera* GetCamera(u32 aIndex) const {
		CPOT_ASSERT(aIndex < cCameraMaxNum);
		return mCamera[aIndex];
	}

	void SetCamera(Camera* aCamera, u32 aIndex) {
		CPOT_ASSERT(aIndex < cCameraMaxNum);
		mCamera[aIndex] = aCamera;
	}


private:
	Camera* mCamera[cCameraMaxNum];
};


}
