//
//	content	:	基本となる関数
//	author	:	SaitoYoshiki
//

#pragma once


#include "defines.h"
#include "typedef.h"

#include "math.h"

#ifdef CPOT_ON_WINDOWS
#include <Windows.h>
#else
#endif


namespace cpot {


#pragma region マクロの定義

#define CPOT_NAME(name) #name
#define CPOT_NAME_EXTEND(name) CPOT_NAME(name)	//マクロの中で使うときに、CPOT_NAMEだと展開されないため
#define CPOT_ARRAY_SIZE(t) ((sizeof((t)) / sizeof((t[0]))))

#pragma endregion


#pragma region deleteの定義

#define CPOT_DELETE(p) if(p) { delete p; }
#define CPOT_DELETE_ARRAY(p) if(p) { delete[] p; }

#pragma endregion


//ラジアンからディグリーへの変換、その逆
#pragma region Radian

inline f32 ToRad(f32 aDegree) {
	return aDegree / 360.0f * c2Pi;
}

inline f32 ToDeg(f32 aRadian) {
	return aRadian / c2Pi * 360.0f;
}

#pragma endregion



//	値の符号を返す
#pragma region Sign

template <typename T>
inline s32 Sign(T aVal) {
	if (aVal > (T)0) return 1;
	if (aVal < (T)0) return -1;
	return 0;
}


template <typename T>
inline s32 SignSafe(T aVal) {
	if (aVal > (T)0) return 1;
	if (aVal < (T)0) return -1;
	return 1;
}


#pragma endregion



//	正規化した値を返す
#pragma region Normal

template <typename T>
inline f32 Normal(T aVal, T aMin, T aMax) {
	return (f32)(aVal - aMin) / (aMax - aMin);
}

#pragma endregion


//	正規化した値を、範囲に再配置する
#pragma region Replace

inline f32 Replace(f32 aNormal, f32 aMin, f32 aMax) {
	return aMin + (aMax - aMin) * aNormal;
}

#pragma endregion


//	最小値を求める
#pragma region Min

template <typename T, typename U>
inline T Min(const T& a, const U& b) {
	return a <= b ? a : b;
}

template <typename T, typename... Rest>
inline T Min(const T& a, const Rest&... rest) {
	return Min(a, Min(rest...));
}

#pragma endregion


//	最大値を求める
#pragma region Max

template <typename T, typename U>
inline T Max(const T& a, const U& b) {
	return a >= b ? a : b;
}

template <typename T, typename... Rest>
inline T Max(const T& a, const Rest&... rest) {
	return Max(a, Max(rest...));
}

#pragma endregion



//	絶対値で最小値を求める
//	例：Weak(-1.0, 2, 3)のとき、-1.0が返ってくる
#pragma region Weak

template <typename T, typename U>
inline T Weak(const T& a, const U& b) {
	return Abs(a) <= Abs(b) ? a : b;
}

template <typename T, typename... Rest>
inline T Weak(const T& a, const Rest&... rest) {
	return Weak(a, Weak(rest...));
}

#pragma endregion


//	絶対値で最大値を求める
#pragma region Strong

template <typename T, typename U>
inline T Strong(const T& a, const U& b) {
	return Abs(a) >= Abs(b) ? a : b;
}

template <typename T, typename... Rest>
inline T Strong(const T& a, const Rest&... rest) {
	return Strong(a, Strong(rest...));
}

#pragma endregion



//	累乗する
#pragma region Pow

template <typename T>
inline T Pow(T aVal, u32 aTimes) {
	T tV = T(1);
	for (u32 i = 0; i < aTimes; i++) {
		tV *= aVal;
	}
	return tV;
}


#pragma endregion



//	絶対値を減少させる
#pragma region DecrAbs

template <typename T>
inline T DcrAbs(T aVal, T aDecrAbs) {

	T res = Sign(aVal) * Max(T(0), Abs(aVal) - aDecrAbs);	//絶対値を減らす
	return res;
}

#pragma endregion



//	値が範囲内かなどを判定する
#pragma region Judge


//	範囲内かどうかを返す
#pragma region IsRange

template <typename T>
inline BOOL IsRange(T aVal, T aMin, T aMax) {
	if (aVal < aMin) {
		return false;
	}
	if (aVal > aMax) {
		return false;
	}
	return true;
}

template <typename T>
inline BOOL IsRange(T aVal, T aMax) {
	return IsRange(aVal, T(0), aMax);
}

#pragma endregion


//	値が、別の値とほぼ等しいか
#pragma region IsEqual

template <typename T>
inline BOOL IsEqual(T aVal, T aOther, T aEp) {
	T v = Abs(aVal - aOther);
	if (v <= aEp) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
inline BOOL IsEqual(T aVal, T aOther) {
	return IsEqual(aVal, aOther, T(0));
}

template <>
inline BOOL IsEqual<f32>(f32 aVal, f32 aOther) {
	return IsEqual(aVal, aOther, cFloatEpsilon * Max(Abs(aVal), Abs(aOther)));
}


#pragma endregion


//	ほぼ0かどうか
inline BOOL IsZero(f32 aVal) {
	return IsEqual(aVal, 0.0f);
}
inline BOOL IsZero(f64 aVal) {
	return IsEqual(aVal, 0.0);
}

//	0でない
inline BOOL NotZero(f32 aVal) {
	return !IsZero(aVal);
}
inline BOOL NotZero(f64 aVal) {
	return !IsZero(aVal);
}


inline BOOL IsNull(void* aVal) {
	return aVal == nullptr;
}
inline BOOL NotNull(void* aVal) {
	return !IsNull(aVal);
}


inline BOOL Is(BOOL aExp) {
	return aExp == true;
}
inline BOOL Not(BOOL aExp) {
	return aExp != true;
}


#pragma endregion




//	範囲内に制限された値を返す
#pragma region Clamp

template <typename T>
inline T Clamp(T aVal, T aMin, T aMax) {
	if (aVal < aMin) {
		return aMin;
	}
	if (aVal > aMax) {
		return aMax;
	}
	return aVal;
}

//	範囲内に制限された値を返す
template <typename T>
inline T Clamp(T aVal, T aMax) {
	return Clamp(aVal, (T)0, aMax);
}

template <typename T>
inline T Clamp01(T aVal) {
	return Clamp(aVal, (T)0, (T)1);
}


//	範囲内に制限された値を返す
template <typename T>
inline T ClampRange(T aVal, T aEdge1, T aEdge2) {
	if (aEdge1 < aEdge2) {
		return Clamp(aVal, aEdge1, aEdge2);
	}
	else {
		return Clamp(aVal, aEdge2, aEdge1);
	}
}


#pragma endregion



//	範囲内に収まるようにループされた数
#pragma region Wrap

template <typename T>
inline T Wrap(T aVal, T aMin, T aMax) {
	T dist = aMax - aMin;
	if (IsZero(dist)) return aMin;
	while (aVal >= aMax) aVal -= dist;
	while (aVal < aMin) aVal += dist;
	return aVal;
}

template <typename T>
inline T Wrap(T aVal, T aMax) {
	return Wrap(aVal, (T)0, aMax);
}


#pragma endregion


//	アラインメントされた数
#pragma region Align

template <typename T>
inline T Align(T aVal, T aAlignNum) {
	return (aVal + aAlignNum - 1) / aAlignNum * aAlignNum;
}


#pragma endregion


//その他
#pragma region Other


//	文字列が等しいかどうか
inline BOOL StringSame(const CHAR* aStr1, const CHAR* aStr2) {

	for (s32 i = 0;; i++) {

		//もし文字が違ったら
		if (aStr1[i] != aStr2[i]) {
			return false;	//等しくない
		}

		//文字列が終わっているかどうか
		bool end1 = (aStr1[i] == '\0');
		bool end2 = (aStr2[i] == '\0');

		//両方終わっているなら
		if (end1 && end2) {
			return true;	//等しい
		}
		//どちらかだけが終わっているなら
		else if (end1 || end2) {
			return false;	//等しくない
		}
		//どちらも終わっていないなら
		else {
			//処理を続ける
		}
	}
	return true;	//ここまでは来ない
}


//	文字列の長さを計算する
inline const u32 StringLen(const CHAR* aStr) {
	u32 i = 0;
	while (aStr[i] != '\0') {
		i++;
	}
	return i;
}


//	メモリをコピーする
inline void CopyMem(void* aTo, const void* aFrom, Pointer aSize) {
	#ifdef CPOT_ON_WINDOWS
	CopyMemory(aTo, aFrom, aSize);
	#else
	for (Pointer i = 0; i < aSize; i++) {
		((u8*)aTo)[i] = ((const u8*)aFrom)[i];
}
	#endif
	
}


//メモリを０で埋める
inline void ZeroMem(void* aMem, Pointer aSize) {
	for (Pointer i = 0; i < aSize; i++) {
		((u8*)aMem)[i] = 0;
	}
}


//エンディアンを逆転させる。例：リトルエンディアンをビッグエンディアンにする
template <typename T>
inline T ReverseEndian(const T aVal) {

	u32 lByteNum = sizeof(T);

	//結果を格納する変数
	T lRes;

	const u8* lFrom = (const u8*)(&aVal);
	u8* lTo = (u8*)(&lRes);

	//バイト数が4の場合、0と3、1と2、という風になるように入れ替える
	for (u32 i = 0; i < lByteNum; i++) {
		lTo[i] = lFrom[lByteNum - i - 1];
	}

	return lRes;
}

//エンディアンを入れ替える（void*版、できれば上のテンプレート版を使って欲しい）
inline void ReverseEndian(void* aVal, u32 aByteNum) {

	CPOT_ASSERT(Mod(aByteNum, 2) == 0);

	//バイト数が4の場合、0と3、1と2、という風になるように入れ替える
	for (u32 i = 0; i < aByteNum / 2; i++) {

		//左側の値を保存
		u8 tB = ((u8*)aVal)[i];
		//左側に、右側の値を代入
		((u8*)aVal)[i] = ((u8*)aVal)[aByteNum - i - 1];
		//右側に、先ほど保存した左側の値を代入
		((u8*)aVal)[aByteNum - i - 1] = tB;
	}
}


#pragma endregion



//補間関数
#pragma region Tween

inline f32 Lerp(f32 aStart, f32 aEnd, f32 aRate) {
	return aStart + (aEnd - aStart) * aRate;
}


//割合を求める
inline f32 Rate(f32 start, f32 end, f32 now) {
	f32 dist = end - start;
	CPOT_ASSERT(NotZero(dist));
	return (now - start) / dist;
}


//0.0fに近いほど、線形と比べて値が小さくなるLerp
inline f32 EaseIn(f32 t) {
	return t * t;
}


//0.0fに近いほど、線形と比べて値が大きくなる
inline f32 EaseOut(f32 t) {
	return 1.0f - EaseIn(1.0f - t);
}


//0.0fに近いほど、また1.0fに近いほど、線形と比べて値が大きくなる
inline f32 EaseInOut(f32 r) {
	return (-2 * r * r * r + 3 * r * r);
}

#pragma endregion


}