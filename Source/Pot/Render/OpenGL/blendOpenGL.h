//
//	content	:	OpenGLでのBlend
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/blend.h"
#include "./Pot/Render/OpenGL/Platform/blendOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class Blend : public BlendBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//将来は、名前からデータを検索して、ロードできるようにしたい
	};
	void Load(CBlendMode aMode) CPOT_OR {

		if (aMode == cNormal) {
			mBlend.Load(platform::Blend::cNormal);
		}
		else if (aMode == cAdd) {
			mBlend.Load(platform::Blend::cAdd);
		}
	}

public:
	void Release() CPOT_OR {
		mBlend.Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mBlend.IsLoaded();
	}

public:
	platform::Blend mBlend;
};

}

using Blend = openGL::Blend;

}