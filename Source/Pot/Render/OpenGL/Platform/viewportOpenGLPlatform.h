#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {


class Viewport {

public:
	Viewport() {

	}
	Viewport(Vector2& aLeftTop, Vector2 aSize, f32 aMinDepth, f32 aMaxDepth) {
		mLeftTop = aLeftTop;
		mSize = aSize;
		mMinDepth = aMinDepth;
		mMaxDepth = aMaxDepth;
	}

public:
	void SetToDevice() {
		glViewport(mLeftTop.x, mLeftTop.y, mSize.x, mSize.y);
		glDepthRangef(mMinDepth, mMaxDepth);
	}


public:
	Vector2 mLeftTop;
	Vector2 mSize;
	f32 mMinDepth;
	f32 mMaxDepth;
};


}

}

}
