//
//	content	:	Standard‚Å‚ÌMath‚Ì’è‹`
//	author	:	SaitoYoshiki
//

#pragma once

#include "../defines.h"
#include "../typedef.h"

#include <cmath>
#include <cfloat>


namespace cpot {


const f32 cPi = 3.1415926535f;
const f32 c2Pi = 2 * 3.1415926535f;

const f32 cFloatEpsilon = FLT_EPSILON;


inline s32 Round(f32 aVal) {
	return s32(std::round(aVal));
}

inline s32 Ceil(f32 aVal) {
	return s32(std::ceil(aVal));
}

inline s32 Floor(f32 aVal) {
	return s32(std::floor(aVal));
}

inline f32 Mod(f32 aVal, f32 aM) {
	return std::fmod(aVal, aM);
}


inline f32 Sin(f32 aRad) {
	return std::sin(aRad);
}

inline f32 Cos(f32 aRad) {
	return std::cos(aRad);
}

inline f32 Tan(f32 aRad) {
	return std::tan(aRad);
}

inline f32 Asin(f32 aVal) {
	return std::asin(aVal);
}

inline f32 Acos(f32 aVal) {
	return std::acos(aVal);
}

inline f32 Atan(f32 aVal) {
	return std::atan(aVal);
}


inline f32 Sqrt(f32 val) {
	return std::sqrt(val);
}

inline f32 Exp(f32 val) {
	return std::exp(val);
}


}