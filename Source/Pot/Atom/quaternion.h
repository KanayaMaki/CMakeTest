//
//	content	:	Quaternion�̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "defines.h"
#include "typedef.h"
#include "math.h"
#include "function.h"
#include "vector.h"


namespace cpot {

#pragma region Quaternion


class Quaternion {
public:
	f32 w;
	Vector3 v;


	//�R���X�g���N�^
	#pragma region

public:
	Quaternion() : w(1.0f), v(0.0f, 0.0f, 0.0f) {
	}
	Quaternion(f32 aX, f32 aY, f32 aZ, f32 aW) : v(aX, aY, aZ), w(aW) {

	}
	Quaternion(const Vector3& aAxis, f32 aRad) {
		*this = FromAxis(aAxis, aRad);
	}

	#pragma endregion


	//�������擾����
	#pragma region Getter

	Vector3 XAxis() const {
		return Right();
	}
	Vector3 YAxis() const {
		return Up();
	}
	Vector3 ZAxis() const {
		return Forward();
	}

	Vector3 Forward() const {
		return Rotate(Vector3::Forward());
	}
	Vector3 Back() const {
		return Rotate(Vector3::Back());
	}
	Vector3 Left() const {
		return Rotate(Vector3::Left());
	}
	Vector3 Right() const {
		return Rotate(Vector3::Right());
	}
	Vector3 Up() const {
		return Rotate(Vector3::Up());
	}
	Vector3 Down() const {
		return Rotate(Vector3::Down());
	}

	#pragma endregion


	//�v�Z
	#pragma region Calculate


	//�x�N�g������]������
	Vector3 Rotate(const Vector3& aVec) const {
		Quaternion p = Quaternion::FromVector(aVec);
		return ((-(*this)) * p * (*this)).v;
	}

	Vector2 Rotate(const Vector2& aVec) const {
		return Rotate(Vector3::FromVector2(aVec)).ToVector2();
	}


	//��]��K�p
	const Quaternion& operator *=(const Quaternion& aQ) {
		f32 tW = w;
		w = aQ.w * tW - v.Dot(aQ.v);
		v = aQ.v * tW + v * aQ.w + v.Cross(aQ.v);
		return *this;
	}
	Quaternion operator*(const Quaternion& aQ) const {
		Quaternion tRes(*this);
		tRes *= aQ;
		return tRes;
	}

	//���΂̉�]���쐬
	Quaternion operator -() const {
		Quaternion res(*this);
		res.v = -res.v;
		return res;
	}


	//���K������
	Quaternion Normal() const {
		Quaternion tRes(*this);
		f32 tLenQuad = tRes.w * tRes.w + tRes.v.x * tRes.v.x + tRes.v.y * tRes.v.y + tRes.v.z * tRes.v.z;

		if (NotZero(tLenQuad)) {
			f32 tLen = Sqrt(tLenQuad);
			tRes.w /= tLen;
			tRes.v /= tLen;
		}
		return tRes;
	}

	f32 Dot(const Quaternion& aOther) const {
		return v.x * aOther.v.x + v.y * aOther.v.y + v.z * aOther.v.z + w * aOther.w;
	}

	#pragma endregion


	//�쐬
	#pragma region Create

	//���Ɖ�]�ʂ���쐬����
	static Quaternion FromAxis(const Vector3& aV, f32 aRad) {
		Quaternion tRes;
		f32 tHalfRad = aRad / 2.0f;
		tRes.w = Cos(tHalfRad);
		tRes.v = -aV.Normal() * Sin(tHalfRad);	//����n�Ōv�Z���邽�߁A�����t�����ɂ���H��������Ƃ��܂�����
		return tRes;
	}

	//�x�N�^�[����쐬
	static Quaternion FromVector(const Vector3& aV) {
		Quaternion tQ;
		tQ.v = aV;
		tQ.w = 0.0f;
		return tQ;
	}

	//�x�N�^�[���m�̍�����쐬
	static Quaternion BetweenVector(const Vector3& aFrom, const Vector3& aTo) {
		Vector3 lFrom = aFrom.Normal();
		Vector3 lTo = aTo.Normal();

		f32 lCosTheta = lFrom.Dot(lTo);
		Vector3 lRotateAxis;

		f32 lErrorPermit = 0.001f;
		//�x�N�g�������Ε����������Ă���ꍇ
		if (lCosTheta < -1 + lErrorPermit) {
			lRotateAxis = Vector3(0.0f, 0.0f, 1.0f).Cross(lFrom);
			if (lRotateAxis.LenQuad() < 0.01f) {
				lRotateAxis = Vector3(1.0f, 0.0f, 0.0f).Cross(lFrom);
			}
			lRotateAxis = lRotateAxis.Normal();
			return FromAxis(lRotateAxis, ToRad(180.0f));
		}
		//�x�N�g�����قړ��������������Ă���ꍇ
		else if (lCosTheta > 1 - lErrorPermit) {
			return Quaternion::Unit();	//��]���Ȃ�
		}

		lRotateAxis = lFrom.Cross(lTo);

		f32 lAngle = Acos(lCosTheta);	//��̉�]�̊Ԃ̊p�x

		return FromAxis(lRotateAxis, lAngle);
	}


	#pragma endregion


	//��r
	#pragma region Compare

	BOOL operator==(const Quaternion& aQ) const {
		if (aQ.v != v) return false;
		if (!IsEqual(w, aQ.w)) return false;
		return true;
	}
	BOOL operator!=(const Quaternion& aQ) const {
		return !(*this == aQ);
	}

	#pragma endregion


	//�ÓI�Ȋ֐�
	#pragma region static

	static Quaternion XAxis(f32 rad) {
		return Quaternion(Vector3::Right(), rad);
	}
	static Quaternion YAxis(f32 rad) {
		return Quaternion(Vector3::Up(), rad);
	}
	static Quaternion ZAxis(f32 rad) {
		return Quaternion(Vector3::Forward(), rad);
	}
	static Quaternion Unit() {
		return Quaternion();
	}
	static Vector3 BaseDirection() {
		return Vector3::Forward();
	}

	#pragma endregion


	//������ɕϊ�����
	#pragma region ToString

	String<64> ToString() const {
		String<64> lRes;
		lRes += "(";
		lRes += "(";
		lRes += cpot::ToString::Do(v.x);
		lRes += ", ";
		lRes += cpot::ToString::Do(v.y);
		lRes += ", ";
		lRes += cpot::ToString::Do(v.z);
		lRes += ")";
		lRes += ", ";
		lRes += cpot::ToString::Do(w);
		lRes += ")";
		return lRes;
	}
	#pragma endregion


	//�w���p�֐�
	#pragma region Helper

	friend f32 BetweenAngle(const Quaternion& aFrom, const Quaternion& aTo) {
		f32 lCosTheta = aFrom.Dot(aTo);
		return Acos(Clamp(lCosTheta, -1.0f, 1.0f));
	}

	//�����ŕ⊮����B���ʕ��
	friend Quaternion SLerp(const Quaternion& aFrom, const Quaternion& aTo, f32 aRate) {

		f64 cosom = aFrom.v.x * aTo.v.x + aFrom.v.y * aTo.v.y +
			aFrom.v.z * aTo.v.z + aFrom.w * aTo.w;

		f32 aTo1[4];
		if (cosom < 0.0) {
			cosom = -cosom;
			aTo1[0] = -aTo.v.x;
			aTo1[1] = -aTo.v.y;
			aTo1[2] = -aTo.v.z;
			aTo1[3] = -aTo.w;
		}
		else {
			aTo1[0] = aTo.v.x;
			aTo1[1] = aTo.v.y;
			aTo1[2] = aTo.v.z;
			aTo1[3] = aTo.w;
		}


		f64 omega, sinom, scale0, scale1;

		cosom = Clamp01(cosom);

		if (NotZero(1.0 - cosom)) {
			omega = Acos(f32( cosom ));
			sinom = Sin(f32( omega ));
			scale0 = f32( Sin(f32( (1.0f - aRate) * omega) ) / sinom );
			scale1 = f32( Sin(f32(aRate * omega)) / sinom );
		}
		else {
			scale0 = 1.0 - aRate;
			scale1 = aRate;
		}

		Quaternion tRes;
		tRes.v.x = f32( scale0 * aFrom.v.x + scale1 * aTo1[0] );
		tRes.v.y = f32( scale0 * aFrom.v.y + scale1 * aTo1[1] );
		tRes.v.z = f32( scale0 * aFrom.v.z + scale1 * aTo1[2] );
		tRes.w = f32( scale0 * aFrom.w + scale1 * aTo1[3] );
		return tRes.Normal();
	}

	//�ő�p�x�܂ŕ⊮����B���ʕ��
	friend Quaternion SLerpLimit(const Quaternion& aFrom, const Quaternion& aTo, f32 aMaxRadian) {

		Quaternion lFrom = aFrom;
		Quaternion lTo = aTo;

		//
		if (aMaxRadian < 0.001f) {
			return lFrom;
		}

		f32 lCosTheta = lFrom.Dot(lTo);

		//��̉�]���قړ����ꍇ
		if (lCosTheta > 0.9999f) {
			return lTo;
		}

		//�Z���ق��̌o�H��⊮����悤�ɂ���
		if (lCosTheta < 0.0f) {
			lFrom = -lFrom;
			lCosTheta *= -1.0f;
		}

		f32 lBetweenRadian = Acos(lCosTheta);	//��̉�]�̊Ԃ̊p�x

		//��������ꍇ
		if (lBetweenRadian < aMaxRadian) {
			return lTo;
		}

		f32 lT = aMaxRadian / lBetweenRadian;

		return SLerp(aFrom, aTo, lT);
	}

	#pragma endregion

};

#pragma endregion


}