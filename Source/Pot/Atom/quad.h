//
//	content	:	Quad2DÅAQuad3DÇ»Ç«ÇÃé¿ëï
//	author	:	SaitoYoshiki
//

#pragma once

#include "vector.h"


namespace cpot {


struct Quad2D {
	enum CPointIndex {
		cLeftBottom,
		cLeftTop,
		cRightBottom,
		cRightTop,
		cPointIndexMax,
	};

	Vector2 GetPoint(CPointIndex aIndex) const {
		CPOT_ASSERT(0 <= aIndex && aIndex < cPointIndexMax);
		return point[aIndex];
	}
	void SetPoint(CPointIndex aIndex, const Vector2& aPoint) {
		CPOT_ASSERT(0 <= aIndex && aIndex < cPointIndexMax);
		point[aIndex] = aPoint;
	}
	void SetRect(const Vector2& aBase, const Vector2& aSize) {
		point[cLeftBottom] = aBase + Vector2(0.0f, 0.0f);
		point[cLeftTop] = aBase + Vector2(0.0f, aSize.y);
		point[cRightBottom] = aBase + Vector2(aSize.x, 0.0f);
		point[cRightTop] = aBase + Vector2(aSize.x, aSize.y);
	}
	void SetRectFromCenter(const Vector2& aBase, const Vector2& aSize) {
		point[cLeftBottom] = aBase + Vector2(-aSize.x, -aSize.y) / 2.0f;
		point[cLeftTop] = aBase + Vector2(-aSize.x, aSize.y) / 2.0f;
		point[cRightBottom] = aBase + Vector2(aSize.x, -aSize.y) / 2.0f;
		point[cRightTop] = aBase + Vector2(aSize.x, aSize.y) / 2.0f;
	}
	
	Quad2D operator *(const Vector2& aValue) const {
		Quad2D q(*this);
		return q *= aValue;
	}
	Quad2D operator *=(const Vector2& aValue) {
		for (u32 i = 0; i < cPointIndexMax; i++) {
			point[i] *= aValue;
		}
		return *this;
	}

	Quad2D operator -(const Vector2& aValue) const {
		Quad2D q(*this);
		return q -= aValue;
	}
	Quad2D operator -=(const Vector2& aValue) {
		for (u32 i = 0; i < cPointIndexMax; i++) {
			point[i] -= aValue;
		}
		return *this;
	}

	Vector2 point[4];
};

}