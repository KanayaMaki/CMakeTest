//
//	content	:	Vector2, Point2などの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "defines.h"
#include "typedef.h"
#include "math.h"
#include "function.h"
#include "string.h"


namespace cpot {


//2つのf32を持つクラス
#pragma region Vector2

class Vector2 {
public:
	f32 x, y;

public:
	//コンストラクタ
	#pragma region Constructor

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(f32 aX, f32 aY) : x(aX), y(aY) {}

	#pragma endregion


	//値を設定する
	#pragma region Setter

	Vector2 X(f32 aV) const {
		return Vector2(aV, y);
	}
	Vector2 Y(f32 aV) const {
		return Vector2(x, aV);
	}
	Vector2 XY(f32 aV) const {
		return Vector2(aV, aV);
	}

	#pragma endregion

	//値を取得する
	#pragma region Getter

	f32 X() const {
		return x;
	}
	f32 Y() const {
		return y;
	}
	Vector2 XX() const {
		return Vector2(x, x);
	}
	Vector2 XY() const {
		return Vector2(x, y);
	}
	Vector2 YX() const {
		return Vector2(y, x);
	}
	Vector2 YY() const {
		return Vector2(y, y);
	}

	#pragma endregion


	//計算のオペレータ
	#pragma region Calculate

	const Vector2& operator +=(const Vector2& aVal) {
		x += aVal.x;
		y += aVal.y;
		return *this;
	}
	Vector2 operator +(const Vector2& aVal) const {
		Vector2 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	const Vector2& operator -=(const Vector2& aVal) {
		x -= aVal.x;
		y -= aVal.y;
		return *this;
	}
	Vector2 operator -(const Vector2& aVal) const {
		Vector2 tRes(*this);
		tRes -= aVal;
		return tRes;
	}

	const Vector2& operator *=(f32 aVal) {
		x *= aVal;
		y *= aVal;
		return *this;
	}
	Vector2 operator *(f32 aVal) const {
		Vector2 tRes(*this);
		tRes *= aVal;
		return tRes;
	}
	
	const Vector2& operator *=(const Vector2& aVal) {
		x *= aVal.x;
		y *= aVal.y;
		return *this;
	}
	Vector2 operator *(const Vector2& aVal) const {
		Vector2 tRes(*this);
		tRes *= aVal;
		return tRes;
	}

	const Vector2& operator /=(f32 aVal) {
		CPOT_ASSERT(NotZero(aVal));	//０では割れない
		x /= aVal;
		y /= aVal;
		return *this;
	}
	Vector2 operator /(f32 aVal) const {
		Vector2 result(*this);
		result /= aVal;
		return result;
	}

	const Vector2& operator /=(const Vector2& aVal) {
		CPOT_ASSERT(NotZero(aVal.x));	//０では割れない
		CPOT_ASSERT(NotZero(aVal.y));	//０では割れない
		x /= aVal.x;
		y /= aVal.y;
		return *this;
	}
	Vector2 operator /(const Vector2& aVal) const {
		Vector2 result(*this);
		result /= aVal;
		return result;
	}

	Vector2 operator -() const {
		Vector2 result(-x, -y);
		return result;
	}

	#pragma endregion

	//比較のオペレータ
	#pragma region Compare
	BOOL operator ==(const Vector2& aVal) const {
		//少しの誤差は認める
		if (!IsEqual(x, aVal.x, cFloatEpsilon * Abs(x))) return false;
		if (!IsEqual(y, aVal.y, cFloatEpsilon * Abs(y))) return false;
		return true;
	}
	BOOL operator !=(const Vector2& aVal) const {
		return !(*this == aVal);
	}

	BOOL operator <(const Vector2& aOther) const {
		return LenQuad() < aOther.LenQuad();
	}
	BOOL operator >=(const Vector2& aOther) const {
		return !(*this < aOther);
	}
	BOOL operator >(const Vector2& aOther) const {
		return LenQuad() > aOther.LenQuad();
	}
	BOOL operator <=(const Vector2& aOther) const {
		return !(*this > aOther);
	}

	#pragma endregion


	//その他計算
	#pragma region Other

	//ベクトルの長さ
	f32 Len() const {
		return Sqrt(LenQuad());
	}
	//ベクトルの長さの二乗
	f32 LenQuad() const {
		return (x * x) + (y * y);
	}

	//正規化
	Vector2 Normal() const {
		return *this / Len();
	}
	//0除算をしない正規化
	Vector2 NormalSafe() const {
		f32 tLen = Len();

		if (IsZero(tLen)) {
			return *this;	//長さが0の時だけそのまま返す
		}
		return *this / tLen;
	}

	
	//外積
	f32 Cross(const Vector2& aVec) const {
		return x * aVec.y - y * aVec.x;
	}
	//内積
	f32 Dot(const Vector2& aVec) const {
		return x * aVec.x + y *  aVec.y;
	}

	#pragma endregion


	//その他静的な関数
	#pragma region Static

	static Vector2 FromFloat2(const f32* aVal) {
		return Vector2(aVal[0], aVal[1]);
	}

	//基本となる単位ベクトル
	static Vector2 Unit() {
		return Vector2(1.0f, 0.0f);
	}
	static Vector2 One() {
		return Vector2(1.0f, 1.0f);
	}
	static Vector2 Zero() {
		return Vector2(0.0f, 0.0f);
	}

	//それぞれの方向を表すベクトル
	static Vector2 Left() {
		return Vector2(-1.0f, 0.0f);
	}
	static Vector2 Right() {
		return Vector2(1.0f, 0.0f);
	}
	static Vector2 Up() {
		return Vector2(0.0f, 1.0f);
	}
	static Vector2 Down() {
		return Vector2(0.0f, -1.0f);
	}

	#pragma endregion


	//float値の配列を取得する
	#pragma region ToFloat

	struct Float2 {
		float v[2];
	};
	Float2 ToFloat2() const {
		Float2 t = { x, y };
		return t;
	}

	#pragma endregion


	//文字列に変換する
	#pragma region ToString

	String<32> ToString() const {
		String<32> lRes;
		lRes += "(";
		lRes += cpot::ToString::Do(x);
		lRes += ", ";
		lRes += cpot::ToString::Do(y);
		lRes += ")";
		return lRes;
	}
	#pragma endregion


	//ヘルパ関数
	#pragma region Helper

	friend Vector2 Lerp(const Vector2& aFrom, const Vector2& aTo, f32 aRate) {
		return aFrom * (1.0f - aRate) + aTo * aRate;
	}

	//それぞれの最大の要素を選ぶ
	friend Vector2 MaxElement(const Vector2& aVal1, const Vector2& aVal2) {
		Vector2 tRes(Max(aVal1.x, aVal2.x), Max(aVal1.x, aVal2.y));
		return tRes;
	}
	friend Vector2 MinElement(const Vector2& aVal1, const Vector2& aVal2) {
		Vector2 tRes(Min(aVal1.x, aVal2.x), Min(aVal1.y, aVal2.y));
		return tRes;
	}

	#pragma endregion
};

#pragma endregion


//3つのf32を持つクラス
#pragma region Vector3

class Vector3 {
public:
	f32 x, y, z;


	//コンストラクタ
	#pragma region Constructor

public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(f32 aX, f32 aY, f32 aZ) : x(aX), y(aY), z(aZ) {}

	#pragma endregion


	//値を設定する
	#pragma region Setter

	Vector3 X(f32 aV) const {
		return Vector3(aV, y, z);
	}
	Vector3 Y(f32 aV) const {
		return Vector3(x, aV, z);
	}
	Vector3 Z(f32 aV) const {
		return Vector3(x, y, aV);
	}
	Vector3 XY(f32 aV) const {
		return Vector3(aV, aV, z);
	}
	Vector3 XZ(f32 aV) const {
		return Vector3(aV, y, aV);
	}
	Vector3 YZ(f32 aV) const {
		return Vector3(x, aV, aV);
	}
	Vector3 XYZ(f32 aV) const {
		return Vector3(aV, aV, aV);
	}

	Vector3 XY(f32 aX, f32 aY) const {
		return Vector3(aX, aY, z);
	}
	Vector3 XZ(f32 aX, f32 aZ) const {
		return Vector3(aX, y, aZ);
	}
	Vector3 YZ(f32 aY, f32 aZ) const {
		return Vector3(x, aY, aZ);
	}

	Vector3 XY(const Vector2& aV) const {
		return Vector3(aV.x, aV.y, z);
	}
	Vector3 YX(const Vector2& aV) const {
		return Vector3(aV.y, aV.x, z);
	}
	Vector3 XZ(const Vector2& aV) const {
		return Vector3(aV.x, y, aV.y);
	}
	Vector3 ZX(const Vector2& aV) const {
		return Vector3(aV.y, y, aV.x);
	}
	Vector3 YZ(const Vector2& aV) const {
		return Vector3(x, aV.x, aV.y);
	}
	Vector3 ZY(const Vector2& aV) const {
		return Vector3(x, aV.y, aV.x);
	}

	#pragma endregion

	//値を取得する
	#pragma region Getter

	//f32
	#pragma region f32

	f32 X() const {
		return x;
	}
	f32 Y() const {
		return y;
	}
	f32 Z() const {
		return z;
	}

	#pragma endregion


	//Vector2
	#pragma region Vector2

	Vector2 XX() const {
		return Vector2(x, x);
	}
	Vector2 XY() const {
		return Vector2(x, y);
	}
	Vector2 XZ() const {
		return Vector2(x, z);
	}

	Vector2 YX() const {
		return Vector2(y, x);
	}
	Vector2 YY() const {
		return Vector2(y, y);
	}
	Vector2 YZ() const {
		return Vector2(y, z);
	}

	Vector2 ZX() const {
		return Vector2(z, x);
	}
	Vector2 ZY() const {
		return Vector2(z, y);
	}
	Vector2 ZZ() const {
		return Vector2(z, z);
	}

	Vector2 ToVector2() const {
		return Vector2(x, y);
	}

	#pragma endregion


	#pragma endregion


	//計算のオペレータ
	#pragma region Calculate

	//Plus
	#pragma region

	const Vector3& operator +=(const Vector3& aVal) {
		x += aVal.x;
		y += aVal.y;
		z += aVal.z;
		return *this;
	}
	Vector3 operator +(const Vector3& aVal) const {
		Vector3 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	const Vector3& operator +=(f32 aVal) {
		x += aVal;
		y += aVal;
		z += aVal;
		return *this;
	}

	Vector3 operator +(f32 aVal) const {
		Vector3 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	#pragma endregion

	//Sub
	#pragma region

	const Vector3& operator -=(const Vector3& aVal) {
		x -= aVal.x;
		y -= aVal.y;
		z -= aVal.z;
		return *this;
	}
	Vector3 operator -(const Vector3& aVal) const {
		Vector3 tRes = *this;
		tRes -= aVal;
		return tRes;
	}
	const Vector3& operator -=(f32 aVal) {
		x -= aVal;
		y -= aVal;
		z -= aVal;
		return *this;
	}
	Vector3 operator -(f32 aVal) const {
		Vector3 tRes = *this;
		tRes -= aVal;
		return tRes;
	}

	#pragma endregion

	//Multi
	#pragma region Multi

	const Vector3& operator *=(f32 aVal) {
		x *= aVal;
		y *= aVal;
		z *= aVal;
		return *this;
	}
	Vector3 operator *(f32 aVal) const {
		Vector3 tRes = *this;
		tRes *= aVal;
		return tRes;
	}

	const Vector3& operator *=(const Vector3 aVal) {
		x *= aVal.x;
		y *= aVal.y;
		z *= aVal.z;
		return *this;
	}
	Vector3 operator *(const Vector3& aVal) const {
		Vector3 tRes = *this;
		tRes *= aVal;
		return tRes;
	}

	#pragma endregion

	//Div
	#pragma region Div

	const Vector3& operator /=(f32 aVal) {
		CPOT_ASSERT(NotZero(aVal));	//０ではないことを保証
		x /= aVal;
		y /= aVal;
		z /= aVal;
		return *this;
	}
	Vector3 operator /(f32 aVal) const {
		Vector3 tRes = *this;
		tRes /= aVal;
		return tRes;
	}

	const Vector3& operator /=(const Vector3& aVal) {
		CPOT_ASSERT(NotZero(aVal.x));	//０ではないことを保証
		CPOT_ASSERT(NotZero(aVal.y));	//０ではないことを保証
		CPOT_ASSERT(NotZero(aVal.z));	//０ではないことを保証
		x /= aVal.x;
		y /= aVal.y;
		z /= aVal.z;
		return *this;
	}
	Vector3 operator /(const Vector3& aVal) const {
		Vector3 tRes = *this;
		tRes /= aVal;
		return tRes;
	}

	#pragma endregion


	Vector3 operator -() const {
		Vector3 tRes(-x, -y, -z);
		return tRes;
	}

	#pragma endregion


	//比較のオペレータ
	#pragma region Compare

	BOOL operator ==(const Vector3& aVal) const {
		if (!IsEqual(x, aVal.x)) return false;
		if (!IsEqual(y, aVal.y)) return false;
		if (!IsEqual(z, aVal.z)) return false;
		return true;
	}
	BOOL operator !=(const Vector3& aVal) const {
		return !(*this == aVal);
	}

	BOOL operator <(const Vector3& aOther) const {
		return LenQuad() < aOther.LenQuad();
	}
	BOOL operator >=(const Vector3& aOther) const {
		return !(*this < aOther);
	}
	BOOL operator >(const Vector3& aOther) const {
		return LenQuad() > aOther.LenQuad();
	}
	BOOL operator <=(const Vector3& aOther) const {
		return !(*this > aOther);
	}

	#pragma endregion


	//その他計算
	#pragma region Other

	//ベクトルの長さを返す
	f32 Len() const {
		return Sqrt(LenQuad());
	}
	//ベクトルの長さの二乗を返す
	f32 LenQuad() const {
		return x * x + y * y + z * z;
	}

	//正規化する
	Vector3 Normal() const {
		return *this / Len();
	}
	Vector3 NormalSafe() const {
		f32 tLen = Len();
		if (IsZero(tLen)) {
			return *this;	//もし長さが0なら自身を返す
		}
		return *this / tLen;
	}


	//外積
	Vector3 Cross(const Vector3& aVal) const {
		return Vector3(
			y * aVal.z - z * aVal.y,
			z * aVal.x - x * aVal.z,
			x * aVal.y - y * aVal.x
		);
	}
	//内積
	f32 Dot(const Vector3& aVal) const {
		return x * aVal.x + y *  aVal.y + z * aVal.z;
	}

	#pragma endregion


	//静的な関数
	#pragma region Static

	static Vector3 FromVector2(const Vector2& aVal) {
		return Vector3(aVal.x, aVal.y, 0.0f);
	}
	static Vector3 FromFloat3(const f32* aVal) {
		return Vector3(aVal[0], aVal[1], aVal[2]);
	}

	static Vector3 Unit() {
		return Vector3(1.0f, 0.0f, 0.0f);
	}
	static Vector3 One() {
		return Vector3(1.0f, 1.0f, 1.0f);
	}
	static Vector3 Zero() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	static Vector3 Forward() {
		return Vector3().Z(1.0f);
	}
	static Vector3 Back() {
		return Vector3().Z(-1.0f);
	}
	static Vector3 Up() {
		return Vector3().Y(1.0f);
	}
	static Vector3 Down() {
		return Vector3().Y(-1.0f);
	}
	static Vector3 Left() {
		return Vector3().X(-1.0f);
	}
	static Vector3 Right() {
		return Vector3().X(1.0f);
	}

	#pragma endregion


	//float値の配列を取得する
	#pragma region ToFloat

	struct Float3 {
		float v[3];
	};
	Float3 ToFloat3() const {
		Float3 t = { x, y, z };
		return t;
	}

	#pragma endregion


	//文字列に変換する
	#pragma region ToString

public:
	String<64> ToString() const {
		String<64> lRes;
		lRes += "(";
		lRes += cpot::ToString::Do(x);
		lRes += ", ";
		lRes += cpot::ToString::Do(y);
		lRes += ", ";
		lRes += cpot::ToString::Do(z);
		lRes += ")";
		return lRes;
	}

	#pragma endregion


	//ヘルパ関数
	#pragma region Helper

	//線形補間
	friend Vector3 Lerp(const Vector3& aFrom, const Vector3& aTo, f32 aRate) {
		return aFrom * (1.0f - aRate) + aTo * aRate;
	}

	//それぞれの最大の要素を選ぶ
	friend Vector3 MaxElement(const Vector3& aVal1, const Vector3& aVal2) {
		Vector3 tRes(Max(aVal1.x, aVal2.x), Max(aVal1.y, aVal2.y), Max(aVal1.z, aVal2.z));
		return tRes;
	}
	friend Vector3 MinElement(const Vector3& aVal1, const Vector3& aVal2) {
		Vector3 tRes(Min(aVal1.x, aVal2.x), Min(aVal1.y, aVal2.y), Min(aVal1.z, aVal2.z));
		return tRes;
	}

	#pragma endregion

};

#pragma endregion


//4つのf32を持つクラス
#pragma region Vector4

class Vector4 {
public:
	f32 x, y, z, w;


	//コンストラクタ
	#pragma region Constructor

public:
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(f32 aX, f32 aY, f32 aZ, f32 aW) : x(aX), y(aY), z(aZ), w(aW) {}

	#pragma endregion

	
	//値を設定する
	#pragma region Setter

	Vector4 X(f32 aVal) const {
		return Vector4(aVal, y, z, w);
	}
	Vector4 Y(f32 aVal) const {
		return Vector4(x, aVal, z, w);
	}
	Vector4 Z(f32 aVal) const {
		return Vector4(x, y, aVal, w);
	}
	Vector4 W(f32 aVal) const {
		return Vector4(x, y, z, aVal);
	}
	Vector4 XY(f32 aVal) const {
		return Vector4(aVal, aVal, z, w);
	}
	Vector4 XZ(f32 aVal) const {
		return Vector4(aVal, y, aVal, w);
	}
	Vector4 XW(f32 aVal) const {
		return Vector4(aVal, y, z, aVal);
	}
	Vector4 YZ(f32 aVal) const {
		return Vector4(x, aVal, aVal, w);
	}
	Vector4 YW(f32 aVal) const {
		return Vector4(x, aVal, z, aVal);
	}
	Vector4 ZW(f32 aVal) const {
		return Vector4(x, y, aVal, aVal);
	}
	Vector4 XYZ(f32 aVal) const {
		return Vector4(aVal, aVal, aVal, w);
	}
	Vector4 XYZW(f32 aVal) const {
		return Vector4(aVal, aVal, aVal, aVal);
	}

	#pragma endregion

	//値を取得する
	#pragma region Getter

	#pragma region f32

	f32 X() const {
		return x;
	}
	f32 Y() const {
		return y;
	}
	f32 Z() const {
		return z;
	}
	f32 W() const {
		return w;
	}

	#pragma endregion

	#pragma region Vector2

	Vector2 XX() const {
		return Vector2(x, x);
	}
	Vector2 XY() const {
		return Vector2(x, y);
	}
	Vector2 XZ() const {
		return Vector2(x, z);
	}
	Vector2 XW() const {
		return Vector2(x, w);
	}

	Vector2 YX() const {
		return Vector2(y, x);
	}
	Vector2 YY() const {
		return Vector2(y, y);
	}
	Vector2 YZ() const {
		return Vector2(y, z);
	}
	Vector2 YW() const {
		return Vector2(y, w);
	}

	Vector2 ZX() const {
		return Vector2(z, x);
	}
	Vector2 ZY() const {
		return Vector2(z, y);
	}
	Vector2 ZZ() const {
		return Vector2(z, z);
	}
	Vector2 ZW() const {
		return Vector2(z, w);
	}

	Vector2 WX() const {
		return Vector2(w, x);
	}
	Vector2 WY() const {
		return Vector2(w, y);
	}
	Vector2 WZ() const {
		return Vector2(w, z);
	}
	Vector2 WW() const {
		return Vector2(w, w);
	}

	#pragma endregion

	Vector3 XYZ() const {
		return Vector3(x, y, z);
	}

	Vector3 ToVector3() const {
		return Vector3(x, y, z);
	}

	#pragma endregion


	//計算のオペレータ
	#pragma region Calculate

	#pragma region Plus

	const Vector4& operator +=(const Vector4& aVal) {
		x += aVal.x;
		y += aVal.y;
		z += aVal.z;
		w += aVal.w;
		return *this;
	}
	Vector4 operator +(const Vector4& aVal) const {
		Vector4 tResult = *this;
		tResult += aVal;
		return tResult;
	}

	const Vector4& operator +=(f32 aVal) {
		x += aVal;
		y += aVal;
		z += aVal;
		w += aVal;
		return *this;
	}
	Vector4 operator +(f32 aVal) const {
		Vector4 tResult = *this;
		tResult += aVal;
		return tResult;
	}

	#pragma endregion


	#pragma region Sub

	const Vector4& operator -=(const Vector4& aVal) {
		x -= aVal.x;
		y -= aVal.y;
		z -= aVal.z;
		w -= aVal.w;
		return *this;
	}
	Vector4 operator -(const Vector4& aVal) const {
		Vector4 tResult = *this;
		tResult -= aVal;
		return tResult;
	}
	const Vector4& operator -=(f32 aVal) {
		x -= aVal;
		y -= aVal;
		z -= aVal;
		w -= aVal;
		return *this;
	}
	Vector4 operator -(f32 aVal) const {
		Vector4 tResult = *this;
		tResult -= aVal;
		return tResult;
	}

	#pragma endregion

	
	#pragma region Multi

	const Vector4& operator *=(f32 aVal) {
		x *= aVal;
		y *= aVal;
		z *= aVal;
		w *= aVal;
		return *this;
	}
	Vector4 operator *(f32 aVal) const {
		Vector4 tResult = *this;
		tResult *= aVal;
		return tResult;
	}

	const Vector4& operator *=(const Vector4& aVal) {
		x *= aVal.x;
		y *= aVal.y;
		z *= aVal.z;
		w *= aVal.w;
		return *this;
	}
	Vector4 operator *(const Vector4& aVal) const {
		Vector4 tResult = *this;
		tResult *= aVal;
		return tResult;
	}

	#pragma endregion

	
	#pragma region Div

	const Vector4& operator /=(f32 aVal) {
		CPOT_ASSERT(NotZero(aVal));	//０ではないことを保証
		x /= aVal;
		y /= aVal;
		z /= aVal;
		w /= aVal;
		return *this;
	}
	Vector4 operator /(f32 aVal) const {
		Vector4 tResult = *this;
		tResult /= aVal;
		return tResult;
	}

	#pragma endregion

	
	Vector4 operator -() const {
		Vector4 tResult(-x, -y, -z, -w);
		return tResult;
	}

	#pragma endregion


	//比較のオペレータ
	#pragma region Compare

	BOOL operator ==(const Vector4& aVal) const {
		//少しの誤差を認める
		if (!IsEqual(x, aVal.x, cFloatEpsilon * Max(Abs(x), Abs(aVal.x)))) return false;
		if (!IsEqual(y, aVal.y, cFloatEpsilon * Max(Abs(y), Abs(aVal.y)))) return false;
		if (!IsEqual(z, aVal.z, cFloatEpsilon * Max(Abs(z), Abs(aVal.z)))) return false;
		if (!IsEqual(w, aVal.w, cFloatEpsilon * Max(Abs(w), Abs(aVal.w)))) return false;
		return true;
	}
	BOOL operator !=(const Vector4& aVal) const {
		return !(*this == aVal);
	}

	BOOL operator <(const Vector4& aOther) {
		return LenQuad() < aOther.LenQuad();
	}
	BOOL operator >=(const Vector4& aOther) {
		return !(*this < aOther);
	}
	BOOL operator >(const Vector4& aOther) {
		return LenQuad() > aOther.LenQuad();
	}
	BOOL operator <=(const Vector4& aOther) {
		return !(*this > aOther);
	}

	#pragma endregion


	//その他計算
	#pragma region Other

	//ベクトルの長さを返す
	f32 Len() const {
		return Sqrt(LenQuad());
	}
	//ベクトルの長さの二乗を返す
	f32 LenQuad() const {
		return x * x + y * y + z * z + w * w;
	}

	//正規化する。長さが０の場合は、基本ベクトルを返す
	Vector4 Normal() const {
		return *this / Len();
	}
	Vector4 NormalSafe() const {
		f32 len = Len();
		if (IsZero(len)) {
			return *this;
		}
		return *this / len;
	}

	#pragma endregion


	//float値の配列を取得する
	#pragma region ToFloat

	struct Float4 {
		float v[4];
	};
	Float4 ToFloat4() const {
		Float4 t = { x, y, z, w };
		return t;
	}

	#pragma endregion



	//文字列に変換する
	#pragma region ToString

public:
	String<64> ToString() const {
		String<64> lRes;
		lRes += "(";
		lRes += cpot::ToString::Do(x);
		lRes += ", ";
		lRes += cpot::ToString::Do(y);
		lRes += ", ";
		lRes += cpot::ToString::Do(z);
		lRes += ", ";
		lRes += cpot::ToString::Do(w);
		lRes += ")";
		return lRes;
	}

	#pragma endregion


	//静的な関数
	#pragma region Static

	static Vector4 FromFloat4(const f32* aVal) {
		return Vector4(aVal[0], aVal[1], aVal[2], aVal[3]);
	}

	static Vector4 FromVector3(const Vector3& aVal) {
		return Vector4(aVal.x, aVal.y, aVal.z, 1.0f);
	}
	static Vector4 One() {
		return Vector4().XYZW(1.0f);
	}
	static Vector4 Zero() {
		return Vector4().XYZW(0.0f);
	}

	#pragma endregion
};

#pragma endregion


class TexCoord {
public:
	TexCoord() {
		*this = Vector2(0.0f, 0.0f);
	}
	TexCoord(f32 aU, f32 aV) {
		*this = Vector2(aU, aV);
	}
	TexCoord(const Vector2& aUV) {
		*this = aUV;
	}

	const TexCoord& operator =(const Vector2& aUV) {
		mUV = Convert(aUV);
		return *this;
	}
	operator Vector2() const {
		return Convert(mUV);
	}

private:
	//環境ごとの変換
	static Vector2 Convert(const Vector2& aUV) {
		#ifdef CPOT_ON_DIRECTX11
		return Vector2(aUV.x, aUV.y);
		#elif defined CPOT_ON_OPENGL
		return Vector2(aUV.x, aUV.y);	//Vを反転
		#endif
	}


private:
	Vector2 mUV;
};



//2つのs32を持つクラス
#pragma region Point2

class Point2 {
public:
	s32 x, y;


	//コンストラクタ
	#pragma region Constructor

public:
	Point2() : x(0), y(0) {}
	Point2(s32 aX, s32 aY) : x(aX), y(aY) {}

	#pragma endregion


	//値を設定する
	#pragma region Setter

	Point2 X(s32 aV) const {
		return Point2(aV, y);
	}
	Point2 Y(s32 aV) const {
		return Point2(x, aV);
	}

	static Point2 XY(s32 aV) {
		return Point2(aV, aV);
	}
	static Point2 XY(s32 aX, s32 aY) {
		return Point2(aX, aY);
	}

	#pragma endregion

	//値を取得する
	#pragma region Getter

	//s32
	#pragma region s32

	s32 X() const {
		return x;
	}
	s32 Y() const {
		return y;
	}

	#pragma endregion


	//Point2
	#pragma region Point2

	Point2 XX() const {
		return Point2(x, x);
	}
	Point2 XY() const {
		return Point2(x, y);
	}

	Point2 YX() const {
		return Point2(y, x);
	}
	Point2 YY() const {
		return Point2(y, y);
	}

	Vector2 ToVector2() const {
		return Vector2((f32)x, (f32)y);
	}

	#pragma endregion


	#pragma endregion


	//計算のオペレータ
	#pragma region Calculate

	//Plus
	#pragma region

	const Point2& operator +=(const Point2& aVal) {
		x += aVal.x;
		y += aVal.y;
		return *this;
	}
	Point2 operator +(const Point2& aVal) const {
		Point2 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	const Point2& operator +=(s32 aVal) {
		x += aVal;
		y += aVal;
		return *this;
	}

	Point2 operator +(s32 aVal) const {
		Point2 tRes = *this;
		tRes += aVal;
		return tRes;
	}

	#pragma endregion

	//Sub
	#pragma region

	const Point2& operator -=(const Point2& aVal) {
		x -= aVal.x;
		y -= aVal.y;
		return *this;
	}
	Point2 operator -(const Point2& aVal) const {
		Point2 tRes = *this;
		tRes -= aVal;
		return tRes;
	}
	const Point2& operator -=(s32 aVal) {
		x -= aVal;
		y -= aVal;
		return *this;
	}
	Point2 operator -(s32 aVal) const {
		Point2 tRes = *this;
		tRes -= aVal;
		return tRes;
	}

	#pragma endregion

	//Multi
	#pragma region Multi

	const Point2& operator *=(s32 aVal) {
		x *= aVal;
		y *= aVal;
		return *this;
	}
	Point2 operator *(s32 aVal) const {
		Point2 tRes = *this;
		tRes *= aVal;
		return tRes;
	}

	#pragma endregion


	Point2 operator -() const {
		Point2 tRes(-x, -y);
		return tRes;
	}

	#pragma endregion


	//その他計算
	#pragma region Other


	#pragma endregion


	//文字列に変換する
	#pragma region ToString

public:
	String<64> ToString() const {
		String<64> lRes;
		lRes += "(";
		lRes += cpot::ToString::Do(x);
		lRes += ", ";
		lRes += cpot::ToString::Do(y);
		lRes += ")";
		return lRes;
	}

	#pragma endregion


	//ヘルパ関数
	#pragma region Helper

	//それぞれの最大の要素を選ぶ
	friend Point2 MaxElement(const Point2& aVal1, const Point2& aVal2) {
		Point2 tRes(Max(aVal1.x, aVal2.x), Max(aVal1.y, aVal2.y));
		return tRes;
	}
	friend Point2 MinElement(const Point2& aVal1, const Point2& aVal2) {
		Point2 tRes(Min(aVal1.x, aVal2.x), Min(aVal1.y, aVal2.y));
		return tRes;
	}

	#pragma endregion

};

#pragma endregion

}