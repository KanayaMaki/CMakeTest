//
//	content	:	OpenGLでのViewport
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/viewport.h"
#include "./Pot/Render/OpenGL/Platform/viewportOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class Viewport : public ViewportBase {

public:
	Viewport() {
		mIsLoad = false;
	}

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//将来は、名前からデータを検索して、ロードできるようにしたい
	};
	void Load(const Vector2& aLeftTop, const Vector2& aSize) CPOT_OR {
		mViewport.mMinDepth = 0.0f;
		mViewport.mMaxDepth = 1.0f;
		mViewport.mLeftTop = aLeftTop;
		mViewport.mSize = aSize;
		mIsLoad = true;
	}

public:
	void Release() CPOT_OR {
		mIsLoad = false;
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mIsLoad;
	}

public:
	platform::Viewport mViewport;
	BOOL mIsLoad;
};

}

using Viewport = openGL::Viewport;

}