#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {


class Buffer {

public:
	Buffer() {
		Reset();
	}
	~Buffer() {
		Release();
	}


protected:
	void Reset() {
		mGLNum = 0;
	}

public:
	void Load(GLenum aTarget, u32 aSize, GLenum aUsage) {
		Load(aTarget, aSize, nullptr, aUsage);
	}
	void Load(GLenum aTarget, u32 aSize, const void* aInitData, GLenum aUsage) {
		if (IsLoaded()) {
			Release();
		}

		glGenBuffers(1, &mGLNum);
		glBindBuffer(aTarget, mGLNum);
		glBufferData(aTarget, aSize, aInitData, aUsage);

		if (mGLNum == 0) {
			CPOT_LOG("CreateError : BufferOpenGL.Load");
			return;
		}

		mSize = aSize;
		mTarget = aTarget;
	}
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		glBindBuffer(mTarget, 0);
		glDeleteBuffers(1, &mGLNum);
		Reset();
	}


public:
	BOOL Write(const void* aBuffer) {
		return Write(aBuffer, mSize);
	}
	BOOL Write(const void* aBuffer, u32 aSize) {
		glBindBuffer(mTarget, mGLNum);
		glBufferSubData(mTarget, 0, aSize, aBuffer);
		return true;	//書き込み成功
	}


public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}

	u32 GetSize() const {
		return mSize;
	}

private:
	GLuint mGLNum;
	GLenum mTarget;
	u32 mSize;
};


}

}

}
