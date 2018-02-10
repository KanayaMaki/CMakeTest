//
//	content	:	Transformの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "defines.h"
#include "typedef.h"
#include "math.h"
#include "function.h"

#include "vector.h"
#include "quaternion.h"
#include "matrix4x4.h"


namespace cpot {


//Transform
#pragma region Transform

class Transform {

	//フィールド
	#pragma region Field

public:
	Quaternion mRotation;
	Vector3 mPosition;
	Vector3 mScale;

	#pragma endregion


public:
	Transform() : mRotation(Quaternion::Unit()), mPosition(Vector3::Zero()), mScale(Vector3::One()) {}
	Transform(const Vector3& aPosition) : mRotation(Quaternion::Unit()), mPosition(aPosition), mScale(Vector3::One()) {}
	Transform(const Quaternion& aRotation) : mRotation(aRotation), mPosition(Vector3::Zero()), mScale(Vector3::One()) {}
	Transform(const Quaternion& aRotation, const Vector3& aPosition) : mRotation(aRotation), mPosition(aPosition), mScale(Vector3::One()) {}
	Transform(const Quaternion& aRotation, const Vector3& aPosition, const Vector3& aScale) : mRotation(aRotation), mPosition(aPosition), mScale(aScale) {}

	Matrix4x4 GetMatrix() const {
		Matrix4x4 lM;
		lM *= Matrix4x4::FromScale(mScale);
		lM *= Matrix4x4::FromRotate(mRotation);
		lM *= Matrix4x4::FromTransform(mPosition);
		return lM;
	}
	Matrix4x4 GetInverseMatrix() const {
		Matrix4x4 lM;
		lM *= Matrix4x4::FromTransform(-mPosition);
		lM *= Matrix4x4::FromRotate(-mRotation);
		lM *= Matrix4x4::FromScale(Vector3::One() / mScale);
		return lM;
	}

	BOOL operator ==(const Transform& aT) const {
		if (mRotation != aT.mRotation) return false;
		if (mPosition != aT.mPosition) return false;
		if (mScale != aT.mScale) return false;
		return true;
	}
	BOOL operator !=(const Transform& aT) {
		return !((*this) == aT);
	}

	friend Transform Lerp(const Transform& aFrom, const Transform& aTo, f32 aRate) {
		return Transform(SLerp(aFrom.mRotation, aTo.mRotation, aRate), Lerp(aFrom.mPosition, aTo.mPosition, aRate), Lerp(aFrom.mScale, aTo.mScale, aRate));
	}
};

#pragma endregion


}