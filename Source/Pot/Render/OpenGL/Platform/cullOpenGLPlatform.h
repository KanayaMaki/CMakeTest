#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {


/*

// OpenGLの場合
// 背面カリングを有効にする
// glEnable(GL_CULL_FACE);
// 反時計回り(counter clockwise)の頂点を持つ面を表と見なす (デフォルト)
// glFrontFace(GL_CCW);
// 時計回り(clockwise)の頂点を持つ面を表と見なす
// glFrontFace(GL_CW);

*/


class Cull {
public:
	Cull() {
		Reset();
	}
	~Cull() {
		Release();
	}

protected:
	void Reset() {
		mCullFace = true;
		mFrontFace = GL_CW;
	}

public:
	void Load(BOOL aCullFace, GLenum aFrontFace) {
		mCullFace = aCullFace;
		mFrontFace = aFrontFace;
	}
	void Load() {
		Reset();
	}
	void Release() {
		Reset();
	}


public:
	BOOL IsLoaded() const {
		return true;
	}

	BOOL GetCullFace() const {
		return mCullFace;
	}

	GLenum GetFrontFace() const {
		return mFrontFace;
	}


public:
	void SetToDevice() {
		if (mCullFace) {
			glEnable(GL_CULL_FACE);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
		glFrontFace(mFrontFace);
	}

protected:
	BOOL mCullFace;
	GLenum mFrontFace;
};


}

}

}
