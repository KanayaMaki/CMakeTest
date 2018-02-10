//
//	content	:	色を表すクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "defines.h"
#include "typedef.h"
#include "math.h"
#include "function.h"
#include "vector.h"


namespace cpot {

#pragma region Color

//色を表すR32G32B32A32浮動小数点型のクラス
class Color {

	//フィールド
	#pragma region Field

public:
	f32 r, g, b, a;

	#pragma endregion


	//コンストラクタ
	#pragma region Constructor

public:
	Color(f32 aR, f32 aG, f32 aB, f32 aA) : r(aR), g(aG), b(aB), a(aA) {}
	Color(f32 aR, f32 aG, f32 aB) : r(aR), g(aG), b(aB), a(MaxValue()) {}
	Color() : r(MinValue()), g(MinValue()), b(MinValue()), a(MaxValue()) {}

	#pragma endregion


	//取得
	#pragma region Getter

	Vector4 ToVector4() const {
		Vector4 lRes(r, g, b, a);
		return lRes;
	}
	Vector3 ToVector3() const {
		Vector3 lRes(r, g, b);
		return lRes;
	}
	struct Float4 {
		f32 v[4];
	};
	Float4 ToFloat4() const {
		Float4 lRes = { r, g, b, a };
		return lRes;
	}

	#pragma endregion


	//作成
	#pragma region Create

	static Color FromVector4(const Vector4& aV) {
		return Color(aV.x, aV.y, aV.z, aV.w);
	}

	static Color FromVector3(const Vector3& aV) {
		return Color(aV.x, aV.y, aV.z, MaxValue());
	}


	//具体的な色を作成する
	#pragma region Color

	static Color White() {
		return Color(MaxValue(), MaxValue(), MaxValue());
	}
	static Color LightGray() {
		Color lRes(MaxValue(), MaxValue(), MaxValue());
		return lRes / 4L * 3L;
	}
	static Color Gray() {
		Color lRes(MaxValue(), MaxValue(), MaxValue());
		return lRes / 4L * 2L;
	}
	static Color DarkGray() {
		Color lRes(MaxValue(), MaxValue(), MaxValue());
		return lRes / 4L * 1L;
	}
	static Color Black() {
		return Color(MinValue(), MinValue(), MinValue());
	}

	static Color Red() {
		return Color(MaxValue(), MinValue(), MinValue());
	}
	static Color Green() {
		return Color(MinValue(), MaxValue(), MinValue());
	}
	static Color Blue() {
		return Color(MinValue(), MinValue(), MaxValue());
	}

	static Color Yellow() {
		return Color(MaxValue(), MaxValue(), MinValue());
	}
	static Color Cyan() {
		return Color(MinValue(), MaxValue(), MaxValue());
	}
	static Color Magenta() {
		return Color(MaxValue(), MinValue(), MaxValue());
	}

	#pragma endregion

	#pragma endregion


	//計算
	#pragma region Calculate

	const Color& operator +=(const Color& aVal) {
		r += aVal.r;
		g += aVal.g;
		b += aVal.b;
		//aはそのまま
		return *this;
	}
	Color operator +(const Color& aVal) const {
		Color lResult(*this);
		return lResult += aVal;
	}

	const Color& operator *=(f32 aVal) {
		r *= aVal;
		g *= aVal;
		b *= aVal;
		//aはそのまま
		return *this;
	}
	Color operator *(f32 aVal) const {
		Color lResult(*this);
		return lResult *= aVal;
	}

	const Color& operator /=(f32 aVal) {
		CPOT_ASSERT(NotZero(aVal));
		r /= aVal;
		g /= aVal;
		b /= aVal;
		//aはそのまま
		return *this;
	}
	Color operator /(f32 aVal) const {
		Color lResult(*this);
		return lResult /= aVal;
	}


	//透明にする
	Color Alpha(f32 aA) const {
		Color lRes(*this);
		lRes.a = Clamp(MaxValue() * aA, MinValue(), MaxValue());
		return lRes;
	}

	//完全に透明にする
	Color Translate() const {
		Color lRes(*this);
		lRes.a = MinValue();
		return lRes;
	}

	//不透明にする
	Color NotTranslate() const {
		Color lRes(*this);
		lRes.a = MaxValue();
		return lRes;
	}

	#pragma endregion


	//静的
	#pragma region Static

	static f32 MaxValue() { return 1.0f; }
	static f32 MinValue() { return 0.0f; }

	#pragma endregion

};

#pragma endregion



#pragma region Color32

//色を表すR8G8B8A8符号なし整数のクラス
class Color32 {

	//フィールド
	#pragma region Field

public:
	u8 r, g, b, a;

	#pragma endregion


	//コンストラクタ
	#pragma region Constructor

public:
	Color32(u8 aR, u8 aG, u8 aB, u8 aA) : r(aR), g(aG), b(aB), a(aA) {}
	Color32(u8 aR, u8 aG, u8 aB) : r(aR), g(aG), b(aB), a(MaxValue()) {}
	Color32() : r(MinValue()), g(MinValue()), b(MinValue()), a(MaxValue()) {}

	#pragma endregion


	//取得
	#pragma region Getter

	Color ToColor() const {
		Color lRes((f32)r / MaxValue(), (f32)g / MaxValue(), (f32)b / MaxValue(), (f32)a / MaxValue());
		return lRes;
	}

	#pragma endregion


	//作成
	#pragma region Create

	static Color32 FromColor(const Color& aV) {
		return Color32(
			static_cast<u8>( Clamp01(aV.r) * MaxValue() ),
			static_cast<u8>( Clamp01(aV.g) * MaxValue() ),
			static_cast<u8>( Clamp01(aV.b) * MaxValue() ),
			static_cast<u8>( Clamp01(aV.a) * MaxValue() )
		);
	}

	#pragma endregion


	//静的
	#pragma region Static

	static u8 MaxValue() { return u8(255U); }
	static u8 MinValue() { return u8(0U); }

	#pragma endregion

};

#pragma endregion


}