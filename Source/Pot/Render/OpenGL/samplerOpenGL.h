//
//	content	:	OpenGLでのSampler
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/sampler.h"
#include "./Pot/Render/OpenGL/Platform/samplerOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class Sampler : public SamplerBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//将来は、名前からデータを検索して、ロードできるようにしたい
	};
	void Load(CUVMode aMode) CPOT_OR {

		if (aMode == cWrap) {
			mSampler.Load(platform::Sampler::cRepeat);
		}
		else if (aMode == cClamp) {
			mSampler.Load(platform::Sampler::cClamp);
		}
	}

public:
	void Release() CPOT_OR {
		mSampler.Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mSampler.IsLoaded();
	}

public:
	platform::Sampler mSampler;

};

}

using Sampler = openGL::Sampler;

}