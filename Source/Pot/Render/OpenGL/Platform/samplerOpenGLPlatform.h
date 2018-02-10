#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"

namespace cpot {

namespace openGL {

namespace platform {


class Sampler {

public:
	Sampler() {
		Reset();
	}
	~Sampler() {
		Release();
	}

protected:
	void Reset() {
		mGLNum = 0;
	}

public:
	void Load(GLenum aWrapS, GLenum aWrapT) {
		if (IsLoaded()) {
			Release();
		}

		glGenSamplers(1, &mGLNum);
		glSamplerParameteri(mGLNum, GL_TEXTURE_WRAP_S, aWrapS);
		glSamplerParameteri(mGLNum, GL_TEXTURE_WRAP_T, aWrapT);
		glSamplerParameteri(mGLNum, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(mGLNum, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	void Load() {
		Load(GL_REPEAT, GL_REPEAT);
	}
	void LoadRepeat() {
		Load(GL_REPEAT, GL_REPEAT);
	}
	void LoadClamp() {
		Load(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	}
	enum CWrapMode {
		cRepeat,
		cClamp
	};
	void Load(CWrapMode aMode) {
		switch (aMode) {
			case cRepeat:
				LoadRepeat();
				break;
			case cClamp:
				LoadClamp();
				break;
		}
	}



	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		glDeleteSamplers(1, &mGLNum);
		Reset();
	}

	void Bind(u32 aSlotNum) {
		glBindSampler(aSlotNum, mGLNum);
	}

public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}

private:
	GLuint mGLNum;
};


}

}

}
