//
//	content	:	Matrix4x4の実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "defines.h"
#include "typedef.h"
#include "math.h"
#include "function.h"
#include "vector.h"
#include "quaternion.h"


namespace cpot {


#pragma region Matrix4x4


class Matrix4x4 {

	//メンバ
	#pragma region Member

public:
	union {
		struct {
			f32 _11, _12, _13, _14;
			f32 _21, _22, _23, _24;
			f32 _31, _32, _33, _34;
			f32 _41, _42, _43, _44;
		};
		f32 v[4][4];
		Vector4 vec[4];
	};

	#pragma endregion


	//コンストラクタ
	#pragma region Constructor

public:
	Matrix4x4() {
		///*
		for (s32 i = 0; i < 4; i++) {
			for (s32 j = 0; j < 4; j++) {
				v[i][j] = 0.0f;
			}
			v[i][i] = 1.0f;
		}//*/

		//対角成分だけ1.0f
		v[0][0] = 1.0f;
		v[1][1] = 1.0f;
		v[2][2] = 1.0f;
		v[3][3] = 1.0f;
	}

	Matrix4x4(const Vector4& aV0, const Vector4& aV1, const Vector4& aV2, const Vector4& aV3) {
		vec[0] = aV0;
		vec[1] = aV1;
		vec[2] = aV2;
		vec[3] = aV3;
	}

	Matrix4x4(const Quaternion& aRotation) {
		*this = FromRotate(aRotation);
	}
	Matrix4x4(const Vector3& aTransform) {
		*this = FromTransform(aTransform);
	}
	Matrix4x4(const Quaternion& aRotation, const Vector3& aTransform) {
		*this = FromRotate(aRotation) * FromTransform(aTransform);
	}
	Matrix4x4(const Quaternion& aRotation, const Vector3& aTransform, const Vector3& aScale) {
		*this = FromScale(aScale) * FromRotate(aRotation) * FromTransform(aTransform);
	}

private:
	//初期化を行わない、効率化用
	Matrix4x4(s32 aDummy) {

	}

	#pragma endregion


	//matrixを作成する
	#pragma region Create

public:
	static Matrix4x4 Unit() {
		return Matrix4x4();
	}

	static Matrix4x4 FromRotate(const Quaternion& aRotate) {
		Matrix4x4 tRes = Unit();
		f32 q0 = aRotate.w; f32 q1 = aRotate.v.x;
		f32 q2 = aRotate.v.y; f32 q3 = aRotate.v.z;

		tRes._11 = q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3;
		tRes._12 = 2 * (q1 * q2 - q0 * q3);
		tRes._13 = 2 * (q1 * q3 + q0 * q2);
		tRes._21 = 2 * (q1 * q2 + q0 * q3);
		tRes._22 = q0 * q0 - q1 * q1 + q2 * q2 - q3 * q3;
		tRes._23 = 2 * (q2 * q3 - q0 * q1);
		tRes._31 = 2 * (q1 * q3 - q0 * q2);
		tRes._32 = 2 * (q2 * q3 + q0 * q1);
		tRes._33 = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
		return tRes;
	}
	static Matrix4x4 FromTransform(const Vector3& aTransform) {
		Matrix4x4 tRes = Unit();
		tRes._41 = aTransform.x;
		tRes._42 = aTransform.y;
		tRes._43 = aTransform.z;
		return tRes;
	}
	static Matrix4x4 FromScale(const Vector3& aScale) {
		Matrix4x4 tRes = Unit();
		tRes._11 *= aScale.x;
		tRes._22 = aScale.y;
		tRes._33 = aScale.z;
		return tRes;
	}


	#pragma endregion


	//計算する
	#pragma region Calculate

public:
	friend Vector3 operator *(const Vector3& aV, const Matrix4x4& aMat) {
		Vector4 lRes = Vector4::FromVector3(aV) * aMat;
		return lRes.ToVector3() / lRes.w;
	}
	friend Vector4 operator *(const Vector4& aV, const Matrix4x4& aMat) {
		Vector4 p(aV);
		Vector4 tRes;
		tRes.x = p.x * aMat._11 + p.y * aMat._21 + p.z * aMat._31 + p.w * aMat._41;
		tRes.y = p.x * aMat._12 + p.y * aMat._22 + p.z * aMat._32 + p.w * aMat._42;
		tRes.z = p.x * aMat._13 + p.y * aMat._23 + p.z * aMat._33 + p.w * aMat._43;
		tRes.w = p.x * aMat._14 + p.y * aMat._24 + p.z * aMat._34 + p.w * aMat._44;
		return tRes;
	}

	const Matrix4x4& operator *=(const Matrix4x4& aM) {
		Matrix4x4 tRes(-1);
		for (s32 i = 0; i < 4; i++) {
			for (s32 j = 0; j < 4; j++) {
				tRes.v[i][j] = 0.0f;
				for (s32 k = 0; k < 4; k++) {
					tRes.v[i][j] += v[i][k] * aM.v[k][j];
				}
			}
		}
		*this = tRes;
		return *this;
	}
	Matrix4x4 operator *(const Matrix4x4& aM) {
		Matrix4x4 tRes = *this;
		tRes *= aM;
		return tRes;
	}

	const Matrix4x4& operator *=(f32 aV) {
		for (s32 i = 0; i < 4; i++) {
			for (s32 j = 0; j < 4; j++) {
				v[i][j] *= aV;
			}
		}
		return *this;
	}
	Matrix4x4 operator *(f32 aV) {
		Matrix4x4 lResult = *this;
		lResult *= aV;
		return lResult;
	}

	#pragma endregion


	//その他
	#pragma region Other

public:
	//転置行列を取得
	Matrix4x4 T() const {
		Matrix4x4 lResult(-1);
		for (s32 i = 0; i < 4; i++) {
			for (s32 j = 0; j < 4; j++) {
				lResult.v[i][j] = v[j][i];
			}
		}
		return lResult;
	}


	//逆行列を取得
	Matrix4x4 Inverse() const {
		
		f32 coef00 = v[2][2] * v[3][3] - v[3][2] * v[2][3];
		f32 coef02 = v[1][2] * v[3][3] - v[3][2] * v[1][3];
		f32 coef03 = v[1][2] * v[2][3] - v[2][2] * v[1][3];

		f32 coef04 = v[2][1] * v[3][3] - v[3][1] * v[2][3];
		f32 coef06 = v[1][1] * v[3][3] - v[3][1] * v[1][3];
		f32 coef07 = v[1][1] * v[2][3] - v[2][1] * v[1][3];

		f32 coef08 = v[2][1] * v[3][2] - v[3][1] * v[2][2];
		f32 coef10 = v[1][1] * v[3][2] - v[3][1] * v[1][2];
		f32 coef11 = v[1][1] * v[2][2] - v[2][1] * v[1][2];

		f32 coef12 = v[2][0] * v[3][3] - v[3][0] * v[2][3];
		f32 coef14 = v[1][0] * v[3][3] - v[3][0] * v[1][3];
		f32 coef15 = v[1][0] * v[2][3] - v[2][0] * v[1][3];

		f32 coef16 = v[2][0] * v[3][2] - v[3][0] * v[2][2];
		f32 coef18 = v[1][0] * v[3][2] - v[3][0] * v[1][2];
		f32 coef19 = v[1][0] * v[2][2] - v[2][0] * v[1][2];

		f32 coef20 = v[2][0] * v[3][1] - v[3][0] * v[2][1];
		f32 coef22 = v[1][0] * v[3][1] - v[3][0] * v[1][1];
		f32 coef23 = v[1][0] * v[2][1] - v[2][0] * v[1][1];


		Vector4 fac0(coef00, coef00, coef02, coef03);
		Vector4 fac1(coef04, coef04, coef06, coef07);
		Vector4 fac2(coef08, coef08, coef10, coef11);
		Vector4 fac3(coef12, coef12, coef14, coef15);
		Vector4 fac4(coef16, coef16, coef18, coef19);
		Vector4 fac5(coef20, coef20, coef22, coef23);

		Vector4 vec0(v[1][0], v[0][0], v[0][0], v[0][0]);
		Vector4 vec1(v[1][1], v[0][1], v[0][1], v[0][1]);
		Vector4 vec2(v[1][2], v[0][2], v[0][2], v[0][2]);
		Vector4 vec3(v[1][3], v[0][3], v[0][3], v[0][3]);


		Vector4 inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
		Vector4 inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
		Vector4 inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
		Vector4 inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

		Vector4 signA(1.0f, -1.0f, 1.0f, -1.0f);
		Vector4 signB(-1.0f, 1.0f, -1.0f, 1.0f);

		Matrix4x4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);
		Vector4 dot0(v[0][0] * inverse.v[0][0], v[0][1] * inverse.v[1][0], v[0][2] * inverse.v[2][0], v[0][3] * inverse.v[3][0]);

		f32 dot = dot0.x + dot0.y + dot0.z + dot0.w;

		if (IsZero(dot)) {
			return Unit();
		}

		f32 oneOverDeterminant = 1.0f / dot;

		return inverse * oneOverDeterminant;
	}

	#pragma endregion

};

#pragma endregion


#pragma region ShaderMatrix4x4


//シェーダで使用する際のMatrix
//環境などによって、転置行列が必要だったりするのを吸収してくれる
class ShaderMatrix4x4 {
public:
	const ShaderMatrix4x4& operator=(const Matrix4x4& aM) {
		mM = aM.T();
		return *this;
	}
	operator Matrix4x4 () {
		return mM.T();
	}

private:
	Matrix4x4 mM;
};


#pragma endregion



}