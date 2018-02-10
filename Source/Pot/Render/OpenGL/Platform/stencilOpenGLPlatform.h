#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {


class Stencil {
public:
	Stencil() {
		Reset();
	}
	~Stencil() {
		Release();
	}

protected:
	void Reset() {
		mStencilEnable = false;
	}

public:
	void Load(BOOL aStencilEnable, GLenum aStencilFunc, GLint aStencilRef, BOOL aStencilMask, GLenum aStencilFail, GLenum aStencilZFail, GLenum aStencilZPass) {
		mStencilEnable = aStencilEnable;
		mStencilFunc = aStencilFunc;
		mStencilMask = aStencilMask;
		mStencilRef = aStencilRef;
		mStencilFail = aStencilFail;
		mStencilZFail = aStencilZFail;
		mStencilZPass = aStencilZPass;
	}
	void Load() {
		Load(false, GL_EQUAL, 1, false, GL_KEEP, GL_REPLACE, GL_REPLACE);
	}

	void Release() {
		Reset();
	}
	void SetToDevice() {
		if (mStencilEnable) {
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(mStencilFunc, mStencilRef, 0xffffffff);
		}
		else {
			glDisable(GL_STENCIL_TEST);
		}

		if (mStencilMask) {
			glStencilMask(true);
			glStencilOp(mStencilFail, mStencilZFail, mStencilZPass);
		}
		else {
			glStencilMask(false);
		}
	}


public:
	BOOL IsLoaded() const {
		return true;
	}

	BOOL GetStencilEnable() const {
		return mStencilEnable;
	}
	BOOL GetStencilMask() const {
		return mStencilMask;
	}
	GLenum GetStencilFunc() const {
		return mStencilFunc;
	}
	GLint GetStencilRef() const {
		return mStencilRef;
	}

	GLenum GetStencilFail() const {
		return mStencilFail;
	}
	GLenum GetStencilZFail() const {
		return mStencilZFail;
	}
	GLenum GetStencilZPass() const {
		return mStencilZPass;
	}

protected:
	BOOL mStencilEnable;
	GLenum mStencilFunc;
	GLint mStencilRef;
	BOOL mStencilMask;

	GLenum mStencilFail;
	GLenum mStencilZFail;
	GLenum mStencilZPass;
};


}

}

}
