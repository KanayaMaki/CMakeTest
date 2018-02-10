//
//	content	:	Mathの宣言。実装は、環境ごとのcppで
//	author	:	SaitoYoshiki
//

#pragma once

#include "defines.h"
#include "typedef.h"


namespace cpot {

//	値の絶対値を返す
#pragma region Abs

template <typename T>
inline T Abs(T aVal) {
	if (aVal < T(0)) aVal *= -1;
	return aVal;
}

#pragma endregion

//	余りを求める
#pragma region Mod

inline s32 Mod(s32 aVal, u32 aM) {
	return aVal % aM;
}
inline u32 Mod(u32 aVal, u32 aM) {
	return aVal % aM;
}

#pragma endregion


//	宣言
/*
const f32 cPi;
const f32 c2Pi;

const f32 cFloatEpsilon;
//*/


s32 Round(f32 aVal);

s32 Ceil(f32 aVal);

s32 Floor(f32 aVal);


f32 Mod(f32 aVal, f32 aM);


f32 Sin(f32 aRad);

f32 Cos(f32 aRad);

f32 Tan(f32 aRad);

f32 Asin(f32 aVal);

f32 Acos(f32 aVal);

f32 Atan(f32 aVal);


f32 Sqrt(f32 val);

f32 Exp(f32 val);

}



//	環境ごとのファイルのインクルード
#ifdef CPOT_ON_WINDOWS
#include "Standard/mathStandard.h"
#elif defined CPOT_ON_ANDROID
#include "Standard/mathStandard.h"
#elif defined CPOT_ON_LINUX
#include "Standard/mathStandard.h"
#endif